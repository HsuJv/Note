use std::{env, process};

use minigrep::Config;

fn main() {
    let config = Config::new(env::args()).unwrap_or_else(|err| {
        eprintln!("Problem parsing arguments: {}", err);
        process::exit(1);
    });
    println!(
        "Searching for {} \nIn file {}",
        config.query, config.filename
    );

    if let Err(e) = minigrep::run(config) {
        eprintln!("Error: {}", e);
        process::exit(1);
    }
}

// fn parse_config(args: Vec<String>) -> Config {
//     if args.len() < 3 {
//         panic!("not enough arguments");
//     }
//     Config {
//         query: args[1].clone(),
//         filename: args[2].clone(),
//     }
// }
