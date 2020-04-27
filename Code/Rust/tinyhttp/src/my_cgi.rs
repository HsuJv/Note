use crate::my_config::*;
use crate::my_job::{get_job, JobInfo};
use crate::my_email::send_email;
use crate::my_jira::create_ticket;
use std::env;
use std::error::Error;
use tokio;

pub enum CgiAction {
    Restart,
    SyncJob,
    AddEmail,
    GetEmails,
    AddUser,
    GetUsers,
}

async fn cgi_restart() {
    warn!("receive a restart request, restart in 2 secs");
    env::set_var("RUST_SERVER_RESTART", "1");
    std::thread::sleep(std::time::Duration::from_secs(2u64));
    crate::restart();
}

async fn cgi_sync_job(query: Option<&str>) -> Result<(), Box<dyn Error>> {
    let query_str = query.unwrap();
    let job_id = &query_str[query_str.rfind("=").unwrap() + 1..];
    match job_id.parse::<i32>() {
        Ok(job) => {
            info!("Sync Job: {0}", job);
            let job: JobInfo = get_job(job).await?;
            let result = create_ticket(job).await?;
            if result.len() > 0 {
                send_email(get_setting_vec("email").unwrap(), result).await?;
            }
        }
        _ => {
            error!("An invalid job id");
        }
    }
    Ok(())
}

fn cgi_get_emails() -> String {
    format!("{:?}", get_setting_vec("email").unwrap())
}

fn cgi_add_email(query: Option<&str>) {
    let query_str = query.unwrap();
    let new_address = &query_str[query_str.rfind("=").unwrap() + 1..];
    warn!("updating email list");
    add_email(new_address);
}

fn cgi_get_users() -> String {
    format!("{:?}", get_setting_vec("users").unwrap())
}

fn cgi_add_user(query: Option<&str>) {
    let query_str = query.unwrap();
    let new_user = &query_str[query_str.rfind("=").unwrap() + 1..];
    warn!("updating user list");
    add_user(new_user);
}

pub async fn cgi_exec(action: CgiAction, query: Option<&str>) -> Result<String, Box<dyn Error>> {
    match action {
        CgiAction::Restart => {
            tokio::spawn(async move {
                cgi_restart().await;
            });
            Ok(String::from("Restarting"))
        }
        CgiAction::SyncJob => {
            cgi_sync_job(query).await?;
            Ok(String::from("Job Synced"))
        }
        CgiAction::AddEmail => {
            cgi_add_email(query);
            Ok(String::from("Email List Updated"))
        }
        CgiAction::GetEmails => Ok(cgi_get_emails()),
        CgiAction::AddUser => {
            cgi_add_user(query);
            Ok(String::from("User List Updated"))
        }
        CgiAction::GetUsers => Ok(cgi_get_users()),
    }
}
