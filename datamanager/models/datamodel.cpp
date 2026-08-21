#include "datamodel.h"

#include "../database/database.h"

DataModel::DataModel(QObject *parent) : QAbstractItemModel{parent}, datas(nullptr)
{
    readDataBase();
}

DataModel::~DataModel()
{
    deleteDatas();
}

QModelIndex DataModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    Abstract *parentNode = nullptr;
    if (!parent.isValid()) {
        parentNode = datas;
    } else {
        parentNode = static_cast<Abstract*>(parent.internalPointer());
    }

    if (row < 0 || row >= getCountChildrens(parentNode)) {
        return QModelIndex();
    }

    return createIndex(row, column, getChildren(parentNode, row));
}

QModelIndex DataModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) {
        return QModelIndex();
    }

    Abstract *childNode = static_cast<Abstract*>(child.internalPointer());
    Abstract *parentNode = getParent(childNode);

    if (parentNode == datas || parentNode == nullptr) {
        return QModelIndex();
    }

    Abstract *grandParent = getParent(parentNode);
    if (!grandParent) {
        return QModelIndex();
    }

    int row = getRow(grandParent, parentNode);
    return createIndex(row, 0, parentNode);
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) {
        return 0;
    }

    Abstract *parentNode = nullptr;
    if (!parent.isValid()) {
        parentNode = datas;
    } else {
        parentNode = static_cast<Abstract*>(parent.internalPointer());
    }

    return getCountChildrens(parentNode);
}

int DataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    Abstract *node = static_cast<Abstract*>(index.internalPointer());

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return node->getData();
    }

    return QVariant();
}

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    Abstract *node = static_cast<Abstract*>(index.internalPointer());
    Qt::ItemFlags defaultFlags = QAbstractItemModel::flags(index);

    bool noEditable = isNoEdit(node);

    if (noEditable) {
        return defaultFlags;
    } else {
        return defaultFlags | Qt::ItemIsEditable;
    }
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0) {
            return QVariant("Информация");
        }
    }
    return QVariant();
}

bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole) {
        return false;
    }

    Abstract *node = static_cast<Abstract*>(index.internalPointer());
    if (!node) {
        return false;
    }

    QByteArray newValue = value.toByteArray();

    setDataAbstract(node, newValue);

    emit dataChanged(index, index, {role});
    return true;
}

bool DataModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || count != 1) {
        return false;
    }

    Abstract *parentNode = nullptr;
    if (!parent.isValid()) {
        parentNode = datas;
    } else {
        parentNode = static_cast<Abstract*>(parent.internalPointer());
    }

    int totalChildren = getCountChildrens(parentNode);
    if (row >= totalChildren) {
        return false;
    }

    if (isNoEdit(getChildren(parentNode, row))) {
        return false;
    }

    bool success = false;

    beginRemoveRows(parent, row, row);

    success = removeAbstract(parentNode, row);

    endRemoveRows();

    return success;
}

