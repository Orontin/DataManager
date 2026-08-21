#include "database.h"
#include <QSqlError>
#include <QSqlRecord>

QSqlDatabase DataBase::db;

const QString DataBase::nameTableDatas("datas");
const QString DataBase::nameTableDatasColumnId("id");
const QString DataBase::nameTableDatasColumnName("name");
const QString DataBase::nameTableDatasColumnSalt("salt");
const QString DataBase::nameTableDatasColumnIV("iv");

const QString DataBase::nameTableLogins("logins");
const QString DataBase::nameTableLoginsColumnId("id");
const QString DataBase::nameTableLoginsColumnIdDatas("id_datas");
const QString DataBase::nameTableLoginsColumnLogin("login");
const QString DataBase::nameTableLoginsColumnSalt("salt");
const QString DataBase::nameTableLoginsColumnIV("iv");

const QString DataBase::nameTablePasswords("passwords");
const QString DataBase::nameTablePasswordsColumnId("id");
const QString DataBase::nameTablePasswordsColumnIdDatas("id_datas");
const QString DataBase::nameTablePasswordsColumnPassword("password");
const QString DataBase::nameTablePasswordsColumnSalt("salt");
const QString DataBase::nameTablePasswordsColumnIV("iv");

const QString DataBase::nameTableMails("mails");
const QString DataBase::nameTableMailsColumnId("id");
const QString DataBase::nameTableMailsColumnIdDatas("id_datas");
const QString DataBase::nameTableMailsColumnMail("mail");
const QString DataBase::nameTableMailsColumnSalt("salt");
const QString DataBase::nameTableMailsColumnIV("iv");

const QString DataBase::nameTableTelephones("telephones");
const QString DataBase::nameTableTelephonesColumnId("id");
const QString DataBase::nameTableTelephonesColumnIdDatas("id_datas");
const QString DataBase::nameTableTelephonesColumnTelephone("telephone");
const QString DataBase::nameTableTelephonesColumnSalt("salt");
const QString DataBase::nameTableTelephonesColumnIV("iv");

const QString DataBase::nameTableTwofactors("twofactors");
const QString DataBase::nameTableTwofactorsColumnId("id");
const QString DataBase::nameTableTwofactorsColumnIdDatas("id_datas");
const QString DataBase::nameTableTwofactorsColumnTwofactor("twofactor");
const QString DataBase::nameTableTwofactorsColumnSalt("salt");
const QString DataBase::nameTableTwofactorsColumnIV("iv");

const QString DataBase::nameTableSecrets("secrets");
const QString DataBase::nameTableSecretsColumnId("id");
const QString DataBase::nameTableSecretsColumnIdDatas("id_datas");
const QString DataBase::nameTableSecretsColumnSecret("secret");
const QString DataBase::nameTableSecretsColumnSalt("salt");
const QString DataBase::nameTableSecretsColumnIV("iv");

void DataBase::write(Datas &datas)
{
    DataBase::common();

    for (Data *data : datas.datas) {
        QSqlQuery query(DataBase::db);
        if (data->id == 0) {
            query.prepare(QString("INSERT INTO \"%1\" (\"%2\", \"%3\", \"%4\") VALUES (:name, :salt, :iv)")
                              .arg(DataBase::nameTableDatas)
                              .arg(DataBase::nameTableDatasColumnName)
                              .arg(DataBase::nameTableDatasColumnSalt)
                              .arg(DataBase::nameTableDatasColumnIV));
            query.bindValue(":name", data->name);
            query.bindValue(":salt", data->salt);
            query.bindValue(":iv", data->iv);
            if (!query.exec()) {
                continue;
            }
            data->id = query.lastInsertId().toUInt();
        } else {
            query.prepare(QString("UPDATE \"%1\" SET \"%2\" = :name, \"%3\" = :salt, \"%4\" = :iv WHERE \"%5\" = :id")
                              .arg(DataBase::nameTableDatas)
                              .arg(DataBase::nameTableDatasColumnName)
                              .arg(DataBase::nameTableDatasColumnSalt)
                              .arg(DataBase::nameTableDatasColumnIV)
                              .arg(DataBase::nameTableDatasColumnId));
            query.bindValue(":name", data->name);
            query.bindValue(":salt", data->salt);
            query.bindValue(":iv", data->iv);
            query.bindValue(":id", data->id);
            if (!query.exec()) {
                continue;
            }
        }

        write(data->logins->logins);
        write(data->passwords->passwords);
        write(data->mails->mails);
        write(data->telephones->telephones);
        write(data->twofactors->twofactors);
        write(data->secrets->secrets);
    }
}

