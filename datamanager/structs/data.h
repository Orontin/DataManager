#ifndef DATA_H
#define DATA_H

#include <QList>
#include <QString>

#include "login.h"
#include "mail.h"
#include "password.h"
#include "telephone.h"
#include "twofactor.h"
#include "secret.h"

struct Data {
    unsigned int id;
    QString name;
    QList<Login> logins;
    QList<Password> passwords;
    QList<Mail> mails;
    QList<Telephone> telephones;
    QList<Twofactor> twofactors;
    QList<Secret> secrets;
};

#endif // DATA_H