QModelIndex DataModel::addNewItem(const QModelIndex &index)
{
    Abstract *node = nullptr;
    if (index.isValid()) {
        node = static_cast<Abstract*>(index.internalPointer());
    }

    Datas *_Datas = dynamic_cast<Datas*>(node);
    Data *_Data = dynamic_cast<Data*>(node);
    if (!node || _Datas || _Data) {
        int newRow = datas->datas.size();
        beginInsertRows(QModelIndex(), newRow, newRow);

        Data *_Data = new Data();
        _Data->datas = datas;
        _Data->logins = new Logins();
        _Data->logins->data = _Data;
        _Data->mails = new Mails();
        _Data->mails->data = _Data;
        _Data->passwords = new Passwords();
        _Data->passwords->data = _Data;
        _Data->secrets = new Secrets();
        _Data->secrets->data = _Data;
        _Data->telephones = new Telephones();
        _Data->telephones->data = _Data;
        _Data->twofactors = new Twofactors();
        _Data->twofactors->data = _Data;
        datas->datas.push_back(_Data);

        endInsertRows();
        return this->index(newRow, 0, QModelIndex());
    }
    Logins *_Logins = dynamic_cast<Logins*>(node);
    if (_Logins) {
        int newRow = _Logins->logins.size();
        beginInsertRows(index, newRow, newRow);

        Login *_Login = new Login;
        _Login->logins = _Logins;
        _Logins->logins.push_back(_Login);

        endInsertRows();
        return this->index(newRow, 0, index);
    }
    Login *_Login = dynamic_cast<Login*>(node);
    if (_Login) {
        Logins *_Logins = _Login->logins;
        int newRow = _Logins->logins.size();
        beginInsertRows(index.parent(), newRow, newRow);

        Login *_Login = new Login;
        _Login->logins = _Logins;
        _Logins->logins.push_back(_Login);

        endInsertRows();
        return this->index(newRow, 0, index.parent());
    }
    Mails *_Mails = dynamic_cast<Mails*>(node);
    if (_Mails) {
        int newRow = _Mails->mails.size();
        beginInsertRows(index, newRow, newRow);

        Mail *_Mail = new Mail;
        _Mail->mails = _Mails;
        _Mails->mails.push_back(_Mail);

        endInsertRows();
        return this->index(newRow, 0, index);
    }
    Mail *_MailNode = dynamic_cast<Mail*>(node);
    if (_MailNode) {
        Mails *_Mails = _MailNode->mails;
        int newRow = _Mails->mails.size();
        beginInsertRows(index.parent(), newRow, newRow);

        Mail *_Mail = new Mail;
        _Mail->mails = _Mails;
        _Mails->mails.push_back(_Mail);

        endInsertRows();
        return this->index(newRow, 0, index.parent());
    }
    Passwords *_Passwords = dynamic_cast<Passwords*>(node);
    if (_Passwords) {
        int newRow = _Passwords->passwords.size();
        beginInsertRows(index, newRow, newRow);

        Password *_Password = new Password;
        _Password->passwords = _Passwords;
        _Passwords->passwords.push_back(_Password);

        endInsertRows();
        return this->index(newRow, 0, index);
    }
    Password *_PasswordNode = dynamic_cast<Password*>(node);
    if (_PasswordNode) {
        Passwords *_Passwords = _PasswordNode->passwords;
        int newRow = _Passwords->passwords.size();
        beginInsertRows(index.parent(), newRow, newRow);

        Password *_Password = new Password;
        _Password->passwords = _Passwords;
        _Passwords->passwords.push_back(_Password);

        endInsertRows();
        return this->index(newRow, 0, index.parent());
    }
    Secrets *_Secrets = dynamic_cast<Secrets*>(node);
    if (_Secrets) {
        int newRow = _Secrets->secrets.size();
        beginInsertRows(index, newRow, newRow);

        Secret *_Secret = new Secret;
        _Secret->secrets = _Secrets;
        _Secrets->secrets.push_back(_Secret);

        endInsertRows();
        return this->index(newRow, 0, index);
    }
    Secret *_SecretNode = dynamic_cast<Secret*>(node);
    if (_SecretNode) {
        Secrets *_Secrets = _SecretNode->secrets;
        int newRow = _Secrets->secrets.size();
        beginInsertRows(index.parent(), newRow, newRow);

        Secret *_Secret = new Secret;
        _Secret->secrets = _Secrets;
        _Secrets->secrets.push_back(_Secret);

        endInsertRows();
        return this->index(newRow, 0, index.parent());
    }
    Telephones *_Telephones = dynamic_cast<Telephones*>(node);
    if (_Telephones) {
        int newRow = _Telephones->telephones.size();
        beginInsertRows(index, newRow, newRow);

        Telephone *_Telephone = new Telephone;
        _Telephone->telephones = _Telephones;
        _Telephones->telephones.push_back(_Telephone);

        endInsertRows();
        return this->index(newRow, 0, index);
    }
    Telephone *_TelephoneNode = dynamic_cast<Telephone*>(node);
    if (_TelephoneNode) {
        Telephones *_Telephones = _TelephoneNode->telephones;
        int newRow = _Telephones->telephones.size();
        beginInsertRows(index.parent(), newRow, newRow);

        Telephone *_Telephone = new Telephone;
        _Telephone->telephones = _Telephones;
        _Telephones->telephones.push_back(_Telephone);

        endInsertRows();
        return this->index(newRow, 0, index.parent());
    }
    Twofactors *_Twofactors = dynamic_cast<Twofactors*>(node);
    if (_Twofactors) {
        int newRow = _Twofactors->twofactors.size();
        beginInsertRows(index, newRow, newRow);

        Twofactor *_Twofactor = new Twofactor;
        _Twofactor->twofactors = _Twofactors;
        _Twofactors->twofactors.push_back(_Twofactor);

        endInsertRows();
        return this->index(newRow, 0, index);
    }
    Twofactor *_TwofactorNode = dynamic_cast<Twofactor*>(node);
    if (_TwofactorNode) {
        Twofactors *_Twofactors = _TwofactorNode->twofactors;
        int newRow = _Twofactors->twofactors.size();
        beginInsertRows(index.parent(), newRow, newRow);

        Twofactor *_Twofactor = new Twofactor;
        _Twofactor->twofactors = _Twofactors;
        _Twofactors->twofactors.push_back(_Twofactor);

        endInsertRows();
        return this->index(newRow, 0, index.parent());
    }

    return QModelIndex();
}

