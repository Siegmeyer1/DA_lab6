#include <sstream>
#include "unsigned_ultra_long.h"

uul::uul(std::string& s) {
    for (long long i = s.length(); i > 0; i -= digits_in_base) {
        if (i < digits_in_base) {
            digits.push_back(atoi(s.substr(0,i).c_str()));
        } else {
            digits.push_back(atoi(s.substr(i-digits_in_base,digits_in_base).c_str()));
        }
    }
    /*while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }*/
    normalize();
}

void uul::normalize() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

std::ostream& operator<<(std::ostream & os, const uul& num) {
    if (num.errFlag) {
        os << "Error";
        return os;
    }
    os << (num.digits.empty() ? 0 : num.digits.back());
    //os.width(num.digits_in_base);
    os.fill('0');
    for (long long i = (long long)num.digits.size()-2; i >=0; --i) {
        os.width(num.digits_in_base);
        os << num.digits[i];
    }
    return os;
}

uul& operator+=(uul& left, uul& right) {
    int carry = 0;
    for (size_t i = 0; i < std::max(left.digits.size(), right.digits.size()) || carry; ++i) {
        if (i == left.digits.size()) left.digits.push_back(0);
        left.digits[i] += carry + (i < right.digits.size() ? right.digits[i] : 0);
        carry = left.digits[i] >= left.base;
        if (carry) left.digits[i] -= left.base;
    }
    return left;
}

bool operator>(const uul& left, const uul& right) {
    if (left.digits.size() < right.digits.size()) return false;
    if (left.digits.size() > right.digits.size()) return true;
    for (int i = (int)left.digits.size()-1; i >= 0; --i) {
        if (left.digits[i] > right.digits[i]) return true;
        if (left.digits[i] < right.digits[i]) return false;
    }
    return false;
}

bool operator<(uul& left, uul& right) {
    if (left.digits.size() > right.digits.size()) return false;
    if (left.digits.size() < right.digits.size()) return true;
    for (int i = (int)left.digits.size()-1; i >= 0; --i) {
        if (left.digits[i] < right.digits[i]) return true;
        if (left.digits[i] > right.digits[i]) return false;
    }
    return false;
}

bool operator==(uul& left, uul& right) {
    if (left.digits.size() != right.digits.size()) return false;
    for (int i = (int)left.digits.size()-1; i >= 0; --i) {
        if (left.digits[i] != right.digits[i]) return false;
    }
    return true;
}

bool operator==(uul& left, int right) {
    std::stringstream ss;
    ss << right;
    std::string str = ss.str();
    uul b(str);
    if (left.digits.size() != b.digits.size()) return false;
    for (int i = (int)left.digits.size()-1; i >= 0; --i) {
        if (left.digits[i] != b.digits[i]) return false;
    }
    return true;
}

uul& operator-=(uul& left, const uul& right) {
    if (right > left) {
        left.errFlag = true;
        return left;
    }
    int carry = 0;
    for (size_t i = 0; i < right.digits.size() || carry; ++i) {
        left.digits[i] -= carry + (i < right.digits.size() ? right.digits[i] : 0);
        carry = left.digits[i] < 0;
        if (carry) left.digits[i] += left.base;
    }
    while (left.digits.size() > 1 && left.digits.back() == 0) {
        left.digits.pop_back();
    }
    return left;
}

uul operator*(uul& left, uul& right) {
    //auto result = new uul;
    uul result;
    result.digits.resize(left.digits.size() + right.digits.size());

    for (size_t i = 0; i < left.digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right.digits.size() || carry != 0; ++j) {
            long long tmp = result.digits[i + j] + carry + (long long)left.digits[i] * (long long)(j < right.digits.size() ? right.digits[j] : 0);
            carry = static_cast<int>(tmp / left.base);
            result.digits[i+j] = static_cast<int>(tmp % left.base);
        }
    }

    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }
    return result;
}

uul& operator*=(uul& left, uul& right) {
    auto result = new uul;
    result->digits.resize(left.digits.size() + right.digits.size());

    for (size_t i = 0; i < left.digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right.digits.size() || carry != 0; ++j) {
            long long tmp = result->digits[i + j] + carry + (long long)left.digits[i] * (long long)(j < right.digits.size() ? right.digits[j] : 0);
            carry = static_cast<int>(tmp / left.base);
            result->digits[i+j] = static_cast<int>(tmp % left.base);
        }
    }

    while (result->digits.size() > 1 && result->digits.back() == 0) {
        result->digits.pop_back();
    }
    left = *result;
    delete result;
    left.normalize();
    return left;
}

uul operator*(uul& left, int right) {
    uul result;
    result.digits.resize(left.digits.size() + (right / left.base) + 1);
    int carry = 0;
    for (size_t i = 0; i < left.digits.size() || carry != 0; ++i) {
        long long tmp = carry + (long long) ( i < left.digits.size() ? left.digits[i] : 0) * (long long)right;
        carry = static_cast<int>(tmp / left.base);
        result.digits[i] = static_cast<int>(tmp % left.base);
    }
    result.normalize();
    return result;
}

void uul::shift_right() {
    if (digits.empty()) {
        digits.push_back(0);
        return;
    }
    digits.push_back(digits[digits.size()-1]);
    for (size_t i = digits.size() - 2; i > 0; --i)
        digits[i] = digits[i-1];
    digits[0] = 0;
}

uul operator/(uul& left, uul& right) {
    //auto result = new uul;
    uul result;
    //auto current = new uul;
    uul current;
    if (right == 0) {
        result.errFlag = true;
        return result;
    }
    result.digits.resize(left.digits.size());
    for (long long i = static_cast<long long>(left.digits.size())-1; i >= 0; --i) {
        current.shift_right();
        current.digits[0] = left.digits[i];
        current.normalize();
        int x = 0, l = 0, r = current.base;
        while (l <= r) {
            int m = (l + r) / 2;
            uul t = right * m;
            if (!(t > current)) {
                x = m;
                l = m + 1;
            } else r = m - 1;
        }
        result.digits[i] = x;
        current -= (right * x);
    }
    result.normalize();
    return result;
}

uul operator^(uul& left, uul& right) {
    //auto res = new uul;
    uul res;
    if (left == 0 && right == 0) {
        res.errFlag=true;
        return res;
    }
    std::string _one("1");
    uul one(_one);
    std::string _two("2");
    uul two(_two);
    res.digits.push_back(1);
    while (!(right == 0)) {
        if (right.digits[0] % 2 == 1) {
            //*res = *res * left; //fucked
            res *= left;
            right -= one;
        } else {
            left *= left;
            right = right / two;
        }
    }
    res.normalize();
    return res;
}

