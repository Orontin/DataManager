#ifndef LOGIN_H
#define LOGIN_H

#include <QString>

#include "abstract.h"

class Logins;

struct Login: public Abstract {
    Login() :
        Abstract(),
        id(0),
        login(),
        logins(nullptr)
    {}

    QByteArray getData() const override
    {
        return this->login;
    };

    unsigned int id;
    QByteArray login;

    Logins *logins;
};
#endif // LOGIN_H
