#ifndef TWOFACTORS_H
#define TWOFACTORS_H

#include <QList>

#include "twofactor.h"

#include "abstract.h"

class Data;

struct Twofactors: public Abstract {
    Twofactors() :
        Abstract(),
        data(nullptr)
    {}
    ~Twofactors()
    {
        for (Twofactor *twofactor : twofactors) {
            delete twofactor;
            twofactor = nullptr;
        }
        twofactors.clear();
    }

    QByteArray getData() const override
    {
        return QByteArray("Двухфакторная аутентификация");
    };

    QList<Twofactor*> twofactors;

    Data *data;
};

#endif // TWOFACTORS_H
