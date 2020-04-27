use tokio::io;
use tokio::net::TcpStream;
use tokio::prelude::*;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // parse the address
    let addr = "0.0.0.0:8090".parse().unwrap();
    let client = TcpStream::connect(&addr)
        .and_then(|stream| {
            println!("created client stream");
            io::write_all(stream, "hello world\n").then(|result| {
                println!("wrote to stream; success={:?}", result.is_ok());
                Ok(())
            })
        })
        .map_err(|err| {
            // all task must have an Error type of (). This forces error
            // handling and helps avoid silencing failures.

            eprintln!("connection error = {:?}", err);
        });
    println!("About to create the stream and write to it...");
    tokio::run(client);
    println!("Stream has been created and written to.");
    Ok(())
}
