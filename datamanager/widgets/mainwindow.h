#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void onRead();
    void onWrite();
    void onEncrypt();
    void onDecrypt();

    void visibleDecryptClicked(bool checked);
    void visibleEncryptClicked(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
