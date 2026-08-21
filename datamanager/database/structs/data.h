#ifndef DATA_H
#define DATA_H

#include <QList>
#include <QString>

#include "abstract.h"
#include "logins.h"
#include "mails.h"
#include "passwords.h"
#include "secrets.h"
#include "telephones.h"
#include "twofactors.h"

class Datas;

struct Data: public Abstract {
    Data() :
        Abstract(),
        id(0),
        name(),
        logins(nullptr),
        mails(nullptr),
        passwords(nullptr),
        secrets(nullptr),
        telephones(nullptr),
        twofactors(nullptr),
        datas(nullptr)
    {}
    ~Data()
    {
        delete logins;
        delete mails;
        delete passwords;
        delete secrets;
        delete telephones;
        delete twofactors;
    }

    QByteArray getData() const override
    {
        return this->name;
    };

    unsigned int id;
    QByteArray name;

    Logins *logins;
    Mails *mails;
    Passwords *passwords;
    Secrets *secrets;
    Telephones *telephones;
    Twofactors *twofactors;

    Datas *datas;
};

#endif // DATA_H
