//
// Created by iliya on 06.05.2025.
//

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <string>

class BigInteger {
public:
    BigInteger(const std::string& s);
    BigInteger() : BigInteger("0") {};
    std::string toString() const;

    BigInteger operator+(const BigInteger& other) const;
    BigInteger operator-(const BigInteger& other) const;
    BigInteger operator*(const BigInteger& other) const;
    BigInteger operator/(const BigInteger& other) const;
    BigInteger operator%(const BigInteger& other) const;

    BigInteger operator+() const;
    BigInteger operator-() const;

    bool operator==(const BigInteger& other) const;
    bool operator!=(const BigInteger& other) const;
    bool operator<(const BigInteger& other) const;
    bool operator>(const BigInteger& other) const;
    bool operator<=(const BigInteger& other) const;
    bool operator>=(const BigInteger& other) const;

    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);

    BigInteger& operator=(const BigInteger& other);
    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);
    BigInteger& operator*=(const BigInteger& other);
    BigInteger& operator/=(const BigInteger& other);
    BigInteger& operator%=(const BigInteger& other);

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& bi);
    friend std::istream& operator>>(std::istream& is, BigInteger& bi);

private:
    bool sign;
    std::string value;

    BigInteger(const bool sign, const std::string& s) : sign(sign), value(s) {};

    BigInteger add(const BigInteger& other) const;
    BigInteger subtract(const BigInteger& other) const;
    BigInteger multiply(const BigInteger& other) const;
    BigInteger divide(const BigInteger& other) const;
    BigInteger mod(const BigInteger& other) const;
    BigInteger abs() const;

    static std::string addStrings(const std::string& a, const std::string& b);
    static std::string subtractStrings(const std::string& a, const std::string& b);
    static std::string multiplyStringByDigit(const std::string& a, int d);
    static std::string multiplyStrings(const std::string& a, const std::string& b);
    static std::pair<std::string, std::string> dividePositive(const std::string& a, const std::string& b);
    static int compareValues(const std::string& a, const std::string& b);
};

#endif // BIGINTEGER_H
