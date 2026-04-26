#ifndef MAIL_H
#define MAIL_H

#include <QString>

#include "abstract.h"

class Mails;

struct Mail: public Abstract {
    Mail() :
        Abstract(),
        id(0),
        mail(),
        mails(nullptr)
    {}

    QByteArray getData() const override
    {
        return this->mail;
    };

    unsigned int id;
    QByteArray mail;

    Mails *mails;
};

#endif // MAIL_H
