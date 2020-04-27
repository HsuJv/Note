use chrono::NaiveDateTime;
use tokio_postgres::types::Type;
use tokio_postgres::NoTls;

const CONN_STATEMENT: &str =
    "xxxxxxxxxxxxxxxxxxxxxxxx";
const QUERY_STATEMENT: &str =
    "yyyyyyyyyyyyyyyyyyyyy";
const VER_STATEMENT: &str = "zzzzzzzzzzzzzzzzz";
const ASSIGN_STATEMENT: &str = "aaaaaaaaaaaaaa";

#[derive(Debug)]
pub struct JobInfo {
    pub id: String,
    pub assignee: String,
    pub reporter: String,
    pub status: String,
    pub create_time: String,
    pub summary: String,
    pub priority: String,
    pub version: Vec<String>,
    pub link: String,
    pub customer_name: String,
}

pub async fn get_job(id: i32) -> Result<JobInfo, Box<dyn std::error::Error>> {
    // connection the db
    let (client, connection) = tokio_postgres::connect(CONN_STATEMENT, NoTls).await?;

    tokio::spawn(async move {
        if let Err(e) = connection.await {
            error!("Error to connect the database {0}", e);
        }
    });
    // preparation to query the job detail
    let query = client.prepare_typed(QUERY_STATEMENT, &[Type::INT4]).await?;
    let result = client.query_one(&query, &[&id]).await?;

    // preparation to query the versions that this job affects
    let version_query = client.prepare_typed(VER_STATEMENT, &[Type::INT4]).await?;
    // preparation to query the ticket owner
    let assignee_query = client
        .prepare_typed(ASSIGN_STATEMENT, &[Type::INT4])
        .await?;

    // versions that this job affects
    let version: Vec<String> = client
        .query(&version_query, &[&id])
        .await?
        .iter()
        .map(|x| x.get(2))
        .collect();
    // ticket owner
    let assignee: String = client
        .query_one(&assignee_query, &[&result.get::<usize, i32>(1)])
        .await?
        .get(1);

    Ok(JobInfo {
        id: id.to_string(),
        assignee,
        reporter: result.get::<usize, i32>(0).to_string(),
        status: String::from("abc"),
        create_time: result.get::<usize, NaiveDateTime>(1).to_string(),
        summary: format!("{0} {1}", id, result.get::<usize, String>(2)),
        priority: result.get::<usize, String>(3),
        version,
        link: format!(
            "xxxxxxxxxxxxxxxx{0}",
            id
        ),
        customer_name: match result.get::<usize, String>(5) {
            s if s.ends_with("]") => {
                s[s.rfind("[").unwrap_or_else(|| s.len() - 2) + 1usize..s.len() - 1].to_string()
            }
            s if s.ends_with(")") => {
                s[s.rfind("(").unwrap_or_else(|| s.len() - 2) + 1usize..s.len() - 1].to_string()
            }
            _ => String::new(),
        },
    })
}
