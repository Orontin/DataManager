#ifndef SECRETS_H
#define SECRETS_H

#include <QList>

#include "secret.h"

#include "abstract.h"

class Data;

struct Secrets: public Abstract {
    Secrets() :
        Abstract(),
        data(nullptr)
    {}
    ~Secrets()
    {
        for (Secret *secret : secrets) {
            delete secret;
            secret = nullptr;
        }
        secrets.clear();
    }

    QByteArray getData() const override
    {
        return QByteArray("Секреты");
    };

    QList<Secret*> secrets;

    Data *data;
};
#endif // SECRETS_H
