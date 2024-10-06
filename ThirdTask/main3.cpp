/*
Создайте небольшую программу для вычисления простых действий с числами.
При запуске программа ожидает пользовательского ввода во временную переменную строку.
После ввода строки она распарсивается на отдельные члены.
Строка записывается в форме “<число-1><действие><число-2>” (без пробелов).
Оба числа — это значения с плавающей точкой, повышенной точности (double).
Действие может быть одним из: +, −, /, *.
Результат действия выводится в стандартный вывод cout.
*/

#include <iostream>

int main()
{
    std::string temp;
    std::cout << "Enter the command:\n";
    std::cin >> temp;
    const std::string buffer = temp;
    std::string a, b;
    std::string oper;
    std::stringstream bufferStream(buffer);
    bufferStream >> a >> oper >> b;
    std::cout << a << oper << b;
}