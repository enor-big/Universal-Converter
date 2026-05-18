#include "bigfraction.h"
#include "stdexcept"

BigFraction::BigFraction() :
    numerator_(0),
    denominator_(1){}

BigFraction::BigFraction(const BigInteger& numerator,
                         const BigInteger& denominator) :
    numerator_(numerator),
    denominator_(denominator) {
    if (denominator_.isZero()) {
        throw std::invalid_argument("Делитель 0");
    }
    reduce();
}

void BigFraction::reduce() {
    if (numerator_.isZero()){
        denominator_=BigInteger(1);
        return;
    }

    BigInteger curr = BigInteger::gcd(numerator_, denominator_);
    numerator_ = numerator_ / curr;
    denominator_ = denominator_ / curr;
}

BigInteger BigFraction::integerPart() const {
    return numerator_ / denominator_;
}

BigInteger BigFraction::remainder() const {
    return numerator_ % denominator_;
}

BigInteger BigFraction::numerator() const {
    return numerator_;
}

BigInteger BigFraction::denominator() const {
    return denominator_;
}

BigFraction operator+(const BigFraction& left,
                     const BigFraction& right){
    BigInteger numerator =
        left.numerator_ * right.denominator_ +
        right.numerator_ * left.denominator_;

    BigInteger denominator =
        left.denominator_ * right.denominator_;

    return BigFraction(numerator, denominator);

}

BigFraction operator-(const BigFraction& left,
                      const BigFraction& right) {
    BigInteger leftNumerator =
        left.numerator_ * right.denominator_;

    BigInteger rightNumerator =
        right.numerator_ * left.denominator_;

    if (leftNumerator < rightNumerator) {
        throw std::invalid_argument("Fraction subtraction result is negative");
    }

    BigInteger numerator = leftNumerator - rightNumerator;

    BigInteger denominator =
        left.denominator_ * right.denominator_;

    return BigFraction(numerator, denominator);
}

BigFraction operator*(const BigFraction& left,
                      const BigFraction& right) {
    BigInteger numerator =
        left.numerator_ * right.numerator_;

    BigInteger denominator =
        left.denominator_ * right.denominator_;

    return BigFraction(numerator, denominator);
}

BigFraction operator/(const BigFraction& left,
                      const BigFraction& right) {
    if (right.numerator_.isZero()) {
        throw std::invalid_argument("Division by zero fraction");
    }

    BigInteger numerator =
        left.numerator_ * right.denominator_;

    BigInteger denominator =
        left.denominator_ * right.numerator_;

    return BigFraction(numerator, denominator);
}