void DataBase::write(QList<Login*> &logins)
{
    DataBase::common();

    for (Login *login : logins) {
        QSqlQuery query(DataBase::db);
        if (login->id == 0) {
            query.prepare(QString("INSERT INTO \"%1\" (\"%2\", \"%3\", \"%4\", \"%5\") VALUES (:id_datas, :login, :salt, :iv)")
                              .arg(DataBase::nameTableLogins)
                              .arg(DataBase::nameTableLoginsColumnIdDatas)
                              .arg(DataBase::nameTableLoginsColumnLogin)
                              .arg(DataBase::nameTableLoginsColumnSalt)
                              .arg(DataBase::nameTableLoginsColumnIV));
            query.bindValue(":id_datas", login->logins->data->id);
            query.bindValue(":login", login->login);
            query.bindValue(":salt", login->salt);
            query.bindValue(":iv", login->iv);
            if (!query.exec()) {
                continue;
            }
            login->id = query.lastInsertId().toUInt();
        } else {
            query.prepare(QString("UPDATE \"%1\" SET \"%2\" = :id_datas, \"%3\" = :login, \"%4\" = :salt, \"%5\" = :iv WHERE \"%6\" = :id")
                              .arg(DataBase::nameTableLogins)
                              .arg(DataBase::nameTableLoginsColumnIdDatas)
                              .arg(DataBase::nameTableLoginsColumnLogin)
                              .arg(DataBase::nameTableLoginsColumnSalt)
                              .arg(DataBase::nameTableLoginsColumnIV)
                              .arg(DataBase::nameTableLoginsColumnId));
            query.bindValue(":id_datas", login->logins->data->id);
            query.bindValue(":login", login->login);
            query.bindValue(":salt", login->salt);
            query.bindValue(":iv", login->iv);
            query.bindValue(":id", login->id);
            if (!query.exec()) {
                qWarning() << "Update login failed:" << query.lastError().text();
            }
        }
    }
}

void DataBase::write(QList<Password*> &passwords)
{
    DataBase::common();

    for (Password *password : passwords) {
        QSqlQuery query(DataBase::db);
        if (password->id == 0) {
            query.prepare(QString("INSERT INTO \"%1\" (\"%2\", \"%3\", \"%4\", \"%5\") VALUES (:id_datas, :password, :salt, :iv)")
                              .arg(DataBase::nameTablePasswords)
                              .arg(DataBase::nameTablePasswordsColumnIdDatas)
                              .arg(DataBase::nameTablePasswordsColumnPassword)
                              .arg(DataBase::nameTablePasswordsColumnSalt)
                              .arg(DataBase::nameTablePasswordsColumnIV));
            query.bindValue(":id_datas", password->passwords->data->id);
            query.bindValue(":password", password->password);
            query.bindValue(":salt", password->salt);
            query.bindValue(":iv", password->iv);
            if (!query.exec()) {
                continue;
            }
            password->id = query.lastInsertId().toUInt();
        } else {
            query.prepare(QString("UPDATE \"%1\" SET \"%2\" = :id_datas, \"%3\" = :password, \"%4\" = :salt, \"%5\" = :iv WHERE \"%6\" = :id")
                              .arg(DataBase::nameTablePasswords)
                              .arg(DataBase::nameTablePasswordsColumnIdDatas)
                              .arg(DataBase::nameTablePasswordsColumnPassword)
                              .arg(DataBase::nameTablePasswordsColumnSalt)
                              .arg(DataBase::nameTablePasswordsColumnIV)
                              .arg(DataBase::nameTablePasswordsColumnId));
            query.bindValue(":id_datas", password->passwords->data->id);
            query.bindValue(":password", password->password);
            query.bindValue(":salt", password->salt);
            query.bindValue(":iv", password->iv);
            query.bindValue(":id", password->id);
            query.exec();
        }
    }
}

