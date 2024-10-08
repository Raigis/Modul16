/*
Создайте упрощённую модель механического пианино.
У этого пианино семь клавиш, которые соответствуют семи нотам.
Каждая клавиша кодируется уникальной битовой маской, которая записывается в enum.
В начале программы пользователь вводит «аккорд», то есть строку с набором цифр от 1 до 7, например: 1234 или 63.

Далее нужно скомпоновать цифры «аккорда» в одну битовую маску, которую будет содержать переменная типа int, где каждый бит соответствует определённой ноте.
В этом случае, даже если при вводе будет введена одна и та же цифра (нота), она превратится только в один конкретный бит
(нельзя нажать на одну клавишу два раза, когда мы берём «аккорд»).
После того как битовая маска сформирована, программа осуществляет вывод нот из введённого «аккорда».
*/

#include <iostream>

enum note {
   DO = 1, RE = 2, MI = 4, FA = 8, SOL = 16, LA = 32, SI = 64
};

int main () {
   std::string chord;
   std::cout << "Enter the notes of the chord(1 - 7) :\n";
   std::cin >> chord;
   int notes = 0;
   for (char c : chord) {
      notes |= 1 << ((c - '0') - 1);
   }
   if (notes & DO) std::cout << "DO ";
   if (notes & RE) std::cout << "RE ";
   if (notes & MI) std::cout << "MI ";
   if (notes & FA) std::cout << "FA ";    
   if (notes & SOL) std::cout << "SOL ";
   if (notes & LA) std::cout << "LA ";
   if (notes & SI) std::cout << "SI ";
    
   return 0;
}