#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <Functions.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void output (const QString& value);                                  //method for output duplicates in widget list
    void Compare(MyMap & Hash);                                          //method for bucket members comparison

private slots:
    void on_DirChooseLeft_doubleClicked(const QModelIndex &index);

    void on_DirChooseRight_doubleClicked(const QModelIndex &index);

    void on_Check_btn_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
};

#endif // MAINWINDOW_H
