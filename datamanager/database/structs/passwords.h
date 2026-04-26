#ifndef PASSWORDS_H
#define PASSWORDS_H

#include <QList>

#include "password.h"

#include "abstract.h"

class Data;

struct Passwords: public Abstract {
    Passwords() :
        Abstract(),
        data(nullptr)
    {}
    ~Passwords()
    {
        for (Password *password : passwords) {
            delete password;
            password = nullptr;
        }
        passwords.clear();
    }

    QByteArray getData() const override
    {
        return QByteArray("Пароли");
    };

    QList<Password*> passwords;

    Data *data;
};

#endif // PASSWORDS_H