void DataModel::writeDataBase()
{
    DataBase::write(*datas);
}

void DataModel::readDataBase()
{
    beginResetModel();
    deleteDatas();
    datas = DataBase::read();
    endResetModel();
}

void DataModel::encryptData(const QByteArray &password)
{
    beginResetModel();

    for (Data *_Data : datas->datas) {
        _Data->name = _Data->encrypt(password);

        for (Login *_Login : _Data->logins->logins) {
            _Login->login = _Login->encrypt(password);
        }
        for (Mail *_Mail : _Data->mails->mails) {
            _Mail->mail = _Mail->encrypt(password);
        }
        for (Password *_Password : _Data->passwords->passwords) {
            _Password->password = _Password->encrypt(password);
        }
        for (Secret *_Secret : _Data->secrets->secrets) {
            _Secret->secret = _Secret->encrypt(password);
        }
        for (Telephone *_Telephone : _Data->telephones->telephones) {
            _Telephone->telephone = _Telephone->encrypt(password);
        }
        for (Twofactor *_Twofactor : _Data->twofactors->twofactors) {
            _Twofactor->twofactor = _Twofactor->encrypt(password);
        }
    }

    endResetModel();
}

void DataModel::decryptData(const QByteArray &password)
{
    beginResetModel();

    for (Data *_Data : datas->datas) {
        _Data->name = _Data->decrypt(password);

        for (Login *_Login : _Data->logins->logins) {
            _Login->login = _Login->decrypt(password);
        }
        for (Mail *_Mail : _Data->mails->mails) {
            _Mail->mail = _Mail->decrypt(password);
        }
        for (Password *_Password : _Data->passwords->passwords) {
            _Password->password = _Password->decrypt(password);
        }
        for (Secret *_Secret : _Data->secrets->secrets) {
            _Secret->secret = _Secret->decrypt(password);
        }
        for (Telephone *_Telephone : _Data->telephones->telephones) {
            _Telephone->telephone = _Telephone->decrypt(password);
        }
        for (Twofactor *_Twofactor : _Data->twofactors->twofactors) {
            _Twofactor->twofactor = _Twofactor->decrypt(password);
        }
    }

    endResetModel();
}

void DataModel::deleteDatas()
{
    if (datas) {
        delete datas;
        datas = nullptr;
    }
}

