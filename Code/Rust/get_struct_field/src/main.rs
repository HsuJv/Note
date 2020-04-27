#[derive(Debug)]
struct MyStruct {
    a: i32,
    b: String,
}

macro_rules! get_field {
    ($member: ident, $type: ident) => {{
        let my_struct = MyStruct {
            a: 1,
            b: "10".to_string(),
        };
        let t: $type = my_struct.$member;
        t
    }};
}

fn main() {
    println!("{:?}", get_field!(a, i32));
    ()
}
