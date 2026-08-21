#ifndef ABSTRACT_H
#define ABSTRACT_H

#include <QString>
#include <QRandomGenerator>

#include "../../aes/qaesencryption.h"

#include <QDebug>

struct Abstract {
    Abstract():
        salt(16, 0),
        iv(16, 0)
    {
        QRandomGenerator::system()->fillRange(reinterpret_cast<quint32*>(salt.data()), salt.size() / sizeof(quint32));
        QRandomGenerator::system()->fillRange(reinterpret_cast<quint32*>(iv.data()), iv.size() / sizeof(quint32));
    };

    virtual QByteArray getData() const = 0;

    QByteArray encrypt(const QByteArray &password)
    {
        QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC, QAESEncryption::PKCS7);
        QByteArray key = QAESEncryption::generateKey(password, salt, QAESEncryption::AES_256);
        return encryption.encode(getData(), key, iv);
    };
    QByteArray decrypt(const QByteArray &password)
    {
        QAESEncryption decryption(QAESEncryption::AES_256, QAESEncryption::CBC, QAESEncryption::PKCS7);
        QByteArray key = QAESEncryption::generateKey(password, salt, QAESEncryption::AES_256);
        QByteArray decrypted = decryption.decode(getData(), key, iv);
        return decryption.removePadding(decrypted);
    };

    QByteArray salt;
    QByteArray iv;
};

#endif // ABSTRACT_H
