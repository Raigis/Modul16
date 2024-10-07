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
#include <sstream>

int main()
{
    std::string buffer;
    while(true){
        std::cout << "Enter an arithmetic expression or \"E\"/\"e\" to exit:\n";
        std::cin >> buffer;
        if (buffer == "E" || buffer == "e") return 0;
        double a, b;
        char oper;
        std::stringstream bufferStream (buffer);
        bufferStream >> a >> oper >> b;
        switch(oper){
            case '+': 
                std::cout << "Result: " << a+b;
                break;
            case '-': 
                std::cout << "Result: " << a-b;
                break;
            case '*': 
                std::cout << "Result: " << a*b;
                break;
            case '/': 
                std::cout << "Result: " << a/b;
                break;
            default:
                std::cout << "Incorrect input.";
        }
        std::cout << "\n";
    }
}