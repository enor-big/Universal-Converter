#pragma once
#ifndef CONVERTER_H
#define CONVERTER_H

#endif // CONVERTER_H

#include <QString>

class BaseConverter{
public:
    static QString convert(const QString& input, int fromBase, int toBase );
};
