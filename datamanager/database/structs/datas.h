#ifndef DATAS_H
#define DATAS_H

#include <QList>
#include <QString>

#include "abstract.h"

#include "data.h"

struct Datas: public Abstract {
    Datas() :
        Abstract()
    {}
    ~Datas()
    {
        for (Data *data : datas) {
            delete data;
            data = nullptr;
        }
        datas.clear();
    }

    QByteArray getData() const override
    {
        return QByteArray("root");
    };

    QList<Data*> datas;
};

#endif // DATAS_H
