#include "converter.h"

QString BaseConverter::convert(const QString& input, int fromBase, int toBase) {
    return "input = " + input + "\n"
        "p = " + QString::number(fromBase) + "\n"
        "q = " + QString::number(toBase);
}