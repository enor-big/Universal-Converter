#pragma once
#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include <string>
#include <vector>

class BigInteger
{
public:
    BigInteger();
    BigInteger(unsigned long long value);
    BigInteger(const std::string& value);

    std::string toString() const;
    bool isZero() const;

    friend bool operator<(const BigInteger& left,const BigInteger& right);
    friend bool operator==(const BigInteger& left,const BigInteger& right);
    friend bool operator!=(const BigInteger& left,const BigInteger& right);
    friend bool operator<=(const BigInteger& left,const BigInteger& right);
    friend bool operator>(const BigInteger& left,const BigInteger& right);
    friend bool operator>=(const BigInteger& left,const BigInteger& right);
    friend BigInteger operator+(const BigInteger& left,const BigInteger& right);
    friend BigInteger operator-(const BigInteger& left,const BigInteger& right);
    friend BigInteger operator*(const BigInteger& left, const BigInteger& right);


    BigInteger multiplyByInt(int value) const;
    int divideByInt(int value);
private:
    static const int Base = 1000000000;
    static const int BaseDigits = 9;
    std::vector<int> digits_;
    void removeLeadingZeros();
};

#endif // BIGINTEGER_H
