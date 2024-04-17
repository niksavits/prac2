use std::io;

fn last_num(mut num: u32, mut degree: u32) -> u32 {
    if degree == 0 {
        return 1; // Любое число в степени 0 равно 1
    }

    num %= 10; // Переводим основание в единицы

    // Находим остаток от деления на 4, т.к. период длины 4 для последних цифр возведений чисел в степень
    let ostatok = degree % 4;
    let mut ostatok = if ostatok == 0 { 4 } else { ostatok }; // Корректируем для четырехстепенного цикла

    let mut result = 1;
    while ostatok > 0 {
        result = (result * num) % 10; // Находим последнюю цифру возведения числа в степень
        ostatok -= 1;
    }

    result
}

fn main() {
    println!("Введите число: ");
    let mut num = String::new();
    io::stdin().read_line(&mut num).expect("Не удалось прочитать строку");
    let num: u32 = num.trim().parse().expect("Введите число");

    println!("Введите первую степень: ");
    let mut degree1 = String::new();
    io::stdin().read_line(&mut degree1).expect("Не удалось прочитать строку");
    let degree1: u32 = degree1.trim().parse().expect("Введите число");

    println!("Введите вторую степень: ");
    let mut degree2 = String::new();
    io::stdin().read_line(&mut degree2).expect("Не удалось прочитать строку");
    let degree2: u32 = degree2.trim().parse().expect("Введите число");

    let finalDegree = last_num(degree1, degree2);
    let result = last_num(num, finalDegree);

    println!(
        "Последняя цифра числа { }^({ }^{ }) равна: { }",
        num, degree1, degree2, result
    );
}
