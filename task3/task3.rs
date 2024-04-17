use std::io;

fn adv_euclid(a: i32, b: i32, u: &mut i32, v: &mut i32) -> i32 {
    if b == 0 {
        *u = 1;
        *v = 0;
        return a;
    }
    let mut u1 = 0;
    let mut v1 = 0;
    let nod = adv_euclid(b, a % b, &mut u1, &mut v1);
    *u = v1;
    *v = u1 - (a / b) * v1;
    nod
}

fn main() {
    println!("Введите c:");
    let mut c = String::new();
    io::stdin().read_line(&mut c).expect("Не удалось прочитать строку");
    let c: i32 = c.trim().parse().expect("Введено некорректное число");

    println!("Введите m:");
    let mut m = String::new();
    io::stdin().read_line(&mut m).expect("Не удалось прочитать строку");
    let m: i32 = m.trim().parse().expect("Введено некорректное число");

    let mut u = 0;
    let mut v = 0;
    let nod = adv_euclid(c, m, &mut u, &mut v);

    if nod != 1 {
        println!("Не существует взаимнообратного числа.");
        return;
    }

    let d = (u % m + m) % m;
    println!("d: {}", d);
}
