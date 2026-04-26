#ifndef TELEPHONE_H
#define TELEPHONE_H

#include <QString>

#include "abstract.h"

class Telephones;

struct Telephone: public Abstract {
    Telephone() :
        Abstract(),
        id(0),
        telephone(),
        telephones(nullptr)
    {}

    QByteArray getData() const override
    {
        return this->telephone;
    };

    unsigned int id;
    QByteArray telephone;

    Telephones *telephones;
};

#endif // TELEPHONE_H
