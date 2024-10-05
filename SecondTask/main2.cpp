/*
Напишите небольшую программу. Из целой и дробной частей числа, которые в отдельности вводит пользователь,
составьте новое число с плавающей точкой (типа double) и выведите это число обратно в консоль для проверки.
Целая часть — это часть числа, которая находится до точки (запятой), дробная — после.
*/

#include <iostream>

int main () {
    std::string integerPart, fractionalPart;
    std::cout << "Input the integer part of the number: ";
    std::cin >> integerPart;
    std::cout << "Input the fractional part of the number: ";
    std::cin >> fractionalPart;
    std::cout << "Number: " << std::stod((integerPart + "." + fractionalPart));
    return 0;
}