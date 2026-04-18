#include "database.h"

QSqlDatabase DataBase::db;

const QString DataBase::nameTableDatas("datas");
const QString DataBase::nameTableDatasColumnId("id");
const QString DataBase::nameTableDatasColumnName("name");

const QString DataBase::nameTableLogins("logins");
const QString DataBase::nameTableLoginsColumnId("id");
const QString DataBase::nameTableLoginsColumnIdDatas("id_datas");
const QString DataBase::nameTableLoginsColumnLogin("login");

const QString DataBase::nameTablePasswords("passwords");
const QString DataBase::nameTablePasswordsColumnId("id");
const QString DataBase::nameTablePasswordsColumnIdDatas("id_datas");
const QString DataBase::nameTablePasswordsColumnPassword("password");

const QString DataBase::nameTableMails("mails");
const QString DataBase::nameTableMailsColumnId("id");
const QString DataBase::nameTableMailsColumnIdDatas("id_datas");
const QString DataBase::nameTableMailsColumnMail("mail");

const QString DataBase::nameTableTelephones("telephones");
const QString DataBase::nameTableTelephonesColumnId("id");
const QString DataBase::nameTableTelephonesColumnIdDatas("id_datas");
const QString DataBase::nameTableTelephonesColumnTelephone("telephone");

const QString DataBase::nameTableTwofactors("twofactors");
const QString DataBase::nameTableTwofactorsColumnId("id");
const QString DataBase::nameTableTwofactorsColumnIdDatas("id_datas");
const QString DataBase::nameTableTwofactorsColumnTwofactor("twofactor");

const QString DataBase::nameTableSecrets("secrets");
const QString DataBase::nameTableSecretsColumnId("id");
const QString DataBase::nameTableSecretsColumnIdDatas("id_datas");
const QString DataBase::nameTableSecretsColumnSecret("secret");

void DataBase::write(QList<Data> &datas)
{
    DataBase::common();

    for (Data &data : datas) {
        QString request;
        if (data.id == 0) {
            request = QString("INSERT INTO '%1' ('%2') VALUES ('%3') RETURNING %4").arg(DataBase::nameTableDatas).arg(DataBase::nameTableDatasColumnName).arg(data.name).arg(DataBase::nameTableDatasColumnId);

            QSqlQuery query(DataBase::db);
            query.exec(request);

            query.next();
            data.id = query.value(0).toUInt();

            for (Login &login : data.logins) {
                login.id_datas = data.id;
            }
            for (Password &password : data.passwords) {
                password.id_datas = data.id;
            }
            for (Mail &mail : data.mails) {
                mail.id_datas = data.id;
            }
            for (Telephone &telephone : data.telephones) {
                telephone.id_datas = data.id;
            }
            for (Twofactor &twofactor : data.twofactors) {
                twofactor.id_datas = data.id;
            }
            for (Secret &secret : data.secrets) {
                secret.id_datas = data.id;
            }
        } else {
            request = QString("UPDATE '%1' SET %2 = '%3' WHERE %4 = '%5'").arg(DataBase::nameTableDatas).arg(DataBase::nameTableDatasColumnName).arg(data.name).arg(DataBase::nameTableDatasColumnId).arg(data.id);

            QSqlQuery query(DataBase::db);
            query.exec(request);
        }

        DataBase::write(data.logins);
        DataBase::write(data.passwords);
        DataBase::write(data.mails);
        DataBase::write(data.telephones);
        DataBase::write(data.twofactors);
        DataBase::write(data.secrets);
    }
}

void DataBase::write(const QList<Login> &logins)
{
    DataBase::common();

    for (const Login &login : logins) {
        QString request;
        if (login.id == 0) {
            request = QString("INSERT INTO '%1' ('%2', '%3') VALUES ('%4', '%5')").arg(DataBase::nameTableLogins).arg(DataBase::nameTableLoginsColumnIdDatas).arg(DataBase::nameTableLoginsColumnLogin).arg(login.id_datas).arg(login.login);
        } else {
            request = QString("UPDATE '%1' SET %2 = '%3', %4 = '%5' WHERE %6 = '%7'").arg(DataBase::nameTableLogins).arg(DataBase::nameTableLoginsColumnIdDatas).arg(login.id_datas).arg(DataBase::nameTableLoginsColumnLogin).arg(login.login).arg(DataBase::nameTableLoginsColumnId).arg(login.id);
        }

        QSqlQuery query(DataBase::db);
        query.exec(request);
    }
}

