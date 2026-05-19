#include "converter.h"
#include "parser.h"

#include <exception>

QString BaseConverter::convert(const QString& input,
                               int fromBase,
                               int toBase) {
    Q_UNUSED(toBase);

    try {
        BigFraction fraction = BaseParser::parseToFraction(input, fromBase);

        return "Parser works!\n\n"
               "Numerator:\n" +
               QString::fromStdString(fraction.numerator().toString()) +
               "\n\nDenominator:\n" +
               QString::fromStdString(fraction.denominator().toString());

    } catch (const std::exception& error) {
        return QString("ERROR:\n") + error.what();

    } catch (...) {
        return "ERROR:\nНеизвестная ошибка.";
    }
}