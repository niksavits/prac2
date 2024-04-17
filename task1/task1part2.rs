use std::io;

fn is_prime(n: u32) -> bool {
    if n <= 1 {
        return false;
    }
    let limit = (n as f64).sqrt() as u32;
    for i in 2..=limit {
        if n % i == 0 {
            return false;
        }
    }
    true
}

fn main() {
    println!("Введите основание: ");
    let mut a = String::new();
    io::stdin().read_line(&mut a).expect("Не удалось прочитать строку");
    let a: u32 = a.trim().parse().expect("Ожидалось целое число");

    println!("Введите модуль: ");
    let mut p = String::new();
    io::stdin().read_line(&mut p).expect("Не удалось прочитать строку");
    let p: u32 = p.trim().parse().expect("Ожидалось целое число");

    println!("Введите степень: ");
    let mut degree = String::new();
    io::stdin().read_line(&mut degree).expect("Не удалось прочитать строку");
    let degree: u32 = degree.trim().parse().expect("Ожидалось целое число");

    let mut result = 1;

    if is_prime(p) {
        if a % p == 0 {
            println!("Условие теоремы Ферма не выполнено!");
        } else {
            let log_degree = (degree as f64).log2() as usize;
            let mut j = log_degree;
            let mut binary = [0; 32];

            for i in (0..=log_degree).rev() {
                let bit = (degree >> i) & 1;
                binary[j] = bit;
                j = j.checked_sub(1).unwrap_or(0); // Исправление здесь
            }

            for i in (0..=log_degree).rev() {
                result = (result * result) % p;
                if binary[i] == 1 {
                    result = (result * a) % p;
                }
            }

            println!("Результат: {}", result);
        }
    } else {
        println!("Модуль не является простым числом!");
    }
}