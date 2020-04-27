use crate::my_job::JobInfo;
use base64::encode;
use reqwest::*;
use serde_json;

const JIRA_API: &str = "*************";
const AUTH_INFO: &[u8] = b"user:password";

lazy_static! {
    static ref HEADERS: header::HeaderMap = {
        let mut headers = header::HeaderMap::new();
        headers.insert("Content-Type", "application/json".parse().unwrap());
        headers.insert("Accpet", "application/json".parse().unwrap());
        headers.insert(
            "Authorization",
            format!(" Basic {0}", encode(AUTH_INFO)).parse().unwrap(),
        );
        headers
    };
}

async fn dup_check(job_id: &str) -> Result<i32> {
    let query = json!({
        "maxResults": 1000,
        "startAt": 0
    });

    let res = Client::new()
        .get(&(String::from(JIRA_API) + "search"))
        .headers((*HEADERS).clone())
        .query(&query)
        .send()
        .await?;

    let res_str = res.text().await?;
    // 53 indeed
    if res_str.len() > 60 {
        Ok(1)
    } else {
        Ok(0)
    }
}

pub async fn create_ticket(job_info: JobInfo) -> Result<String> {
    // build the json body
    let dup_num = dup_check(&job_info.id[..]).await?;
    if 0 == dup_num {
        let lambda = |x: i32| {
            json!({
                "id" : x.to_string()
            })
        };
        let version_info: Vec<serde_json::Value> = job_info
            .version
            .iter()
            .map(move |x| match x {
                s if s.starts_with("Version x.y.z.0") => lambda(0),
                s if s.starts_with("Version x.y.z.1") => lambda(1),
                s if s.starts_with("Version x.y.z.2") => lambda(2),
                s if s.starts_with("Version x.y.z.3") => lambda(3),
                s if s.starts_with("Version x.y.z.4") => lambda(4),
                s if s.starts_with("Version x.y.z.5") => lambda(5),
                s if s.starts_with("Version x.y.z.6") => lambda(6),
                _ => serde_json::Value::String(String::new()),
            })
            .collect();

        info!("Ready to create ticket {:?}", &job_info);
        let json_data = json!({
            "update": {}
        });

        debug!("{:?}", json_data);
        let res = Client::new()
            .post(&(String::from(JIRA_API) + "issue/"))
            .headers((*HEADERS).clone())
            .json(&json_data)
            .send()
            .await?;
        info!("Updated with respose {:?}", res);
        let res_str = res.text().await?;
        Ok(res_str)
    } else {
        info!("Found dup entry of job {0}", &job_info.id[..]);
        Ok(String::new())
    }
}