void DataBase::write(QList<Mail*> &mails)
{
    DataBase::common();

    for (Mail *mail : mails) {
        QSqlQuery query(DataBase::db);
        if (mail->id == 0) {
            query.prepare(QString("INSERT INTO \"%1\" (\"%2\", \"%3\", \"%4\", \"%5\") VALUES (:id_datas, :mail, :salt, :iv)")
                              .arg(DataBase::nameTableMails)
                              .arg(DataBase::nameTableMailsColumnIdDatas)
                              .arg(DataBase::nameTableMailsColumnMail)
                              .arg(DataBase::nameTableMailsColumnSalt)
                              .arg(DataBase::nameTableMailsColumnIV));
            query.bindValue(":id_datas", mail->mails->data->id);
            query.bindValue(":mail", mail->mail);
            query.bindValue(":salt", mail->salt);
            query.bindValue(":iv", mail->iv);
            if (!query.exec()) {
                continue;
            }
            mail->id = query.lastInsertId().toUInt();
        } else {
            query.prepare(QString("UPDATE \"%1\" SET \"%2\" = :id_datas, \"%3\" = :mail, \"%4\" = :salt, \"%5\" = :iv WHERE \"%6\" = :id")
                              .arg(DataBase::nameTableMails)
                              .arg(DataBase::nameTableMailsColumnIdDatas)
                              .arg(DataBase::nameTableMailsColumnMail)
                              .arg(DataBase::nameTableMailsColumnSalt)
                              .arg(DataBase::nameTableMailsColumnIV)
                              .arg(DataBase::nameTableMailsColumnId));
            query.bindValue(":id_datas", mail->mails->data->id);
            query.bindValue(":mail", mail->mail);
            query.bindValue(":salt", mail->salt);
            query.bindValue(":iv", mail->iv);
            query.bindValue(":id", mail->id);
            query.exec();
        }
    }
}

void DataBase::write(QList<Telephone*> &telephones)
{
    DataBase::common();

    for (Telephone *telephone : telephones) {
        QSqlQuery query(DataBase::db);
        if (telephone->id == 0) {
            query.prepare(QString("INSERT INTO \"%1\" (\"%2\", \"%3\", \"%4\", \"%5\") VALUES (:id_datas, :telephone, :salt, :iv)")
                              .arg(DataBase::nameTableTelephones)
                              .arg(DataBase::nameTableTelephonesColumnIdDatas)
                              .arg(DataBase::nameTableTelephonesColumnTelephone)
                              .arg(DataBase::nameTableTelephonesColumnSalt)
                              .arg(DataBase::nameTableTelephonesColumnIV));
            query.bindValue(":id_datas", telephone->telephones->data->id);
            query.bindValue(":telephone", telephone->telephone);
            query.bindValue(":salt", telephone->salt);
            query.bindValue(":iv", telephone->iv);
            if (!query.exec()) {
                continue;
            }
            telephone->id = query.lastInsertId().toUInt();
        } else {
            query.prepare(QString("UPDATE \"%1\" SET \"%2\" = :id_datas, \"%3\" = :telephone, \"%4\" = :salt, \"%5\" = :iv WHERE \"%6\" = :id")
                              .arg(DataBase::nameTableTelephones)
                              .arg(DataBase::nameTableTelephonesColumnIdDatas)
                              .arg(DataBase::nameTableTelephonesColumnTelephone)
                              .arg(DataBase::nameTableTelephonesColumnSalt)
                              .arg(DataBase::nameTableTelephonesColumnIV)
                              .arg(DataBase::nameTableTelephonesColumnId));
            query.bindValue(":id_datas", telephone->telephones->data->id);
            query.bindValue(":telephone", telephone->telephone);
            query.bindValue(":salt", telephone->salt);
            query.bindValue(":iv", telephone->iv);
            query.bindValue(":id", telephone->id);
            query.exec();
        }
    }
}

