//
// Created by iliya on 06.05.2025.
//

#include "BigInteger.h"
#include <string>
#include <iostream>

BigInteger BigInteger::operator+(const BigInteger& other) const {
    return add(other);
}

BigInteger BigInteger::operator-(const BigInteger& other) const {
    return subtract(other);
}

BigInteger BigInteger::operator*(const BigInteger& other) const {
    return multiply(other);
}

BigInteger BigInteger::operator/(const BigInteger& other) const {
    return divide(other);
}

BigInteger BigInteger::operator%(const BigInteger& other) const {
    return mod(other);
}

BigInteger BigInteger::operator+() const {
    return *this;
}

BigInteger BigInteger::operator-() const {
    if (value == "0") return *this;
    return BigInteger(!sign, value);
}

bool BigInteger::operator==(const BigInteger& other) const {
    return sign == other.sign && value == other.value;
}

bool BigInteger::operator!=(const BigInteger& other) const {
    return !(*this == other);
}

bool BigInteger::operator<(const BigInteger& other) const {
    if (sign != other.sign) return !sign;
    if (sign) {
        return compareValues(value, other.value) < 0;
    } else {
        return compareValues(value, other.value) > 0;
    }
}

bool BigInteger::operator>(const BigInteger& other) const {
    return other < *this;
}

bool BigInteger::operator<=(const BigInteger& other) const {
    return !(*this > other);
}

bool BigInteger::operator>=(const BigInteger& other) const {
    return !(*this < other);
}

BigInteger& BigInteger::operator++() {
    *this = add(BigInteger("1"));
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger temp = *this;
    *this = add(BigInteger("1"));
    return temp;
}

BigInteger& BigInteger::operator--() {
    *this = subtract(BigInteger("1"));
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger temp = *this;
    *this = subtract(BigInteger("1"));
    return temp;
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
    if (this != &other) {
        sign = other.sign;
        value = other.value;
    }
    return *this;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
    *this = add(other);
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
    *this = subtract(other);
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
    *this = multiply(other);
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
    *this = divide(other);
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
    *this = mod(other);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& bi) {
    os << bi.toString();
    return os;
}

std::istream& operator>>(std::istream& is, BigInteger& bi) {
    std::string s;
    is >> s;
    bi = BigInteger(s);
    return is;
}
