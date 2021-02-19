//
// Created by anri on 26.09.2020.
//

#ifndef DA_LAB6_UNSIGNED_ULTRA_LONG_H
#define DA_LAB6_UNSIGNED_ULTRA_LONG_H

#include <iostream>
#include <vector>

class uul {
public:
    uul() = default;
    uul(std::string& s);

    friend std::ostream& operator<<(std::ostream& os, const uul& num);
    friend uul& operator+=(uul& left, uul& right);
    friend bool operator>(const uul& left, const uul& right);
    friend bool operator<(uul& left, uul& right);
    friend bool operator==(uul& left, uul& right);
    friend bool operator==(uul& left, int right);
    friend uul& operator-=(uul& left, const uul& right);
    friend uul operator*(uul& left, uul& right);
    friend uul& operator*=(uul& left, uul& right);
    friend uul operator*(uul& left, int right);
    friend uul operator^(uul& left, uul& right);
    friend uul operator/(uul& left, uul& right);
    ~uul() = default;
private:
    void shift_right();
    void normalize();
    std::vector<int> digits;
    int base = 1000*1000*1000/*10000*/;
    int digits_in_base = 9;
    bool errFlag = false;
};

#endif //DA_LAB6_UNSIGNED_ULTRA_LONG_H
