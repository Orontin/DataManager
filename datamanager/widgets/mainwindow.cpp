#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../models/datamodel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Менеджер данных");

    ui->treeView->setModel(new DataModel);
    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->setStyleSheet(
        "QTreeView {"
        "    background-color: #1E1E1E;"
        "    alternate-background-color: #2D2D2D;"
        "    outline: none;"
        "    selection-background-color: transparent;"
        "}"
        "QTreeView::item {"
        "    background-color: #252526;"
        "    color: #FFFFFF;"
        "}"
        "QTreeView::item:alternate {"
        "    background-color: #2D2D2D;"
        "}"
        "QTreeView::item:selected {"
        "    border: 1px dotted #FFFFFF;"
        "    background-color: transparent;"
        "}"
        "QTreeView::item:hover {"
        "    background-color: #3A3A3A;"
        "}"
    );

    connect(ui->read, &QPushButton::clicked, this, &MainWindow::onRead, Qt::ConnectionType::DirectConnection);
    connect(ui->write, &QPushButton::clicked, this, &MainWindow::onWrite, Qt::ConnectionType::DirectConnection);
    connect(ui->encrypt, &QPushButton::clicked, this, &MainWindow::onEncrypt, Qt::ConnectionType::DirectConnection);
    connect(ui->decrypt, &QPushButton::clicked, this, &MainWindow::onDecrypt, Qt::ConnectionType::DirectConnection);

    ui->treeView->setModel(new DataModel);
}

MainWindow::~MainWindow()
{
    delete ui->treeView->model();
    ui->treeView->setModel(nullptr);
    delete ui;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        QTreeView *tree = ui->treeView;
        QAbstractItemModel *model = tree->model();
        QModelIndex currentIndex = tree->selectionModel()->currentIndex();
        if (currentIndex.isValid()) {
            model->removeRows(currentIndex.row(), 1, currentIndex.parent());
            event->accept();
            return;
        }
    } else if (event->key() == Qt::Key_Insert) {
        QTreeView *tree = ui->treeView;
        DataModel *model = static_cast<DataModel*>(tree->model());
        QModelIndex currentIndex = tree->selectionModel()->currentIndex();
        QModelIndex newIndex = model->addNewItem(currentIndex);
        if (newIndex.isValid()) {
            tree->setCurrentIndex(newIndex);
            tree->edit(newIndex);
        }
        event->accept();
        return;
    }

    QMainWindow::keyReleaseEvent(event);
}

void MainWindow::onRead()
{
    static_cast<DataModel*>(ui->treeView->model())->readDataBase();
}

void MainWindow::onWrite()
{
    static_cast<DataModel*>(ui->treeView->model())->writeDataBase();
}

void MainWindow::onEncrypt()
{
    static_cast<DataModel*>(ui->treeView->model())->encryptData(ui->encryptSecret->text().toUtf8());
}

void MainWindow::onDecrypt()
{
    static_cast<DataModel*>(ui->treeView->model())->decryptData(ui->decrypSecret->text().toUtf8());
}