void DataBase::write(QList<Twofactor*> &twofactors)
{
    DataBase::common();

    for (Twofactor *twofactor : twofactors) {
        QSqlQuery query(DataBase::db);
        if (twofactor->id == 0) {
            query.prepare(QString("INSERT INTO \"%1\" (\"%2\", \"%3\", \"%4\", \"%5\") VALUES (:id_datas, :twofactor, :salt, :iv)")
                              .arg(DataBase::nameTableTwofactors)
                              .arg(DataBase::nameTableTwofactorsColumnIdDatas)
                              .arg(DataBase::nameTableTwofactorsColumnTwofactor)
                              .arg(DataBase::nameTableTwofactorsColumnSalt)
                              .arg(DataBase::nameTableTwofactorsColumnIV));
            query.bindValue(":id_datas", twofactor->twofactors->data->id);
            query.bindValue(":twofactor", twofactor->twofactor);
            query.bindValue(":salt", twofactor->salt);
            query.bindValue(":iv", twofactor->iv);
            if (!query.exec()) {
                continue;
            }
            twofactor->id = query.lastInsertId().toUInt();
        } else {
            query.prepare(QString("UPDATE \"%1\" SET \"%2\" = :id_datas, \"%3\" = :twofactor, \"%4\" = :salt, \"%5\" = :iv WHERE \"%6\" = :id")
                              .arg(DataBase::nameTableTwofactors)
                              .arg(DataBase::nameTableTwofactorsColumnIdDatas)
                              .arg(DataBase::nameTableTwofactorsColumnTwofactor)
                              .arg(DataBase::nameTableTwofactorsColumnSalt)
                              .arg(DataBase::nameTableTwofactorsColumnIV)
                              .arg(DataBase::nameTableTwofactorsColumnId));
            query.bindValue(":id_datas", twofactor->twofactors->data->id);
            query.bindValue(":twofactor", twofactor->twofactor);
            query.bindValue(":salt", twofactor->salt);
            query.bindValue(":iv", twofactor->iv);
            query.bindValue(":id", twofactor->id);
            query.exec();
        }
    }
}

void DataBase::write(QList<Secret*> &secrets)
{
    DataBase::common();

    for (Secret *secret : secrets) {
        QSqlQuery query(DataBase::db);
        if (secret->id == 0) {
            query.prepare(QString("INSERT INTO \"%1\" (\"%2\", \"%3\", \"%4\", \"%5\") VALUES (:id_datas, :secret, :salt, :iv)")
                              .arg(DataBase::nameTableSecrets)
                              .arg(DataBase::nameTableSecretsColumnIdDatas)
                              .arg(DataBase::nameTableSecretsColumnSecret)
                              .arg(DataBase::nameTableSecretsColumnSalt)
                              .arg(DataBase::nameTableSecretsColumnIV));
            query.bindValue(":id_datas", secret->secrets->data->id);
            query.bindValue(":secret", secret->secret);
            query.bindValue(":salt", secret->salt);
            query.bindValue(":iv", secret->iv);
            if (!query.exec()) {
                continue;
            }
            secret->id = query.lastInsertId().toUInt();
        } else {
            query.prepare(QString("UPDATE \"%1\" SET \"%2\" = :id_datas, \"%3\" = :secret, \"%4\" = :salt, \"%5\" = :iv WHERE \"%6\" = :id")
                              .arg(DataBase::nameTableSecrets)
                              .arg(DataBase::nameTableSecretsColumnIdDatas)
                              .arg(DataBase::nameTableSecretsColumnSecret)
                              .arg(DataBase::nameTableSecretsColumnSalt)
                              .arg(DataBase::nameTableSecretsColumnIV)
                              .arg(DataBase::nameTableSecretsColumnId));
            query.bindValue(":id_datas", secret->secrets->data->id);
            query.bindValue(":secret", secret->secret);
            query.bindValue(":salt", secret->salt);
            query.bindValue(":iv", secret->iv);
            query.bindValue(":id", secret->id);
            query.exec();
        }
    }
}

Datas *DataBase::read()
{
    DataBase::common();

    Datas *datas = new Datas;

    DataBase::getDatas(*datas);

    return datas;
}

void DataBase::getDatas(Datas &datas)
{
    QSqlQuery query(DataBase::db);
    query.prepare(QString("SELECT \"%1\", \"%2\", \"%3\", \"%4\" FROM \"%5\"")
                      .arg(DataBase::nameTableDatasColumnId)
                      .arg(DataBase::nameTableDatasColumnName)
                      .arg(DataBase::nameTableDatasColumnSalt)
                      .arg(DataBase::nameTableDatasColumnIV)
                      .arg(DataBase::nameTableDatas));
    query.exec();

    while (query.next()) {
        Data *data = new Data;
        data->id = query.value(0).toUInt();
        data->name = query.value(1).toByteArray();
        data->salt = query.value(2).toByteArray();
        data->iv = query.value(3).toByteArray();

        DataBase::getLogins(*data);
        DataBase::getPasswords(*data);
        DataBase::getMails(*data);
        DataBase::getTelephones(*data);
        DataBase::getTwofactors(*data);
        DataBase::getSecrets(*data);

        data->datas = &datas;
        datas.datas.push_back(data);
    }
}