void DataBase::write(const QList<Password> &passwords)
{
    DataBase::common();

    for (const Password &password : passwords) {
        QString request;
        if (password.id == 0) {
            request = QString("INSERT INTO '%1' ('%2', '%3') VALUES ('%4', '%5')").arg(DataBase::nameTablePasswords).arg(DataBase::nameTablePasswordsColumnIdDatas).arg(DataBase::nameTablePasswordsColumnPassword).arg(password.id_datas).arg(password.password);
        } else {
            request = QString("UPDATE '%1' SET %2 = '%3', %4 = '%5' WHERE %6 = '%7'").arg(DataBase::nameTablePasswords).arg(DataBase::nameTablePasswordsColumnIdDatas).arg(password.id_datas).arg(DataBase::nameTablePasswordsColumnPassword).arg(password.password).arg(DataBase::nameTablePasswordsColumnId).arg(password.id);
        }

        QSqlQuery query(DataBase::db);
        query.exec(request);
    }
}

void DataBase::write(const QList<Mail> &mails)
{
    DataBase::common();

    for (const Mail &mail : mails) {
        QString request;
        if (mail.id == 0) {
            request = QString("INSERT INTO '%1' ('%2', '%3') VALUES ('%4', '%5')").arg(DataBase::nameTableMails).arg(DataBase::nameTableMailsColumnIdDatas).arg(DataBase::nameTableMailsColumnMail).arg(mail.id_datas).arg(mail.mail);
        } else {
            request = QString("UPDATE '%1' SET %2 = '%3', %4 = '%5' WHERE %6 = '%7'").arg(DataBase::nameTableMails).arg(DataBase::nameTableMailsColumnIdDatas).arg(mail.id_datas).arg(DataBase::nameTableMailsColumnMail).arg(mail.mail).arg(DataBase::nameTableMailsColumnId).arg(mail.id);
        }

        QSqlQuery query(DataBase::db);
        query.exec(request);
    }
}

void DataBase::write(const QList<Telephone> &telephones)
{
    DataBase::common();

    for (const Telephone &telephone : telephones) {
        QString request;
        if (telephone.id == 0) {
            request = QString("INSERT INTO '%1' ('%2', '%3') VALUES ('%4', '%5')").arg(DataBase::nameTableTelephones).arg(DataBase::nameTableTelephonesColumnIdDatas).arg(DataBase::nameTableTelephonesColumnTelephone).arg(telephone.id_datas).arg(telephone.telephone);
        } else {
            request = QString("UPDATE '%1' SET %2 = '%3', %4 = '%5' WHERE %6 = '%7'").arg(DataBase::nameTableTelephones).arg(DataBase::nameTableTelephonesColumnIdDatas).arg(telephone.id_datas).arg(DataBase::nameTableTelephonesColumnTelephone).arg(telephone.telephone).arg(DataBase::nameTableTelephonesColumnId).arg(telephone.id);
        }

        QSqlQuery query(DataBase::db);
        query.exec(request);
    }
}

void DataBase::write(const QList<Twofactor> &twofactors)
{
    DataBase::common();

    for (const Twofactor &twofactor : twofactors) {
        QString request;
        if (twofactor.id == 0) {
            request = QString("INSERT INTO '%1' ('%2', '%3') VALUES ('%4', '%5')").arg(DataBase::nameTableTwofactors).arg(DataBase::nameTableTwofactorsColumnIdDatas).arg(DataBase::nameTableTwofactorsColumnTwofactor).arg(twofactor.id_datas).arg(twofactor.twofactor);
        } else {
            request = QString("UPDATE '%1' SET %2 = '%3', %4 = '%5' WHERE %6 = '%7'").arg(DataBase::nameTableTwofactors).arg(DataBase::nameTableTwofactorsColumnIdDatas).arg(twofactor.id_datas).arg(DataBase::nameTableTwofactorsColumnTwofactor).arg(twofactor.twofactor).arg(DataBase::nameTableTwofactorsColumnId).arg(twofactor.id);
        }

        QSqlQuery query(DataBase::db);
        query.exec(request);
    }
}

