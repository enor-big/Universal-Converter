#pragma once

#include "bigfraction.h"

#include <QString>

class BaseFormatter {
public:
    static QString format(const BigFraction& fraction, int base);

private:
    static QString digitToString(int digit);
    static QString integerToBase(BigInteger value, int base);
};