#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QSqlDatabase>

#include "structs/datas.h"

class DataBase : public QObject
{
    Q_OBJECT
public:
    static void write(Datas &datas);
    static void write(QList<Login*> &logins);
    static void write(QList<Password*> &passwords);
    static void write(QList<Mail*> &mails);
    static void write(QList<Telephone*> &telephones);
    static void write(QList<Twofactor*> &twofactors);
    static void write(QList<Secret*> &secrets);

    static Datas *read();

private:
    static void getDatas(Datas &datas);
    static void getLogins(Data &data);
    static void getPasswords(Data &data);
    static void getMails(Data &data);
    static void getTelephones(Data &data);
    static void getTwofactors(Data &data);
    static void getSecrets(Data &data);

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

    static QString createRequestCreateTable(const QString &nameTable,
                                            const QString &nameColumnId,
                                            const QString &nameColumnKey,
                                            const QString &nameTableDatas,
                                            const QString &nameTableDatasColumnId,
                                            const QString &nameColumnInformation,
                                            const QString &saltColumnName,
                                            const QString &ivColumnName);

    static QSqlDatabase db;

    static const QString nameTableDatas;
    static const QString nameTableDatasColumnId;
    static const QString nameTableDatasColumnName;
    static const QString nameTableDatasColumnSalt;
    static const QString nameTableDatasColumnIV;

    static const QString nameTableLogins;
    static const QString nameTableLoginsColumnId;
    static const QString nameTableLoginsColumnIdDatas;
    static const QString nameTableLoginsColumnLogin;
    static const QString nameTableLoginsColumnSalt;
    static const QString nameTableLoginsColumnIV;

    static const QString nameTablePasswords;
    static const QString nameTablePasswordsColumnId;
    static const QString nameTablePasswordsColumnIdDatas;
    static const QString nameTablePasswordsColumnPassword;
    static const QString nameTablePasswordsColumnSalt;
    static const QString nameTablePasswordsColumnIV;

    static const QString nameTableMails;
    static const QString nameTableMailsColumnId;
    static const QString nameTableMailsColumnIdDatas;
    static const QString nameTableMailsColumnMail;
    static const QString nameTableMailsColumnSalt;
    static const QString nameTableMailsColumnIV;

    static const QString nameTableTelephones;
    static const QString nameTableTelephonesColumnId;
    static const QString nameTableTelephonesColumnIdDatas;
    static const QString nameTableTelephonesColumnTelephone;
    static const QString nameTableTelephonesColumnSalt;
    static const QString nameTableTelephonesColumnIV;

    static const QString nameTableTwofactors;
    static const QString nameTableTwofactorsColumnId;
    static const QString nameTableTwofactorsColumnIdDatas;
    static const QString nameTableTwofactorsColumnTwofactor;
    static const QString nameTableTwofactorsColumnSalt;
    static const QString nameTableTwofactorsColumnIV;

    static const QString nameTableSecrets;
    static const QString nameTableSecretsColumnId;
    static const QString nameTableSecretsColumnIdDatas;
    static const QString nameTableSecretsColumnSecret;
    static const QString nameTableSecretsColumnSalt;
    static const QString nameTableSecretsColumnIV;
};

#endif // DATABASE_H