void DataBase::getLogins(Data &data)
{
    QSqlQuery query(DataBase::db);
    query.prepare(QString("SELECT \"%1\", \"%2\", \"%3\", \"%4\" FROM \"%5\" WHERE \"%6\" = :id_datas")
                      .arg(DataBase::nameTableLoginsColumnId)
                      .arg(DataBase::nameTableLoginsColumnLogin)
                      .arg(DataBase::nameTableLoginsColumnSalt)
                      .arg(DataBase::nameTableLoginsColumnIV)
                      .arg(DataBase::nameTableLogins)
                      .arg(DataBase::nameTableLoginsColumnIdDatas));
    query.bindValue(":id_datas", data.id);
    query.exec();

    Logins *logins = new Logins;
    logins->data = &data;
    data.logins = logins;
    while (query.next()) {
        Login *login = new Login;
        login->id = query.value(0).toUInt();
        login->login = query.value(1).toByteArray();
        login->salt = query.value(2).toByteArray();
        login->iv = query.value(3).toByteArray();
        login->logins = logins;
        logins->logins.push_back(login);
    }
}

void DataBase::getPasswords(Data &data)
{
    QSqlQuery query(DataBase::db);
    query.prepare(QString("SELECT \"%1\", \"%2\", \"%3\", \"%4\" FROM \"%5\" WHERE \"%6\" = :id_datas")
                      .arg(DataBase::nameTablePasswordsColumnId)
                      .arg(DataBase::nameTablePasswordsColumnPassword)
                      .arg(DataBase::nameTablePasswordsColumnSalt)
                      .arg(DataBase::nameTablePasswordsColumnIV)
                      .arg(DataBase::nameTablePasswords)
                      .arg(DataBase::nameTablePasswordsColumnIdDatas));
    query.bindValue(":id_datas", data.id);
    query.exec();

    Passwords *passwords = new Passwords;
    passwords->data = &data;
    data.passwords = passwords;
    while (query.next()) {
        Password *password = new Password;
        password->id = query.value(0).toUInt();
        password->password = query.value(1).toByteArray();
        password->salt = query.value(2).toByteArray();
        password->iv = query.value(3).toByteArray();
        password->passwords = passwords;
        passwords->passwords.push_back(password);
    }
}

void DataBase::getMails(Data &data)
{
    QSqlQuery query(DataBase::db);
    query.prepare(QString("SELECT \"%1\", \"%2\", \"%3\", \"%4\" FROM \"%5\" WHERE \"%6\" = :id_datas")
                      .arg(DataBase::nameTableMailsColumnId)
                      .arg(DataBase::nameTableMailsColumnMail)
                      .arg(DataBase::nameTableMailsColumnSalt)
                      .arg(DataBase::nameTableMailsColumnIV)
                      .arg(DataBase::nameTableMails)
                      .arg(DataBase::nameTableMailsColumnIdDatas));
    query.bindValue(":id_datas", data.id);
    query.exec();

    Mails *mails = new Mails;
    mails->data = &data;
    data.mails = mails;
    while (query.next()) {
        Mail *mail = new Mail;
        mail->id = query.value(0).toUInt();
        mail->mail = query.value(1).toByteArray();
        mail->salt = query.value(2).toByteArray();
        mail->iv = query.value(3).toByteArray();
        mail->mails = mails;
        mails->mails.push_back(mail);
    }
}

