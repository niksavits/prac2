use std::io;

fn isPrime(n: u32) -> bool {
    if n <= 1 {
        return false;
    }
    for i in 2..=((n as f64).sqrt() as u32) {
        if n % i == 0 {
            return false;
        }
    }
    true
}

fn main() {
    println!("Введите основание:");
    let mut a = String::new();
    io::stdin().read_line(&mut a).expect("Ошибка при чтении ввода.");
    let a: u32 = a.trim().parse().expect("Введено некорректное значение.");

    println!("Введите модуль:");
    let mut p = String::new();
    io::stdin().read_line(&mut p).expect("Ошибка при чтении ввода.");
    let p: u32 = p.trim().parse().expect("Введено некорректное значение.");

    println!("Введите степень:");
    let mut degree = String::new();
    io::stdin().read_line(&mut degree).expect("Ошибка при чтении ввода.");
    let degree: u32 = degree.trim().parse().expect("Введено некорректное значение.");

    let mut result = 1;

    if isPrime(p) {
        if a % p == 0 {
            println!("Условие теоремы Ферма не выполнено!");
        } else {
            for _ in 1..= degree {
                result = (result * a) % p;
            }
            println!("Результат: { }", result);
        }
    } else {
        println!("Модуль не является простым числом!");
    }
}
