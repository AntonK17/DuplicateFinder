#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void Compare(MyMap &Hash);                                          //method for bucket members comparison (from 'Hash'). It'll also call the 'output' function
    void output (const QString &StringPath);                            //method will add item at the 'ResultList' widget by the absoulute path name

private slots:
    void on_DirChooseLeft_doubleClicked(const QModelIndex &index);      //these slots are necessery for the file system navigation possibility
    void on_DirChooseRight_doubleClicked(const QModelIndex &index);
    void on_Check_btn_clicked();
    void on_ResultList_itemDoubleClicked(QListWidgetItem *item);        //folder which contain chosen file from the 'ResultList' will be open by double click on it
    void on_RefreshButton_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
};

#endif // MAINWINDOW_H
