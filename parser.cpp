#include "parser.h"
#include <stdexcept>

ParsedNumber BaseParser::parseToDigits(const QString& input, int base) {
    if (base < 2 || base > 500) {
        throw std::invalid_argument("Ошибка: основание должно быть от 2 до 500.");
    }

    if (input.isEmpty()) {
        throw std::invalid_argument("Ошибка: входная строка пуста.");
    }

    ParsedNumber result;

    bool hasPoint = false;
    bool hasPeriod = false;
    bool periodClosed = false;

    int pos = 0;

    while (pos < input.size()) {
        QChar ch = input[pos];

        if (ch == '.') {
            if (hasPoint) {
                throw std::invalid_argument("Ошибка: более одной точки.");
            }

            if (result.integerDigits.empty()) {
                throw std::invalid_argument("Ошибка: отсутствует целая часть.");
            }

            hasPoint = true;
            ++pos;
            continue;
        }

        if (ch == '(') {
            if (!hasPoint) {
                throw std::invalid_argument("Ошибка: период возможен только после точки.");
            }

            if (hasPeriod) {
                throw std::invalid_argument("Ошибка: более одного периода.");
            }

            hasPeriod = true;
            ++pos;
            continue;
        }

        if (ch == ')') {
            if (!hasPeriod) {
                throw std::invalid_argument("Ошибка: лишняя закрывающая скобка периода.");
            }

            if (result.periodDigits.empty()) {
                throw std::invalid_argument("Ошибка: период не может быть пустым.");
            }

            periodClosed = true;
            ++pos;

            if (pos != input.size()) {
                throw std::invalid_argument("Ошибка: после закрывающей скобки периода не должно быть других символов.");
            }

            break;
        }

        if (periodClosed) {
            throw std::invalid_argument("Ошибка: после закрывающей скобки периода не должно быть других символов.");
        }

        int digit = readDigit(input, pos, base);

        if (!hasPoint) {
            result.integerDigits.push_back(digit);
        } else if (hasPeriod) {
            result.periodDigits.push_back(digit);
        } else {
            result.fractionDigits.push_back(digit);
        }
    }

    if (hasPoint && result.fractionDigits.empty() && !hasPeriod) {
        throw std::invalid_argument("Ошибка: отсутствует дробная часть после точки.");
    }

    if (hasPeriod && !periodClosed) {
        throw std::invalid_argument("Ошибка: не закрыта скобка периода.");
    }

    if (result.integerDigits.empty()) {
        throw std::invalid_argument("Ошибка: отсутствует целая часть.");
    }

    return result;
}

int BaseParser::readDigit(const QString& input, int& pos, int base) {
    QChar ch = input[pos];

    int digit = -1;

    if (ch >= '0' && ch <= '9') {
        digit = ch.unicode() - '0';
        ++pos;
    } else if (ch >= 'A' && ch <= 'Z') {
        digit = ch.unicode() - 'A' + 10;
        ++pos;
    } else if (ch >= 'a' && ch <= 'z') {
        digit = ch.unicode() - 'a' + 10;
        ++pos;
    } else if (ch == '[') {
        ++pos;

        if (pos >= input.size()) {
            throw std::invalid_argument(
                "Ошибка: не закрыта квадратная скобка."
                );
        }

        QString number;

        while (pos < input.size() && input[pos] != ']') {
            number.push_back(input[pos]);
            ++pos;
        }

        if (pos >= input.size() || input[pos] != ']') {
            throw std::invalid_argument(
                "Ошибка: не закрыта квадратная скобка."
                );
        }

        if (number.isEmpty()) {
            throw std::invalid_argument(
                "Ошибка: пустые квадратные скобки."
                );
        }

        bool onlyDigits = true;

        for (QChar current : number) {
            if (current < '0' || current > '9') {
                onlyDigits = false;
                break;
            }
        }

        if (onlyDigits) {
            digit = number.toInt();
        } else {
            if (number.size() != 1) {
                throw std::invalid_argument(
                    "Ошибка: некорректная запись цифры."
                    );
            }

            QChar current = number[0];

            if (current >= 'A' && current <= 'Z') {
                digit = current.unicode() - 'A' + 10;
            } else if (current >= 'a' && current <= 'z') {
                digit = current.unicode() - 'a' + 10;
            } else {
                throw std::invalid_argument(
                    "Ошибка: некорректная запись цифры."
                    );
            }
        }

        ++pos;
    }

    else {
        throw std::invalid_argument("Ошибка: недопустимый символ во входной строке.");
    }

    if (digit >= base) {
        throw std::invalid_argument("Ошибка: цифра недопустима в данной системе счисления.");
    }

    return digit;
}

BigInteger BaseParser::digitsToInteger(const std::vector<int>& digits,
                                       int base) {
    BigInteger result(0);

    for (size_t i = 0; i < digits.size(); ++i) {
        result = result.multiplyByInt(base);
        result = result + BigInteger(digits[i]);
    }

    return result;
}

BigInteger BaseParser::power(BigInteger value, int degree) {
    BigInteger result(1);

    for (int i = 0; i < degree; ++i) {
        result = result * value;
    }

    return result;
}

BigFraction BaseParser::parseToFraction(const QString& input, int base) {
    ParsedNumber parsed = parseToDigits(input, base);

    BigInteger integerPart =
        digitsToInteger(parsed.integerDigits, base);

    BigInteger fractionPart =
        digitsToInteger(parsed.fractionDigits, base);

    BigInteger periodPart =
        digitsToInteger(parsed.periodDigits, base);

    int k = static_cast<int>(parsed.fractionDigits.size());
    int m = static_cast<int>(parsed.periodDigits.size());

    BigInteger baseBig(base);
    BigInteger pk = power(baseBig, k);

    if (m == 0) {
        BigInteger numerator =
            integerPart * pk + fractionPart;

        BigInteger denominator = pk;

        return BigFraction(numerator, denominator);
    }

    BigInteger pm = power(baseBig, m);
    BigInteger periodDenominatorPart = pm - BigInteger(1);

    BigInteger denominator =
        pk * periodDenominatorPart;

    BigInteger numerator =
        integerPart * denominator +
        fractionPart * periodDenominatorPart +
        periodPart;

    return BigFraction(numerator, denominator);
}