int DataModel::getCountChildrens(const Abstract *abstract) const
{
    const Datas *_Datas = dynamic_cast<const Datas*>(abstract);
    if (_Datas) {
        return _Datas->datas.size();
    }
    const Data *_Data = dynamic_cast<const Data*>(abstract);
    if (_Data) {
        return 6;
    }
    const Logins *_Logins = dynamic_cast<const Logins*>(abstract);
    if (_Logins) {
        return _Logins->logins.size();
    }
    const Login *_Login = dynamic_cast<const Login*>(abstract);
    if (_Login) {
        return 0;
    }
    const Mails *_Mails = dynamic_cast<const Mails*>(abstract);
    if (_Mails) {
        return _Mails->mails.size();
    }
    const Mail *_Mail = dynamic_cast<const Mail*>(abstract);
    if (_Mail) {
        return 0;
    }
    const Passwords *_Passwords = dynamic_cast<const Passwords*>(abstract);
    if (_Passwords) {
        return _Passwords->passwords.size();
    }
    const Password *_Password = dynamic_cast<const Password*>(abstract);
    if (_Password) {
        return 0;
    }
    const Secrets *_Secrets = dynamic_cast<const Secrets*>(abstract);
    if (_Secrets) {
        return _Secrets->secrets.size();
    }
    const Secret *_Secret = dynamic_cast<const Secret*>(abstract);
    if (_Secret) {
        return 0;
    }
    const Telephones *_Telephones = dynamic_cast<const Telephones*>(abstract);
    if (_Telephones) {
        return _Telephones->telephones.size();
    }
    const Telephone *_Telephone = dynamic_cast<const Telephone*>(abstract);
    if (_Telephone) {
        return 0;
    }
    const Twofactors *_Twofactors = dynamic_cast<const Twofactors*>(abstract);
    if (_Twofactors) {
        return _Twofactors->twofactors.size();
    }
    const Twofactor *_Twofactor = dynamic_cast<const Twofactor*>(abstract);
    if (_Twofactor) {
        return 0;
    }

    return 0;
}

Abstract *DataModel::getParent(const Abstract *abstract) const
{
    const Datas *_Datas = dynamic_cast<const Datas*>(abstract);
    if (_Datas) {
        return nullptr;
    }
    const Data *_Data = dynamic_cast<const Data*>(abstract);
    if (_Data) {
        return _Data->datas;
    }
    const Logins *_Logins = dynamic_cast<const Logins*>(abstract);
    if (_Logins) {
        return _Logins->data;
    }
    const Login *_Login = dynamic_cast<const Login*>(abstract);
    if (_Login) {
        return _Login->logins;
    }
    const Mails *_Mails = dynamic_cast<const Mails*>(abstract);
    if (_Mails) {
        return _Mails->data;
    }
    const Mail *_Mail = dynamic_cast<const Mail*>(abstract);
    if (_Mail) {
        return _Mail->mails;
    }
    const Passwords *_Passwords = dynamic_cast<const Passwords*>(abstract);
    if (_Passwords) {
        return _Passwords->data;
    }
    const Password *_Password = dynamic_cast<const Password*>(abstract);
    if (_Password) {
        return _Password->passwords;
    }
    const Secrets *_Secrets = dynamic_cast<const Secrets*>(abstract);
    if (_Secrets) {
        return _Secrets->data;
    }
    const Secret *_Secret = dynamic_cast<const Secret*>(abstract);
    if (_Secret) {
        return _Secret->secrets;
    }
    const Telephones *_Telephones = dynamic_cast<const Telephones*>(abstract);
    if (_Telephones) {
        return _Telephones->data;
    }
    const Telephone *_Telephone = dynamic_cast<const Telephone*>(abstract);
    if (_Telephone) {
        return _Telephone->telephones;
    }
    const Twofactors *_Twofactors = dynamic_cast<const Twofactors*>(abstract);
    if (_Twofactors) {
        return _Twofactors->data;
    }
    const Twofactor *_Twofactor = dynamic_cast<const Twofactor*>(abstract);
    if (_Twofactor) {
        return _Twofactor->twofactors;
    }

    return nullptr;
}

