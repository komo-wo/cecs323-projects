// Katherine Kim
// Class (CECS 325-01)
// Project Name (Prog 7 – BigInt)
// Due Date (12/06/2023)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include "BigInt.h"

using namespace std;

BigInt::BigInt() {
    v.push_back(0); // default constructor - initialize with 0
}

BigInt::BigInt(int num) {
    while (num > 0) {
        v.push_back(num % 10);
        num /= 10;
    }
    if (v.empty()) {
        v.push_back(0);
    }
}

BigInt::BigInt(string str) {
    for (int i = str.length() - 1; i >= 0; --i) {
        if (isdigit(str[i])) {
            v.push_back(str[i] - '0');
        }
    }
    if (v.empty()) {
        v.push_back(0);
    }
}

int BigInt::operator[](int index) const{
    if (index < 0 || index >= size()) {
        throw string("index out of range");
    }
    return v[index];
}

int BigInt::size() const{
    return v.size();
}

BigInt BigInt::operator+(BigInt other) {
    BigInt result;
    int carry = 0;
    int maxSize = max(size(), other.size());

    for (int i = 0; i < maxSize || carry; ++i) {
        if (i == size()) {
            result.v.push_back(0);
        }
        int sum = carry + (i < size() ? v[i] : 0) + (i < other.size() ? other.v[i] : 0);
        result.v[i] = sum % 10;
        carry = sum / 10;
    }
    return result;
}

BigInt BigInt::operator++() {
    *this = *this + BigInt(1);
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt temp = *this;
    ++(*this);
    return temp;
}

BigInt BigInt::operator*(BigInt other) {
    BigInt result;

    for (int i = 0; i < size(); ++i) {
        result = result + *this;
        }
    return result;
}

BigInt BigInt::half() {
    BigInt result;
    int carry = 0;

    auto it = v.rbegin(); // Start from the reversed vector

    while (it != v.rend()) {
        int curDigit = *it + carry * 10;
        result.v.insert(result.v.begin(), curDigit / 2);
        carry = curDigit % 2;
        ++it;
    }

    while (result.size() > 1 && result.v.front() == 0) {
        result.v.erase(result.v.begin());
    }

    return result;
}


bool BigInt::isOdd() {
    return v[0] % 2 != 0;
}

bool BigInt::isEven() {
    return !isOdd();
}

bool BigInt::operator==(BigInt other) {
    return v == other.v;
}

bool BigInt::operator<(BigInt other) {
    if (size() != other.size()) {
        return size() < other.size();
    }
    for (int i = size() - 1; i >= 0; --i) {
        if (v[i] != other.v[i]) {
            return v[i] < other.v[i];
        }
    }
    return false;
}

ostream& operator<<(ostream& os, const BigInt& bigint) {
    if (bigint.size() <= 8) {
        for (int i = bigint.size() - 1; i >= 0; --i) {
            os << bigint[i];
        }
    } else {
        os << bigint[bigint.size() - 1] << '.';
        for (int i = 1; i < 8 && i < bigint.size(); ++i) {
            os << bigint[bigint.size() - 1 - i];
        }
        os << 'e' << bigint.size() - 1;
    }
    return os;
}
