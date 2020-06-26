#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <includes.h>
#include <WorkerObject.h>
#include <waitingspinnerwidget.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void startOpeartion(const QString&, const QString&);
private slots:
    void GetData();                                                      //this slot recieve data (Hash table with results) from 'thread1' process
    void on_DirChooseLeft_doubleClicked(const QModelIndex &index);       //these slots are necessery for the file system navigation possibility
    void on_DirChooseRight_doubleClicked(const QModelIndex &index);
    void on_Check_btn_clicked();
    void on_ResultList_itemDoubleClicked(QListWidgetItem *item);         //folder which contain chosen file from the 'ResultList' will be opened by double click on it
    void on_Refresh_Btn_clicked();

private:
    void output();                                                       //adds items from 'FinalMainHash' at the 'ResultList' widget
    MyMap FinalMainHash;
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    Worker *b_worker;
    QThread *thread1;
    WaitingSpinnerWidget *spinner;
};

#endif // MAINWINDOW_H
