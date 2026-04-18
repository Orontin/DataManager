#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QSqlDatabase>

#include "../structs/data.h"

class DataBase : public QObject
{
    Q_OBJECT
public:
    static void write(QList<Data> &datas);
    static void write(const QList<Login> &logins);
    static void write(const QList<Password> &passwords);
    static void write(const QList<Mail> &mails);
    static void write(const QList<Telephone> &telephones);
    static void write(const QList<Twofactor> &twofactors);
    static void write(const QList<Secret> &secrets);

    static QList<Data> read();

private:
    static void getDatas(QList<Data> &datas);
    static void getLogins(QList<Data> &datas);
    static void getPasswords(QList<Data> &datas);
    static void getMails(QList<Data> &datas);
    static void getTelephones(QList<Data> &datas);
    static void getTwofactors(QList<Data> &datas);
    static void getSecrets(QList<Data> &datas);

    static void common();

    static void checkAndCreateConnectDataBase();
    static void checkAndCreateDataBase();

    static bool checkTable(const QString &name, const QString &requestCreate);
    static void createTable(const QString &request);
    static void deleteTable(const QString &name);

    static QString createRequestCreateTableDatas();

    static QString createRequestCreateTableLogins();
    static QString createRequestCreateTablePasswords();
    static QString createRequestCreateTableMails();
    static QString createRequestCreateTableTelephones();
    static QString createRequestCreateTableTwofactors();
    static QString createRequestCreateTableSecrets();

    static QString createRequestCreateTable(const QString &nameTable, const QString &nameColumnId, const QString &nameColumnKey, const QString &nameTableDatas, const QString &nameTableDatasColumnId, const QString &nameColumnInformation);

    static QSqlDatabase db;

    static const QString nameTableDatas;
    static const QString nameTableDatasColumnId;
    static const QString nameTableDatasColumnName;

    static const QString nameTableLogins;
    static const QString nameTableLoginsColumnId;
    static const QString nameTableLoginsColumnIdDatas;
    static const QString nameTableLoginsColumnLogin;

    static const QString nameTablePasswords;
    static const QString nameTablePasswordsColumnId;
    static const QString nameTablePasswordsColumnIdDatas;
    static const QString nameTablePasswordsColumnPassword;

    static const QString nameTableMails;
    static const QString nameTableMailsColumnId;
    static const QString nameTableMailsColumnIdDatas;
    static const QString nameTableMailsColumnMail;

    static const QString nameTableTelephones;
    static const QString nameTableTelephonesColumnId;
    static const QString nameTableTelephonesColumnIdDatas;
    static const QString nameTableTelephonesColumnTelephone;

    static const QString nameTableTwofactors;
    static const QString nameTableTwofactorsColumnId;
    static const QString nameTableTwofactorsColumnIdDatas;
    static const QString nameTableTwofactorsColumnTwofactor;

    static const QString nameTableSecrets;
    static const QString nameTableSecretsColumnId;
    static const QString nameTableSecretsColumnIdDatas;
    static const QString nameTableSecretsColumnSecret;
};

#endif // DATABASE_H