Abstract *DataModel::getChildren(const Abstract *abstract, const int &row) const
{
    const Datas *_Datas = dynamic_cast<const Datas*>(abstract);
    if (_Datas) {
        return _Datas->datas[row];
    }
    const Data *_Data = dynamic_cast<const Data*>(abstract);
    if (_Data) {
        if (row == 0) {
            return _Data->logins;
        } else if (row == 1) {
            return _Data->mails;
        } else if (row == 2) {
            return _Data->passwords;
        } else if (row == 3) {
            return _Data->secrets;
        } else if (row == 4) {
            return _Data->telephones;
        } else if (row == 5) {
            return _Data->twofactors;
        }
        return nullptr;
    }
    const Logins *_Logins = dynamic_cast<const Logins*>(abstract);
    if (_Logins) {
        return _Logins->logins[row];
    }
    const Login *_Login = dynamic_cast<const Login*>(abstract);
    if (_Login) {
        return nullptr;
    }
    const Mails *_Mails = dynamic_cast<const Mails*>(abstract);
    if (_Mails) {
        return _Mails->mails[row];
    }
    const Mail *_Mail = dynamic_cast<const Mail*>(abstract);
    if (_Mail) {
        return nullptr;
    }
    const Passwords *_Passwords = dynamic_cast<const Passwords*>(abstract);
    if (_Passwords) {
        return _Passwords->passwords[row];
    }
    const Password *_Password = dynamic_cast<const Password*>(abstract);
    if (_Password) {
        return nullptr;
    }
    const Secrets *_Secrets = dynamic_cast<const Secrets*>(abstract);
    if (_Secrets) {
        return _Secrets->secrets[row];
    }
    const Secret *_Secret = dynamic_cast<const Secret*>(abstract);
    if (_Secret) {
        return nullptr;
    }
    const Telephones *_Telephones = dynamic_cast<const Telephones*>(abstract);
    if (_Telephones) {
        return _Telephones->telephones[row];
    }
    const Telephone *_Telephone = dynamic_cast<const Telephone*>(abstract);
    if (_Telephone) {
        return nullptr;
    }
    const Twofactors *_Twofactors = dynamic_cast<const Twofactors*>(abstract);
    if (_Twofactors) {
        return _Twofactors->twofactors[row];
    }
    const Twofactor *_Twofactor = dynamic_cast<const Twofactor*>(abstract);
    if (_Twofactor) {
        return nullptr;
    }

    return nullptr;
}

int DataModel::getRow(const Abstract *parent, const Abstract *children) const
{
    const Datas *_Datas = dynamic_cast<const Datas*>(parent);
    if (_Datas) {
        return _Datas->datas.indexOf(children);
    }
    const Data *_Data = dynamic_cast<const Data*>(parent);
    if (_Data) {
        const Logins *__Logins = dynamic_cast<const Logins*>(children);
        if (__Logins) {
            return 0;
        }
        const Mails *__Mails = dynamic_cast<const Mails*>(children);
        if (__Mails) {
            return 1;
        }
        const Passwords *__Passwords = dynamic_cast<const Passwords*>(children);
        if (__Passwords) {
            return 2;
        }
        const Secrets *__Secrets = dynamic_cast<const Secrets*>(children);
        if (__Secrets) {
            return 3;
        }
        const Telephones *__Telephones = dynamic_cast<const Telephones*>(children);
        if (__Telephones) {
            return 4;
        }
        const Twofactors *__Twofactors = dynamic_cast<const Twofactors*>(children);
        if (__Twofactors) {
            return 5;
        }
        return -1;
    }
    const Logins *_Logins = dynamic_cast<const Logins*>(parent);
    if (_Logins) {
        return _Logins->logins.indexOf(children);
    }
    const Login *_Login = dynamic_cast<const Login*>(parent);
    if (_Login) {
        return -1;
    }
    const Mails *_Mails = dynamic_cast<const Mails*>(parent);
    if (_Mails) {
        return _Mails->mails.indexOf(children);
    }
    const Mail *_Mail = dynamic_cast<const Mail*>(parent);
    if (_Mail) {
        return -1;
    }
    const Passwords *_Passwords = dynamic_cast<const Passwords*>(parent);
    if (_Passwords) {
        return _Passwords->passwords.indexOf(children);
    }
    const Password *_Password = dynamic_cast<const Password*>(parent);
    if (_Password) {
        return -1;
    }
    const Secrets *_Secrets = dynamic_cast<const Secrets*>(parent);
    if (_Secrets) {
        return _Secrets->secrets.indexOf(children);
    }
    const Secret *_Secret = dynamic_cast<const Secret*>(parent);
    if (_Secret) {
        return -1;
    }
    const Telephones *_Telephones = dynamic_cast<const Telephones*>(parent);
    if (_Telephones) {
        return _Telephones->telephones.indexOf(children);
    }
    const Telephone *_Telephone = dynamic_cast<const Telephone*>(parent);
    if (_Telephone) {
        return -1;
    }
    const Twofactors *_Twofactors = dynamic_cast<const Twofactors*>(parent);
    if (_Twofactors) {
        return _Twofactors->twofactors.indexOf(children);
    }
    const Twofactor *_Twofactor = dynamic_cast<const Twofactor*>(parent);
    if (_Twofactor) {
        return -1;
    }

    return -1;
}

