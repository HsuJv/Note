// use std::thread::{sleep, spawn};
// use std::time::Duration;

// fn sleepus() {
//     for i in 1..=10 {
//         println!("Sleepus {}", i);
//         sleep(Duration::from_millis(500));
//     }
// }

// fn interruptus() {
//     for i in 1..=5 {
//         println!("Interruptus {}", i);
//         sleep(Duration::from_millis(1000));
//     }
// }

// fn main() {
//     let sleepus = spawn(sleepus);
//     let interruptus = spawn(interruptus);

//     sleepus.join().unwrap();
//     interruptus.join().unwrap();
// }

use async_std::task::{sleep, spawn};
use std::time::Duration;

// fn sleepus() -> impl std::future::Future<Output=()> {
//     async {
//         for i in 1..=10 {
//             println!("Sleepus {}", i);
//             sleep(Duration::from_millis(500)).await;
//         }
//     }
// }

async fn sleepus() {
    for i in 1..=10 {
        println!("Sleepus {}", i);
        sleep(Duration::from_millis(500)).await;
    }
}

async fn interruptus() {
    for i in 1..=5 {
        println!("Interruptus {}", i);
        sleep(Duration::from_millis(1000)).await;
    }
}

#[async_std::main]
async fn main() {
    let sleepus = spawn(sleepus());
    interruptus().await;

    sleepus.await;
}
