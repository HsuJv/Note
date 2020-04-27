use std::io::prelude::*;
use std::net::{TcpListener, TcpStream};
use std::{fs, str};
use threadpool::ThreadPool;

static HTTP_GET_STRING: &str = "GET";
static HTTP_POST_STRING: &str = "POST";

fn main() {
    let lfd = TcpListener::bind("0.0.0.0:8090").unwrap();
    let th_pool = ThreadPool::new(4);

    for stream in lfd.incoming() {
        let stream = stream.unwrap();

        // conn_handler(stream);
        th_pool.execute(move || {
            conn_handler(stream);
        });
    }
}

fn conn_handler(mut stream: TcpStream) {
    let mut buf = [0u8; 512];

    stream.read(&mut buf).unwrap();
    let response = rqst_handler(&buf);
    stream.write(response.as_bytes()).unwrap();
    stream.flush().unwrap();
}

fn rqst_handler(req: &[u8]) -> String {
    if req.starts_with(HTTP_GET_STRING.as_bytes()) {
        return get_handler(&req);
    } else if req.starts_with(HTTP_POST_STRING.as_bytes()) {
        return post_handler(&req);
    };
    error_handler()
}

fn get_handler(req: &[u8]) -> String {
    let start = HTTP_GET_STRING.len() + 2;
    let mut end = start;
    while b' ' != req[end] {
        end += 1;
    }
    // println!("{}{}   {}", String::from_utf8_lossy(&req), start, end);
    let filename = match end - start {
        0 => "index.html",
        _ => str::from_utf8(&req[start..end]).unwrap(),
    };
    if let Ok(file_ctx) = fs::read_to_string(filename) {
        let mut res = String::from("HTTP/1.1 200 OK\r\n\r\n");
        res += &file_ctx;
        return res;
    };
    error_handler()
}

fn post_handler(req: &[u8]) -> String {
    panic!("Do not support now");
}

fn error_handler() -> String {
    let ctx_404 = fs::read_to_string("404.html").unwrap();
    let mut res = String::from("HTTP/1.1 404 NOT FOUND\r\n\r\n");
    res += &ctx_404;
    res
}