void DataBase::write(const QList<Secret> &secrets)
{
    DataBase::common();

    for (const Secret &secret : secrets) {
        QString request;
        if (secret.id == 0) {
            request = QString("INSERT INTO '%1' ('%2', '%3') VALUES ('%4', '%5')").arg(DataBase::nameTableSecrets).arg(DataBase::nameTableSecretsColumnIdDatas).arg(DataBase::nameTableSecretsColumnSecret).arg(secret.id_datas).arg(secret.secret);
        } else {
            request = QString("UPDATE '%1' SET %2 = '%3', %4 = '%5' WHERE %6 = '%7'").arg(DataBase::nameTableSecrets).arg(DataBase::nameTableSecretsColumnIdDatas).arg(secret.id_datas).arg(DataBase::nameTableSecretsColumnSecret).arg(secret.secret).arg(DataBase::nameTableSecretsColumnId).arg(secret.id);
        }

        QSqlQuery query(DataBase::db);
        query.exec(request);
    }
}

QList<Data> DataBase::read()
{
    QList<Data> datas;

    DataBase::common();

    DataBase::getDatas(datas);
    DataBase::getLogins(datas);
    DataBase::getPasswords(datas);
    DataBase::getMails(datas);
    DataBase::getTelephones(datas);
    DataBase::getTwofactors(datas);
    DataBase::getSecrets(datas);

    return datas;
}

void DataBase::getDatas(QList<Data> &datas)
{
    QString request = QString("SELECT '%1', '%2' FROM '%3'").arg(DataBase::nameTableDatasColumnId).arg(DataBase::nameTableDatasColumnName).arg(DataBase::nameTableDatas);

    QSqlQuery query(DataBase::db);
    query.exec(request);

    while (query.next()) {
        Data data;

        int id = query.value(0).toUInt();
        QString name = query.value(1).toString();

        data.id = id;
        data.name = name;

        datas.push_back(data);
    }
}

void DataBase::getLogins(QList<Data> &datas)
{
    QString request = QString("SELECT '%1', '%2', '%3' FROM '%4'").arg(DataBase::nameTableLoginsColumnId).arg(DataBase::nameTableLoginsColumnIdDatas).arg(DataBase::nameTableLoginsColumnLogin).arg(DataBase::nameTableLogins);

    QSqlQuery query(DataBase::db);
    query.exec(request);

    while (query.next()) {
        Login login;

        int id = query.value(0).toUInt();
        int id_datas = query.value(1).toUInt();
        QString _login = query.value(2).toString();

        login.id = id;
        login.id_datas = id_datas;
        login.login = _login;

        for (Data &data : datas) {
            if (data.id == login.id_datas) {
                data.logins.push_back(login);
                break;
            }
        }
    }
}

void DataBase::getPasswords(QList<Data> &datas)
{
    QString request = QString("SELECT '%1', '%2', '%3' FROM '%4'").arg(DataBase::nameTablePasswordsColumnId).arg(DataBase::nameTablePasswordsColumnIdDatas).arg(DataBase::nameTablePasswordsColumnPassword).arg(DataBase::nameTablePasswords);

    QSqlQuery query(DataBase::db);
    query.exec(request);

    while (query.next()) {
        Password password;

        int id = query.value(0).toUInt();
        int id_datas = query.value(1).toUInt();
        QString _password = query.value(2).toString();

        password.id = id;
        password.id_datas = id_datas;
        password.password = _password;

        for (Data &data : datas) {
            if (data.id == password.id_datas) {
                data.passwords.push_back(password);
                break;
            }
        }
    }
}

void DataBase::getMails(QList<Data> &datas)
{
    QString request = QString("SELECT '%1', '%2', '%3' FROM '%4'").arg(DataBase::nameTableMailsColumnId).arg(DataBase::nameTableMailsColumnIdDatas).arg(DataBase::nameTableMailsColumnMail).arg(DataBase::nameTableMails);

    QSqlQuery query(DataBase::db);
    query.exec(request);

    while (query.next()) {
        Mail mail;

        int id = query.value(0).toUInt();
        int id_datas = query.value(1).toUInt();
        QString _mail = query.value(2).toString();

        mail.id = id;
        mail.id_datas = id_datas;
        mail.mail = _mail;

        for (Data &data : datas) {
            if (data.id == mail.id_datas) {
                data.mails.push_back(mail);
                break;
            }
        }
    }
}

