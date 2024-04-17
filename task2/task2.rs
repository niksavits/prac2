use std::io;

fn gcd(mut a: i32, mut b: i32) -> i32 {
    while b != 0 {
        let r = a % b;
        a = b;
        b = r;
    }
    a
}

fn mult_invers(c: i32, m: i32) -> Option<i32> {
    if gcd(c, m) != 1 {
        println!("Такого не существует!");
        return None;
    }
    for d in 1..m {
        if (c * d) % m == 1 {
            return Some(d);
        }
    }
    None
}

fn main() {
    println!("Введите c: ");
    let mut c = String::new();
    io::stdin().read_line(&mut c).expect("Не удалось прочитать строку");
    let c: i32 = c.trim().parse().expect("Ожидалось целое число");

    println!("Введите m: ");
    let mut m = String::new();
    io::stdin().read_line(&mut m).expect("Не удалось прочитать строку");
    let m: i32 = m.trim().parse().expect("Ожидалось целое число");

    if let Some(d) = mult_invers(c, m) {
        println!("Число d равно: {}", d);
    }
}