void DataBase::getTelephones(Data &data)
{
    QSqlQuery query(DataBase::db);
    query.prepare(QString("SELECT \"%1\", \"%2\", \"%3\", \"%4\" FROM \"%5\" WHERE \"%6\" = :id_datas")
                      .arg(DataBase::nameTableTelephonesColumnId)
                      .arg(DataBase::nameTableTelephonesColumnTelephone)
                      .arg(DataBase::nameTableTelephonesColumnSalt)
                      .arg(DataBase::nameTableTelephonesColumnIV)
                      .arg(DataBase::nameTableTelephones)
                      .arg(DataBase::nameTableTelephonesColumnIdDatas));
    query.bindValue(":id_datas", data.id);
    query.exec();

    Telephones *telephones = new Telephones;
    telephones->data = &data;
    data.telephones = telephones;
    while (query.next()) {
        Telephone *telephone = new Telephone;
        telephone->id = query.value(0).toUInt();
        telephone->telephone = query.value(1).toByteArray();
        telephone->salt = query.value(2).toByteArray();
        telephone->iv = query.value(3).toByteArray();
        telephone->telephones = telephones;
        telephones->telephones.push_back(telephone);
    }
}

void DataBase::getTwofactors(Data &data)
{
    QSqlQuery query(DataBase::db);
    query.prepare(QString("SELECT \"%1\", \"%2\", \"%3\", \"%4\" FROM \"%5\" WHERE \"%6\" = :id_datas")
                      .arg(DataBase::nameTableTwofactorsColumnId)
                      .arg(DataBase::nameTableTwofactorsColumnTwofactor)
                      .arg(DataBase::nameTableTwofactorsColumnSalt)
                      .arg(DataBase::nameTableTwofactorsColumnIV)
                      .arg(DataBase::nameTableTwofactors)
                      .arg(DataBase::nameTableTwofactorsColumnIdDatas));
    query.bindValue(":id_datas", data.id);
    query.exec();

    Twofactors *twofactors = new Twofactors;
    twofactors->data = &data;
    data.twofactors = twofactors;
    while (query.next()) {
        Twofactor *twofactor = new Twofactor;
        twofactor->id = query.value(0).toUInt();
        twofactor->twofactor = query.value(1).toByteArray();
        twofactor->salt = query.value(2).toByteArray();
        twofactor->iv = query.value(3).toByteArray();
        twofactor->twofactors = twofactors;
        twofactors->twofactors.push_back(twofactor);
    }
}

