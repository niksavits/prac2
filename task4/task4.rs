use rand::Rng;
use std::io;

fn is_prime(n: u64) -> bool {
    if n <= 1 {
        return false;
    }
    for i in 2..=(n as f64).sqrt() as u64 {
        if n % i == 0 {
            return false;
        }
    }
    true
}

fn in_degree_by_mod(mut a: u64, mut b: u64, m: u64) -> u64 {
    let mut result = 1;
    a %= m;
    while b > 0 {
        if b % 2 == 1 {
            result = (result * a) % m;
        }
        b >>= 1;
        a = (a * a) % m;
    }
    result
}

fn find_g(p: u64) -> u64 {
    if !is_prime(p) {
        println!("Число p не является простым!");
        return 0;
    }

    let mut rng = rand::thread_rng();
    let mut g_rand = rng.gen_range(1..p);

    loop {
        let mut prim_sqrt = true;

        for i in 2..p - 1 {
            if in_degree_by_mod(g_rand, i, p) == 1 {
                prim_sqrt = false;
                break;
            }
        }

        if prim_sqrt {
            return g_rand;
        }

        g_rand = rng.gen_range(1..p);
    }
}

fn gen_sec_key(n: u64) -> u64 {
    let mut rng = rand::thread_rng();
    rng.gen_range(1..n)
}

fn generate_public_key(p: u64, g: u64, x: u64) -> (u64, u64) {
    let y = in_degree_by_mod(g, x, p);
    (p, y)
}

fn for_encrypt(m: u64, p: u64, g: u64, y: u64) -> (u64, u64) {
    let mut rng = rand::thread_rng();
    let k = rng.gen_range(1..p);
    let c1 = in_degree_by_mod(g, k, p);
    let c2 = (m * in_degree_by_mod(y, k, p)) % p;
    (c1, c2)
}

fn decrypt(txt_encrypt: (u64, u64), p: u64, x: u64) -> u64 {
    let c1 = txt_encrypt.0;
    let c2 = txt_encrypt.1;
    (c2 * in_degree_by_mod(c1, p - 1 - x, p)) % p
}

fn main() {
    println!("Выберите действие:");
    println!("1. Зашифровать сообщение");
    println!("2. Расшифровать сообщение");
    println!("Ваш выбор: ");

    let mut choice = String::new();
    io::stdin().read_line(&mut choice).expect("Не удалось прочитать строку");
    let choice: u32 = choice.trim().parse().expect("Введите число");

    if choice == 1 {
        println!("Введите простое число p: ");
        let mut p = String::new();
        io::stdin().read_line(&mut p).expect("Не удалось прочитать строку");
        let p: u64 = p.trim().parse().expect("Введите число");

        let g = find_g(p);
        if g == 0 {
            println!("Не найдено примитивного корня!");
            return;
        }

        println!("Найденный примитивный корень g: {}", g);

        let x = gen_sec_key(p - 1);
        println!("Секретный ключ x: {}", x);

        let public_key = generate_public_key(p, g, x);
        println!("Открытый ключ (p, g, y): ({}, {}, {})", public_key.0, g, public_key.1);

        println!("Введите сообщение m для шифрования: ");
        let mut m = String::new();
        io::stdin().read_line(&mut m).expect("Не удалось прочитать строку");
        let m: u64 = m.trim().parse().expect("Введите число");

        let txt_encrypt = for_encrypt(m, public_key.0, g, public_key.1);
        println!("Шифртекст (c1, c2): ({}, {})", txt_encrypt.0, txt_encrypt.1);
    } else if choice == 2 {
        println!("Введите закрытый ключ x: ");
        let mut x = String::new();
        io::stdin().read_line(&mut x).expect("Не удалось прочитать строку");
        let x: u64 = x.trim().parse().expect("Введите число");

        println!("Введите простое число p: ");
        let mut p = String::new();
        io::stdin().read_line(&mut p).expect("Не удалось прочитать строку");
        let p: u64 = p.trim().parse().expect("Введите число");

        println!("Введите примитивный корень g: ");
        let mut g = String::new();
        io::stdin().read_line(&mut g).expect("Не удалось прочитать строку");
        let g: u64 = g.trim().parse().expect("Введите число");

        println!("Введите шифртекст (c1, c2): ");
        let mut c1 = String::new();
        io::stdin().read_line(&mut c1).expect("Не удалось прочитать строку");
        let c1: u64 = c1.trim().parse().expect("Введите число");

        let mut c2 = String::new();
        io::stdin().read_line(&mut c2).expect("Не удалось прочитать строку");
        let c2: u64 = c2.trim().parse().expect("Введите число");

        let decr_msg = decrypt((c1, c2), p, x);
        println!("Расшифрованное сообщение: {}", decr_msg);
    } else {
        println!("Неверный выбор. Пожалуйста, выберите 1 или 2.");
    }
}