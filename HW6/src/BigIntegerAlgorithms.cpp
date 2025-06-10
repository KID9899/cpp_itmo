//
// Created by iliya on 06.05.2025.
//

#include "BigInteger.h"
#include <algorithm>
#include <stdexcept>

BigInteger::BigInteger(const std::string& s) {
    if (s.empty()) {
        sign = true;
        value = "0";
        return;
    }
    size_t start = 0;
    if (s[0] == '-') {
        sign = false;
        start = 1;
    } else {
        sign = true;
    }
    while (start < s.size() && s[start] == '0') start++;
    if (start == s.size()) {
        sign = true;
        value = "0";
    } else {
        value = s.substr(start);
    }
    for (char c : value) {
        if (!isdigit(c)) throw std::invalid_argument("Invalid number");
    }
}

std::string BigInteger::toString() const {
    if (value == "0") return "0";
    return sign ? value : "-" + value;
}

int BigInteger::compareValues(const std::string& a, const std::string& b) {
    if (a.length() < b.length()) return -1;
    if (a.length() > b.length()) return 1;
    return a.compare(b);
}

std::string BigInteger::addStrings(const std::string& a, const std::string& b) {
    std::string result;
    result.reserve(std::max(a.size(), b.size()) + 1);
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string BigInteger::subtractStrings(const std::string& a, const std::string& b) {
    std::string result;
    result.reserve(a.size());
    int borrow = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
    while (i >= 0 || j >= 0 || borrow) {
        int diff = borrow;
        if (i >= 0) diff += a[i--] - '0';
        if (j >= 0) diff -= b[j--] - '0';
        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }
        result.push_back(diff + '0');
    }
    std::reverse(result.begin(), result.end());
    size_t start = result.find_first_not_of('0');
    if (start == std::string::npos) return "0";
    return result.substr(start);
}

std::string BigInteger::multiplyStringByDigit(const std::string& a, int d) {
    if (d == 0) return "0";
    std::string result;
    result.reserve(a.size() + 1);
    int carry = 0;
    for (int i = a.size() - 1; i >= 0; --i) {
        int prod = (a[i] - '0') * d + carry;
        carry = prod / 10;
        result.push_back(prod % 10 + '0');
    }
    if (carry) result.push_back(carry + '0');
    std::reverse(result.begin(), result.end());
    return result;
}

std::string BigInteger::multiplyStrings(const std::string& a, const std::string& b) {
    std::string result = "0";
    result.reserve(a.size() + b.size());
    for (size_t i = 0; i < b.size(); ++i) {
        int digit = b[b.size() - 1 - i] - '0';
        std::string temp = multiplyStringByDigit(a, digit);
        temp.append(i, '0');
        result = addStrings(result, temp);
    }
    return result;
}

std::pair<std::string, std::string> BigInteger::dividePositive(const std::string& a, const std::string& b) {
    if (b == "0") throw std::invalid_argument("Division by zero");
    if (compareValues(a, b) < 0) return {"0", a};
    std::string q = "";
    q.reserve(a.size());
    std::string r = "";
    for (char c : a) {
        r += c;
        while (r.size() > 1 && r[0] == '0') r.erase(0, 1);
        int k = 0;
        while (compareValues(multiplyStringByDigit(b, k + 1), r) <= 0 && k < 9) k++;
        q += char('0' + k);
        if (k > 0) r = subtractStrings(r, multiplyStringByDigit(b, k));
    }
    size_t start = q.find_first_not_of('0');
    if (start == std::string::npos) q = "0";
    else q = q.substr(start);
    return {q, r};
}

BigInteger BigInteger::add(const BigInteger& other) const {
    if (sign == other.sign) {
        return BigInteger(sign, addStrings(value, other.value));
    }
    int cmp = compareValues(value, other.value);
    if (cmp > 0) {
        return BigInteger(sign, subtractStrings(value, other.value));
    } else if (cmp < 0) {
        return BigInteger(other.sign, subtractStrings(other.value, value));
    } else {
        return BigInteger(true, "0");
    }
}

BigInteger BigInteger::subtract(const BigInteger& other) const {
    return add(BigInteger(!other.sign, other.value));
}

BigInteger BigInteger::multiply(const BigInteger& other) const {
    std::string prod = multiplyStrings(value, other.value);
    return BigInteger(sign == other.sign, prod);
}

BigInteger BigInteger::divide(const BigInteger& other) const {
    if (other.value == "0") throw std::invalid_argument("Division by zero");
    if (value == "0") return BigInteger(true, "0");
    return BigInteger(sign == other.sign, dividePositive(value, other.value).first);
}

BigInteger BigInteger::mod(const BigInteger& other) const {
    if (other.value == "0") throw std::invalid_argument("Division by zero");
    if (value == "0") return BigInteger(true, "0");
    BigInteger res = BigInteger(sign, dividePositive(value, other.value).second);
    return res;
}

BigInteger BigInteger::abs() const {
    return BigInteger(true, value);
}