void DataBase::getTelephones(QList<Data> &datas)
{
    QString request = QString("SELECT '%1', '%2', '%3' FROM '%4'").arg(DataBase::nameTableTelephonesColumnId).arg(DataBase::nameTableTelephonesColumnIdDatas).arg(DataBase::nameTableTelephonesColumnTelephone).arg(DataBase::nameTableTelephones);

    QSqlQuery query(DataBase::db);
    query.exec(request);

    while (query.next()) {
        Telephone telephone;

        int id = query.value(0).toUInt();
        int id_datas = query.value(1).toUInt();
        QString _telephone = query.value(2).toString();

        telephone.id = id;
        telephone.id_datas = id_datas;
        telephone.telephone = _telephone;

        for (Data &data : datas) {
            if (data.id == telephone.id_datas) {
                data.telephones.push_back(telephone);
                break;
            }
        }
    }
}

void DataBase::getTwofactors(QList<Data> &datas)
{
    QString request = QString("SELECT '%1', '%2', '%3' FROM '%4'").arg(DataBase::nameTableTwofactorsColumnId).arg(DataBase::nameTableTwofactorsColumnIdDatas).arg(DataBase::nameTableTwofactorsColumnTwofactor).arg(DataBase::nameTableTwofactors);

    QSqlQuery query(DataBase::db);
    query.exec(request);

    while (query.next()) {
        Twofactor twofactor;

        int id = query.value(0).toUInt();
        int id_datas = query.value(1).toUInt();
        QString _twofactor = query.value(2).toString();

        twofactor.id = id;
        twofactor.id_datas = id_datas;
        twofactor.twofactor = _twofactor;

        for (Data &data : datas) {
            if (data.id == twofactor.id_datas) {
                data.twofactors.push_back(twofactor);
                break;
            }
        }
    }
}

void DataBase::getSecrets(QList<Data> &datas)
{
    QString request = QString("SELECT '%1', '%2', '%3' FROM '%4'").arg(DataBase::nameTableSecretsColumnId).arg(DataBase::nameTableSecretsColumnIdDatas).arg(DataBase::nameTableSecretsColumnSecret).arg(DataBase::nameTableSecrets);

    QSqlQuery query(DataBase::db);
    query.exec(request);

    while (query.next()) {
        Secret secret;

        int id = query.value(0).toUInt();
        int id_datas = query.value(1).toUInt();
        QString _secret = query.value(2).toString();

        secret.id = id;
        secret.id_datas = id_datas;
        secret.secret = _secret;

        for (Data &data : datas) {
            if (data.id == secret.id_datas) {
                data.secrets.push_back(secret);
                break;
            }
        }
    }
}

void DataBase::common()
{
    DataBase::checkAndCreateConnectDataBase();
    DataBase::checkAndCreateDataBase();
}

void DataBase::checkAndCreateConnectDataBase()
{
    if (!DataBase::db.isOpen()) {
        DataBase::db = QSqlDatabase::addDatabase("QSQLITE");
        DataBase::db.setDatabaseName("database.db");
        DataBase::db.open();
    }
}

void DataBase::checkAndCreateDataBase()
{
    if (!DataBase::checkTable(DataBase::nameTableDatas, DataBase::createRequestCreateTableDatas())) {
        DataBase::deleteTable(DataBase::nameTableDatas);
        DataBase::createTable(DataBase::createRequestCreateTableDatas());
    }

    if (!DataBase::checkTable(DataBase::nameTableLogins, DataBase::createRequestCreateTableLogins())) {
        DataBase::deleteTable(DataBase::nameTableLogins);
        DataBase::createTable(DataBase::createRequestCreateTableLogins());
    }

    if (!DataBase::checkTable(DataBase::nameTablePasswords, DataBase::createRequestCreateTablePasswords())) {
        DataBase::deleteTable(DataBase::nameTablePasswords);
        DataBase::createTable(DataBase::createRequestCreateTablePasswords());
    }

    if (!DataBase::checkTable(DataBase::nameTableMails, DataBase::createRequestCreateTableMails())) {
        DataBase::deleteTable(DataBase::nameTableMails);
        DataBase::createTable(DataBase::createRequestCreateTableMails());
    }

    if (!DataBase::checkTable(DataBase::nameTableTelephones, DataBase::createRequestCreateTableTelephones())) {
        DataBase::deleteTable(DataBase::nameTableTelephones);
        DataBase::createTable(DataBase::createRequestCreateTableTelephones());
    }

    if (!DataBase::checkTable(DataBase::nameTableTwofactors, DataBase::createRequestCreateTableTwofactors())) {
        DataBase::deleteTable(DataBase::nameTableTwofactors);
        DataBase::createTable(DataBase::createRequestCreateTableTwofactors());
    }

    if (!DataBase::checkTable(DataBase::nameTableSecrets, DataBase::createRequestCreateTableSecrets())) {
        DataBase::deleteTable(DataBase::nameTableSecrets);
        DataBase::createTable(DataBase::createRequestCreateTableSecrets());
    }
}

