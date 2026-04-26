#ifndef TELEPHONES_H
#define TELEPHONES_H

#include <QList>

#include "telephone.h"

#include "abstract.h"

class Data;

struct Telephones: public Abstract {
    Telephones() :
        Abstract(),
        data(nullptr)
    {}
    ~Telephones()
    {
        for (Telephone *telephone : telephones) {
            delete telephone;
            telephone = nullptr;
        }
        telephones.clear();
    }

    QByteArray getData() const override
    {
        return QByteArray("Номера телефонов");
    };

    QList<Telephone*> telephones;

    Data *data;
};

#endif // TELEPHONES_H
