#ifndef PASSWORD_H
#define PASSWORD_H

#include <QString>

#include "abstract.h"

#include "abstract.h"

class Passwords;

struct Password: public Abstract {
    Password() :
        Abstract(),
        id(0),
        password(),
        passwords(nullptr)
    {}

    QByteArray getData() const override
    {
        return this->password;
    };

    unsigned int id;
    QByteArray password;

    Passwords *passwords;
};

#endif // PASSWORD_H
