extern crate bytes;
extern crate tokio;
#[macro_use]
extern crate futures;

use bytes::{Buf, Bytes};
use futures::{Async, Future, Poll};
use std::io::{self, Cursor};
use tokio::io::AsyncWrite;
use tokio::net::{tcp::ConnectFuture, TcpStream};

enum HelloWorld {
    Connecting(ConnectFuture),
    Connected(TcpStream, Cursor<Bytes>),
}

impl Future for HelloWorld {
    type Item = ();
    type Error = io::Error;

    fn poll(&mut self) -> Poll<(), io::Error> {
        use self::HelloWorld::*;

        loop {
            match self {
                Connecting(ref mut f) => {
                    let sock = try_ready!(f.poll());
                    let data = Cursor::new(Bytes::from_static(b"hello world"));
                    println!("conneted");
                    *self = Connected(sock, data);
                }
                Connected(ref mut sock, ref mut data) => {
                    // Keep trying to write the buffer to the socket as long
                    // as the buffer has more bytes available for consumption
                    while data.has_remaining() {
                        try_ready!(sock.write_buf(data));
                    }
                    println!("sended");
                    return Ok(Async::Ready(()));
                }
            }
        }
    }
}

fn main() {
    let addr = "127.0.0.1:8090".parse().unwrap();
    let cnnt_future = TcpStream::connect(&addr);
    let hello_world = HelloWorld::Connecting(cnnt_future);
    println!("start to run");
    // Run it, here we map the error since tokio::run expects a Future<Item=(), Error=()>
    tokio::run(hello_world.map_err(|e| println!("{0}", e)));
    println!("end of main");
}
