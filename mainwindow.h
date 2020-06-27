#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <includes.h>
#include <backgroundworker.h>
#include <waitingspinnerwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MyMap HashTable;
signals:
    void StartHashing1(const QString&);
    void StartHashing2(const QString&);
private slots:
    void WorkerFinished();
    void on_CheckButton_clicked();
    void on_RefreshButton_clicked();
    void on_ResultList_itemDoubleClicked(QListWidgetItem *item);
    void on_UpperList_doubleClicked(const QModelIndex &index);
    void on_LowerList_doubleClicked(const QModelIndex &index);
    void GetData(const QString&, const QString&);
    void on_SortButton_clicked();

    void on_StopButton_clicked();

private:
    short ThreadCounter=0;
    bool IsDirNotDifferent(const QString&, const QString&);
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    QThread *thread1;
    QThread *thread2;
    WaitingSpinnerWidget *spinner;
};
#endif // MAINWINDOW_H