bool DataBase::checkTable(const QString &name, const QString &requestCreate)
{
    QString request = QString("SELECT sql FROM sqlite_master WHERE type = 'table' AND name = '%1'").arg(name);

    QSqlQuery query(DataBase::db);
    query.exec(request);

    query.next();
    QString response = query.value(0).toString();

    return response == requestCreate;
}

void DataBase::createTable(const QString &request)
{
    QSqlQuery query(DataBase::db);
    query.exec(request);
}

void DataBase::deleteTable(const QString &name)
{
    QString request = QString("DROP TABLE '%1'").arg(name);

    QSqlQuery query(DataBase::db);
    query.exec(request);
}

QString DataBase::createRequestCreateTableDatas()
{
    return QString("CREATE TABLE '%1' ('%2' INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT, '%3' TEXT)").arg(DataBase::nameTableDatas).arg(DataBase::nameTableDatasColumnId).arg(DataBase::nameTableDatasColumnName);
}

QString DataBase::createRequestCreateTableLogins()
{
    return DataBase::createRequestCreateTable(DataBase::nameTableLogins, DataBase::nameTableLoginsColumnId, DataBase::nameTableLoginsColumnIdDatas, DataBase::nameTableDatas, DataBase::nameTableDatasColumnId, DataBase::nameTableLoginsColumnLogin);
}

QString DataBase::createRequestCreateTablePasswords()
{
    return DataBase::createRequestCreateTable(DataBase::nameTablePasswords, DataBase::nameTablePasswordsColumnId, DataBase::nameTablePasswordsColumnIdDatas, DataBase::nameTableDatas, DataBase::nameTableDatasColumnId, DataBase::nameTablePasswordsColumnPassword);
}

QString DataBase::createRequestCreateTableMails()
{
    return DataBase::createRequestCreateTable(DataBase::nameTableMails, DataBase::nameTableMailsColumnId, DataBase::nameTableMailsColumnIdDatas, DataBase::nameTableDatas, DataBase::nameTableDatasColumnId, DataBase::nameTableMailsColumnMail);
}

QString DataBase::createRequestCreateTableTelephones()
{
    return DataBase::createRequestCreateTable(DataBase::nameTableTelephones, DataBase::nameTableTelephonesColumnId, DataBase::nameTableTelephonesColumnIdDatas, DataBase::nameTableDatas, DataBase::nameTableDatasColumnId, DataBase::nameTableTelephonesColumnTelephone);
}

QString DataBase::createRequestCreateTableTwofactors()
{
    return DataBase::createRequestCreateTable(DataBase::nameTableTwofactors, DataBase::nameTableTwofactorsColumnId, DataBase::nameTableTwofactorsColumnIdDatas, DataBase::nameTableDatas, DataBase::nameTableDatasColumnId, DataBase::nameTableTwofactorsColumnTwofactor);
}

QString DataBase::createRequestCreateTableSecrets()
{
    return DataBase::createRequestCreateTable(DataBase::nameTableSecrets, DataBase::nameTableSecretsColumnId, DataBase::nameTableSecretsColumnIdDatas, DataBase::nameTableDatas, DataBase::nameTableDatasColumnId, DataBase::nameTableSecretsColumnSecret);
}

QString DataBase::createRequestCreateTable(const QString &nameTable, const QString &nameColumnId, const QString &nameColumnKey, const QString &nameTableDatas, const QString &nameTableDatasColumnId, const QString &nameColumnInformation)
{
    return QString("CREATE TABLE '%1' ('%2' INTEGER PRIMARY KEY ASC ON CONFLICT ROLLBACK AUTOINCREMENT, '%3' INTEGER REFERENCES '%4' ('%5') ON DELETE CASCADE ON UPDATE CASCADE, '%6' TEXT)").arg(nameTable).arg(nameColumnId).arg(nameColumnKey).arg(nameTableDatas).arg(nameTableDatasColumnId).arg(nameColumnInformation);
}
