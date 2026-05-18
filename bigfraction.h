#ifndef BIGFRACTION_H
#define BIGFRACTION_H
#include "biginteger.h"

class BigFraction
{
public:
    BigFraction();
    BigFraction(const BigInteger& numerator,
                const BigInteger& denominator);
    BigInteger integerPart() const;
    BigInteger remainder() const;
    BigInteger numerator() const;
    BigInteger denominator() const;

    friend BigFraction operator+(const BigFraction& left,
                                 const BigFraction& right);

    friend BigFraction operator-(const BigFraction& left,
                                 const BigFraction& right);

    friend BigFraction operator*(const BigFraction& left,
                                 const BigFraction& right);

    friend BigFraction operator/(const BigFraction& left,
                                 const BigFraction& right);
private:
    BigInteger numerator_;
    BigInteger denominator_;

    void reduce();
};

#endif // BIGFRACTION_H
