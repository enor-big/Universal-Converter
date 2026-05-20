#include "converter.h"
#include "parser.h"
#include "formatter.h"

#include <exception>

QString BaseConverter::convert(const QString& input,
                               int fromBase,
                               int toBase) {
    try {
        BigFraction fraction =
            BaseParser::parseToFraction(input, fromBase);

        return BaseFormatter::format(fraction, toBase);

    } catch (const std::exception& error) {
        return QString("ERROR:\n") + error.what();
    } catch (...) {
        return "ERROR:\nНеизвестная ошибка.";
    }
}