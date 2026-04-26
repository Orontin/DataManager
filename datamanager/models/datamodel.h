#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractItemModel>
#include <QObject>

#include "../database/structs/datas.h"

class DataModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DataModel(QObject *parent = nullptr);
    ~DataModel();

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QModelIndex addNewItem(const QModelIndex &index);

    void writeDataBase();
    void readDataBase();

    void encryptData(const QByteArray &password);
    void decryptData(const QByteArray &password);

private:
    Datas *datas;

    void deleteDatas();

    int getCountChildrens(const Abstract *abstract) const;
    Abstract *getParent(const Abstract *abstract) const;
    Abstract *getChildren(const Abstract *abstract, const int &row) const;
    int getRow(const Abstract *parent, const Abstract *children) const;
    void setDataAbstract(Abstract *abstract, const QByteArray &data);
    bool removeAbstract(Abstract *parent, const int &row);
    bool isNoEdit(const Abstract *abstract) const;
};

#endif // DATAMODEL_H
