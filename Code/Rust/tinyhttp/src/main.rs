#[macro_use]
extern crate serde_derive;
#[macro_use]
extern crate lazy_static;
#[macro_use]
extern crate log;
#[macro_use]
extern crate serde_json;

mod my_cgi;
mod my_config;
mod my_job;
mod my_email;
mod my_http;
mod my_jira;

use std::env;
use std::error::Error;
use std::os::unix::process::CommandExt;
use std::process::Command;

#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    env_logger::init();

    if let Ok(_) = env::var("RUST_SERVER_RESTART") {
        env::remove_var("RUST_SERVER_RESTART");
    }

    if let Some(file_root) = my_config::get_setting_str("file_root") {
        info!("Set File Root {0}", file_root);
        env::set_var("File_Root", file_root);
    } else {
        panic!("Lack the key File_Root in config");
    }

    if let Some(cgi_root) = my_config::get_setting_str("cgi_root") {
        info!("Set Cgi Root {0}", cgi_root);
        env::set_var("Cgi_Root", cgi_root);
    } else {
        panic!("Lack the key Cgi_Root in config");
    }

    if let Some(proxy_server) = my_config::get_setting_str("proxy_server") {
        env::set_var("http_proxy", &proxy_server);
        env::set_var("https_proxy", &proxy_server);
        info!("Set proxy server {0}", proxy_server);
    }

    if let (Some(server_ip), Some(server_port)) = (
        my_config::get_setting_str("server_ip"),
        my_config::get_setting_str("server_port"),
    ) {
        tokio::spawn(async move {
            if let Err(e) = my_http::run_http_server(&server_ip, &server_port).await {
                panic!("Failed to start http server {0}", e);
            }
        });
    } else {
        panic!("Lack the key server_ip, server_port in config");
    }

    loop {}

    // Ok(())
}

fn restart() {
    warn!("Process restarting");
    Command::new("/proc/self/exe").exec();
}
