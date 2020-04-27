#[derive(Debug)]
struct Rectangle {
    h: u32,
    w: u32,
}

fn main() {
    let rect = Rectangle {h: 30, w: 50};
    println!("rect is {:?}", rect);
    println!("rect is {:#?}", rect);
    println!("The area of the rectangle is {} square pixels", area(&rect));
}

fn area(r: &Rectangle) -> u32 {
    r.h * r.w
}
