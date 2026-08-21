#ifndef LOGINS_H
#define LOGINS_H

#include <QList>

#include "login.h"

#include "abstract.h"

class Data;

struct Logins: public Abstract {
    Logins() :
        Abstract(),
        data(nullptr)
    {}
    ~Logins()
    {
        for (Login *login : logins) {
            delete login;
            login = nullptr;
        }
        logins.clear();
    }

    QByteArray getData() const override
    {
        return QByteArray("Логины");
    };

    QList<Login*> logins;

    Data *data;
};

#endif // LOGINS_H
