#ifndef MAILS_H
#define MAILS_H

#include <QList>

#include "mail.h"

#include "abstract.h"

class Data;

struct Mails: public Abstract {
    Mails() :
        Abstract(),
        data(nullptr)
    {}
    ~Mails()
    {
        for (Mail *mail : mails) {
            delete mail;
            mail = nullptr;
        }
        mails.clear();
    }

    QByteArray getData() const override
    {
        return QByteArray("Почтовые ящики");
    };

    QList<Mail*> mails;

    Data *data;
};

#endif // MAILS_H
