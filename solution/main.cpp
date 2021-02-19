#include <iostream>
#include "unsigned_ultra_long.h"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);


    std::string num1, num2;
    char c;
    auto long_num3 = new uul;
    while (std::cin >> num1 >> num2 >> c) {
        uul long_num1(num1);
        uul long_num2(num2);
        switch (c) {
            case '+':
                std::cout << (long_num1 += long_num2) << '\n';
                break;
            case '-':
                std::cout << (long_num1 -= long_num2) << '\n';
                break;
            case '*':
                *long_num3 = long_num1 * long_num2;
                std::cout << *long_num3 << '\n';
                break;
            case '^':
                *long_num3 = long_num1 ^ long_num2;
                std::cout << *long_num3 << '\n';
                break;
            case '/':
                *long_num3 = long_num1 / long_num2;
                std::cout << *long_num3 << '\n';
                break;
            case '>':
                std::cout << (long_num1 > long_num2 ? "true" : "false") << '\n';
                break;
            case '<':
                std::cout << (long_num1 < long_num2 ? "true" : "false") << '\n';
                break;
            case '=':
                std::cout << (long_num1 == long_num2 ? "true" : "false") << '\n';
                break;
            default:
                std::cout << "input error\n";
                return -1;
        }
    }
    delete long_num3;
    return 0;
}