void DataModel::setDataAbstract(Abstract *abstract, const QByteArray &data)
{
    Data *_Data = dynamic_cast<Data*>(abstract);
    if (_Data) {
        _Data->name = data;
        return;
    }
    Login *_Login = dynamic_cast<Login*>(abstract);
    if (_Login) {
        _Login->login = data;
        return;
    }
    Mail *_Mail = dynamic_cast<Mail*>(abstract);
    if (_Mail) {
        _Mail->mail = data;
        return;
    }
    Password *_Password = dynamic_cast<Password*>(abstract);
    if (_Password) {
        _Password->password = data;
        return;
    }
    Secret *_Secret = dynamic_cast<Secret*>(abstract);
    if (_Secret) {
        _Secret->secret = data;
        return;
    }
    Telephone *_Telephone = dynamic_cast<Telephone*>(abstract);
    if (_Telephone) {
        _Telephone->telephone = data;
        return;
    }
    Twofactor *_Twofactor = dynamic_cast<Twofactor*>(abstract);
    if (_Twofactor) {
        _Twofactor->twofactor = data;
        return;
    }
}

bool DataModel::removeAbstract(Abstract *parent, const int &row)
{
    Datas *datas = dynamic_cast<Datas*>(parent);
    if (datas) {
        Data *data = datas->datas[row];
        datas->datas.removeAt(row);
        delete data;
        return true;
    }
    Logins *logins = dynamic_cast<Logins*>(parent);
    if (logins) {
        Login *login = logins->logins[row];
        logins->logins.removeAt(row);
        delete login;
        return true;
    }
    Mails *mails = dynamic_cast<Mails*>(parent);
    if (mails) {
        Mail *mail = mails->mails[row];
        mails->mails.removeAt(row);
        delete mail;
        return true;
    }
    Passwords *passwords = dynamic_cast<Passwords*>(parent);
    if (passwords) {
        Password *password = passwords->passwords[row];
        passwords->passwords.removeAt(row);
        delete password;
        return true;
    }
    Secrets *secrets = dynamic_cast<Secrets*>(parent);
    if (secrets) {
        Secret *secret = secrets->secrets[row];
        secrets->secrets.removeAt(row);
        delete secret;
        return true;
    }
    Telephones *telephones = dynamic_cast<Telephones*>(parent);
    if (telephones) {
        Telephone *telephone = telephones->telephones[row];
        telephones->telephones.removeAt(row);
        delete telephone;
        return true;
    }
    Twofactors *twofactors = dynamic_cast<Twofactors*>(parent);
    if (twofactors) {
        Twofactor *twofactor = twofactors->twofactors[row];
        twofactors->twofactors.removeAt(row);
        delete twofactor;
        return true;
    }

    return false;
}

bool DataModel::isNoEdit(const Abstract *abstract) const
{
    const Logins *logins = dynamic_cast<const Logins*>(abstract);
    const Mails *mails = dynamic_cast<const Mails*>(abstract);
    const Passwords *passwords = dynamic_cast<const Passwords*>(abstract);
    const Secrets *secrets = dynamic_cast<const Secrets*>(abstract);
    const Telephones *telephones = dynamic_cast<const Telephones*>(abstract);
    const Twofactors *twofactors = dynamic_cast<const Twofactors*>(abstract);

    return (logins || mails || passwords || secrets || telephones || twofactors);
}