void DataBase::getSecrets(Data &data)
{
    QSqlQuery query(DataBase::db);
    query.prepare(QString("SELECT \"%1\", \"%2\", \"%3\", \"%4\" FROM \"%5\" WHERE \"%6\" = :id_datas")
                      .arg(DataBase::nameTableSecretsColumnId)
                      .arg(DataBase::nameTableSecretsColumnSecret)
                      .arg(DataBase::nameTableSecretsColumnSalt)
                      .arg(DataBase::nameTableSecretsColumnIV)
                      .arg(DataBase::nameTableSecrets)
                      .arg(DataBase::nameTableSecretsColumnIdDatas));
    query.bindValue(":id_datas", data.id);
    query.exec();

    Secrets *secrets = new Secrets;
    secrets->data = &data;
    data.secrets = secrets;
    while (query.next()) {
        Secret *secret = new Secret;
        secret->id = query.value(0).toUInt();
        secret->secret = query.value(1).toByteArray();
        secret->salt = query.value(2).toByteArray();
        secret->iv = query.value(3).toByteArray();
        secret->secrets = secrets;
        secrets->secrets.push_back(secret);
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
    QSqlQuery query(DataBase::db);
    query.prepare("SELECT sql FROM sqlite_master WHERE type = 'table' AND name = :name");
    query.bindValue(":name", name);
    query.exec();

    if (query.next()) {
        QString response = query.value(0).toString();
        return response == requestCreate;
    }
    return false;
}

void DataBase::createTable(const QString &request)
{
    QSqlQuery query(DataBase::db);
    query.exec(request);
}

void DataBase::deleteTable(const QString &name)
{
    QSqlQuery query(DataBase::db);
    query.exec(QString("DROP TABLE \"%1\"").arg(name));
}

QString DataBase::createRequestCreateTableDatas()
{
    return QString("CREATE TABLE \"%1\" ("
                   "\"%2\" INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "\"%3\" BLOB, "
                   "\"%4\" BLOB, "
                   "\"%5\" BLOB)")
        .arg(DataBase::nameTableDatas)
        .arg(DataBase::nameTableDatasColumnId)
        .arg(DataBase::nameTableDatasColumnName)
        .arg(DataBase::nameTableDatasColumnSalt)
        .arg(DataBase::nameTableDatasColumnIV);
}

QString DataBase::createRequestCreateTableLogins()
{
    return DataBase::createRequestCreateTable(DataBase::nameTableLogins,
                                              DataBase::nameTableLoginsColumnId,
                                              DataBase::nameTableLoginsColumnIdDatas,
                                              DataBase::nameTableDatas,
                                              DataBase::nameTableDatasColumnId,
                                              DataBase::nameTableLoginsColumnLogin,
                                              DataBase::nameTableLoginsColumnSalt,
                                              DataBase::nameTableLoginsColumnIV);
}

QString DataBase::createRequestCreateTablePasswords()
{
    return DataBase::createRequestCreateTable(DataBase::nameTablePasswords,
                                              DataBase::nameTablePasswordsColumnId,
                                              DataBase::nameTablePasswordsColumnIdDatas,
                                              DataBase::nameTableDatas,
                                              DataBase::nameTableDatasColumnId,
                                              DataBase::nameTablePasswordsColumnPassword,
                                              DataBase::nameTablePasswordsColumnSalt,
                                              DataBase::nameTablePasswordsColumnIV);
}

QString DataBase::createRequestCreateTableMails()
{
    return DataBase::createRequestCreateTable(DataBase::nameTableMails,
                                              DataBase::nameTableMailsColumnId,
                                              DataBase::nameTableMailsColumnIdDatas,
                                              DataBase::nameTableDatas,
                                              DataBase::nameTableDatasColumnId,
                                              DataBase::nameTableMailsColumnMail,
                                              DataBase::nameTableMailsColumnSalt,
                                              DataBase::nameTableMailsColumnIV);
}

QString DataBase::createRequestCreateTableTelephones()
{
    return DataBase::createRequestCreateTable(DataBase::nameTableTelephones,
                                              DataBase::nameTableTelephonesColumnId,
                                              DataBase::nameTableTelephonesColumnIdDatas,
                                              DataBase::nameTableDatas,
                                              DataBase::nameTableDatasColumnId,
                                              DataBase::nameTableTelephonesColumnTelephone,
                                              DataBase::nameTableTelephonesColumnSalt,
                                              DataBase::nameTableTelephonesColumnIV);
}

QString DataBase::createRequestCreateTableTwofactors()
{
    return DataBase::createRequestCreateTable(DataBase::nameTableTwofactors,
                                              DataBase::nameTableTwofactorsColumnId,
                                              DataBase::nameTableTwofactorsColumnIdDatas,
                                              DataBase::nameTableDatas,
                                              DataBase::nameTableDatasColumnId,
                                              DataBase::nameTableTwofactorsColumnTwofactor,
                                              DataBase::nameTableTwofactorsColumnSalt,
                                              DataBase::nameTableTwofactorsColumnIV);
}

QString DataBase::createRequestCreateTableSecrets()
{
    return DataBase::createRequestCreateTable(DataBase::nameTableSecrets,
                                              DataBase::nameTableSecretsColumnId,
                                              DataBase::nameTableSecretsColumnIdDatas,
                                              DataBase::nameTableDatas,
                                              DataBase::nameTableDatasColumnId,
                                              DataBase::nameTableSecretsColumnSecret,
                                              DataBase::nameTableSecretsColumnSalt,
                                              DataBase::nameTableSecretsColumnIV);
}

QString DataBase::createRequestCreateTable(const QString &nameTable,
                                           const QString &nameColumnId,
                                           const QString &nameColumnKey,
                                           const QString &nameTableDatas,
                                           const QString &nameTableDatasColumnId,
                                           const QString &nameColumnInformation,
                                           const QString &saltColumnName,
                                           const QString &ivColumnName)
{
    return QString("CREATE TABLE \"%1\" ("
                   "\"%2\" INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "\"%3\" INTEGER REFERENCES \"%4\" (\"%5\") ON DELETE CASCADE ON UPDATE CASCADE, "
                   "\"%6\" BLOB, "
                   "\"%7\" BLOB, "
                   "\"%8\" BLOB)")
        .arg(nameTable)
        .arg(nameColumnId)
        .arg(nameColumnKey)
        .arg(nameTableDatas)
        .arg(nameTableDatasColumnId)
        .arg(nameColumnInformation)
        .arg(saltColumnName)
        .arg(ivColumnName);
}
