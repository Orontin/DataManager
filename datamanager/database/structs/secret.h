#ifndef SECRET_H
#define SECRET_H

#include <QString>

#include "abstract.h"

class Secrets;

struct Secret: public Abstract {
    Secret() :
        Abstract(),
        id(0),
        secret(),
        secrets(nullptr)
    {}

    QByteArray getData() const override
    {
        return this->secret;
    };

    unsigned int id;
    QByteArray secret;

    Secrets *secrets;
};

#endif // SECRET_H
