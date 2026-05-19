#pragma once
#ifndef PARSER_H
#define PARSER_H
#include "bigfraction.h"
#include <QString>
#include <vector>

struct ParsedNumber {
    std::vector<int> integerDigits;
    std::vector<int> fractionDigits;
    std::vector<int> periodDigits;
};

class BaseParser {
public:
    static ParsedNumber parseToDigits(const QString& input, int base);
    static BigFraction parseToFraction(const QString& input, int base);

private:
    static int readDigit(const QString& input, int& pos, int base);
    static BigInteger digitsToInteger(const std::vector<int>& digits, int base);
    static BigInteger power(BigInteger value, int degree);
};

#endif // PARSER_H
