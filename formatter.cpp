#include "formatter.h"

#include <map>
#include <stdexcept>
#include <vector>

static const size_t MAX_OUTPUT_LENGTH = 100000;

QString BaseFormatter::format(const BigFraction& fraction, int base) {
    if (base < 2 || base > 500) {
        throw std::invalid_argument("Ошибка: основание должно быть от 2 до 500.");
    }

    BigInteger integerPart = fraction.integerPart();
    BigInteger remainder = fraction.remainder();
    BigInteger denominator = fraction.denominator();

    QString result = integerToBase(integerPart, base);

    if (remainder.isZero()) {
        return result;
    }

    result += ".";

    std::map<BigInteger, size_t> seen;
    std::vector<int> fractionDigits;

    while (!remainder.isZero()) {
        if (result.size() > static_cast<int>(MAX_OUTPUT_LENGTH)) {
            result += "...";
            result += "\nПолная запись результата слишком длинная. Показаны первые 100000 символов.";
            return result;
        }

        if (seen.find(remainder) != seen.end()) {
            size_t periodStart = seen[remainder];

            QString finalResult = integerToBase(integerPart, base);
            finalResult += ".";

            for (size_t i = 0; i < fractionDigits.size(); ++i) {
                if (i == periodStart) {
                    finalResult += "(";
                }

                finalResult += digitToString(fractionDigits[i]);
            }

            finalResult += ")";

            return finalResult;
        }

        seen[remainder] = fractionDigits.size();

        remainder = remainder.multiplyByInt(base);

        BigInteger digitBig = remainder / denominator;
        remainder = remainder % denominator;

        int digit = digitBig.divideByInt(1000000000);
        if (!digitBig.isZero()) {
            throw std::invalid_argument("Ошибка: внутренняя ошибка форматирования цифры.");
        }

        fractionDigits.push_back(digit);
        result += digitToString(digit);
    }

    return result;
}

QString BaseFormatter::integerToBase(BigInteger value, int base) {
    if (value.isZero()) {
        return "0";
    }

    std::vector<int> digits;

    while (!value.isZero()) {
        int remainder = value.divideByInt(base);
        digits.push_back(remainder);
    }

    QString result;

    for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
        result += digitToString(digits[i]);
    }

    return result;
}

QString BaseFormatter::digitToString(int digit) {
    if (digit < 0) {
        throw std::invalid_argument("Ошибка: отрицательная цифра.");
    }

    if (digit <= 9) {
        return QString(QChar('0' + digit));
    }

    if (digit <= 35) {
        return QString(QChar('A' + digit - 10));
    }

    return "[" + QString::number(digit) + "]";
}