use config::*;
use std::fs;

#[derive(Serialize, Deserialize, Debug)]
struct MyConfig {
    email: Vec<String>,
    users: Vec<String>,
    file_root: String,
    cgi_root: String,
    server_ip: String,
    server_port: String,
    #[serde(default = "String::new")]
    proxy_server: String,
}

lazy_static! {
    static ref SETTINGS: Config = {
        let mut settings = Config::default();
        settings.merge(File::with_name("conf.json")).unwrap();

        settings
    };
}

#[allow(dead_code)]
pub fn show() {
    println!("\n{:?} \n\n-----------", SETTINGS.clone());
}

pub fn get_setting_vec(s: &str) -> Option<Vec<String>> {
    match SETTINGS.get_array(s) {
        Ok(ret) => Some(ret.iter().map(|x| x.clone().into_str().unwrap()).collect()),
        _ => None,
    }
}

pub fn get_setting_str(s: &str) -> Option<String> {
    match SETTINGS.get_str(s) {
        Ok(ret) => Some(ret),
        _ => None,
    }
}

pub fn add_email(s: &str) {
    let mut my_config: MyConfig =
        serde_json::from_str(fs::read_to_string("conf.json").unwrap().as_str()).unwrap();
    match my_config.email.binary_search(&String::from(s)) {
        Err(_) => {
            my_config.email.push(s.to_string());
            let json = serde_json::to_string_pretty(&my_config).unwrap();
            if let Err(e) = fs::write("conf.json", json) {
                error!("Fail to update the email list {0}", e);
            }
        }
        _ => warn!("email_addr {0} already in the list", s),
    }
    ()
}

pub fn add_user(s: &str) {
    let mut my_config: MyConfig =
        serde_json::from_str(fs::read_to_string("conf.json").unwrap().as_str()).unwrap();
    match my_config.users.binary_search(&String::from(s)) {
        Err(_) => {
            my_config.users.push(s.to_string());
            let json = serde_json::to_string_pretty(&my_config).unwrap();
            if let Err(e) = fs::write("conf.json", json) {
                error!("Fail to update the users list {0}", e);
            }
        }
        _ => warn!("user {0} already in the list", s),
    }
    ()
}
