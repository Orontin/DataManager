#ifndef TWOFACTOR_H
#define TWOFACTOR_H

#include <QString>

#include "abstract.h"

class Twofactors;

struct Twofactor: public Abstract {
    Twofactor() :
        Abstract(),
        id(0),
        twofactor(),
        twofactors(nullptr)
    {}

    QByteArray getData() const override
    {
        return this->twofactor;
    };

    unsigned int id;
    QByteArray twofactor;

    Twofactors *twofactors;
};

#endif // TWOFACTOR_H
