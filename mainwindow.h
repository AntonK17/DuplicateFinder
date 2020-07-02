#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <includes.h>
#include <backgroundworker.h>
#include <waitingspinnerwidget.h>
#include <warningwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //shared HashTable for both threads
    MyMap HashTable;
    QList<QString> MainList;
signals:
    //signals for worker1 and worker2 to start their algorithms
    void StartHashing1(const QString &DirName, const QString &ExludeDirName, const bool &InsidersAllowed);
    void StartHashing2(const QString &DirName, const QString &ExludeDirName, const bool &InsidersAllowed);
    void AbortionStart();
    void CountDuplicatesSe();
private slots:

    //slots which recieve signals from workers for getting data from them
    void WorkerFinished();

    //  ui objects slots
    void on_CheckButton_clicked();
    void on_RefreshButton_clicked();
    void on_ResultList_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_UpperList_doubleClicked(const QModelIndex &index);
    void on_LowerList_doubleClicked(const QModelIndex &index);
    void on_SortButton_clicked();
    void on_StopButton_clicked();
    void on_UpperInsideDirs_toggled(bool checked);
    void on_LowerInsideDirs_toggled(bool checked);
    void on_LowerLine_textChanged(const QString &arg1);
    void on_UpperLine_textChanged(const QString &arg1);
    void on_ResultList_customContextMenuRequested(const QPoint &pos);

    //slots for
    void deleteFile(const bool&, const bool&);
    void DeleteEnabledChecker();

    void CountDuplicatesRe();


private:

    /*flags we getting from check boxes. false means algorithm won't check all directories inside
    the chosen one. Thread counter is needed for detection whether workers in threads finshed their tasks*/
    short ThreadCounter=0;
    short NumberOfThreads=2;
    bool InsidersAllowedFlag1=0;
    bool InsidersAllowedFlag2=0;
    bool IsDirNotDifferent(const QString &str1, const QString &str2);
    bool DeleteEnabled=0;
    int counting=0;
    WarningWindow *Ww;
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    QThread *thread1;
    QThread *thread2;
    WaitingSpinnerWidget *spinner;
    void GetData();
protected:
    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
