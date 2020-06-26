#include "ui_mainwindow.h"
#include <QMainWindow>
#include "WorkerObject.h"
#include "mainwindow.h"
#include "waitingspinnerwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);                                         //allocate memory for QFileSystemModel object model
    model->setFilter(QDir::QDir::AllEntries);                                   //set filter 'AllEntries' to see all files in current directory
    model->setRootPath("");                                                     //this method helps to observe all the changes in current directory permamently
    ui->DirChooseRight->setModel(model);                                        //set both view lists
    ui->DirChooseLeft->setModel(model);

    b_worker = new Worker;
    connect(this, &MainWindow::startOpeartion, b_worker, &Worker::CallAll);     //connects and slots for another thread. After b_worker's job is done
    connect(b_worker, &Worker::SendData, this,&MainWindow::GetData);            //...main thread will recieve hash table with onle duplicates in it
    thread1=new QThread();
    connect(this, &MainWindow::destroyed, thread1, &QThread::quit);
    b_worker->moveToThread(thread1);
    thread1->start( QThread::HighPriority);
    spinner = new WaitingSpinnerWidget(ui->ResultList);
}

MainWindow::~MainWindow()
{
    delete ui;
    thread1->quit();
    thread1->wait();
}


void MainWindow::on_DirChooseLeft_doubleClicked(const QModelIndex &index)           //this method makes possible to navigate the file system
{
    QListView* listView = (QListView*)sender();
    QFileInfo fileinfo =  model->fileInfo(index);
    if (fileinfo.fileName() == "..")                                                //double click on two dots to view the upper directory...
        {
            QDir dir = fileinfo.dir();
            dir.cd("..");
            listView->setRootIndex(model->index(dir.absolutePath()));
        }
    else if (fileinfo.fileName()== ".")                                             //...one dot to view the root...
        {
            listView->setRootIndex(model->index(""));
        }
    else if (fileinfo.isDir())                                                      //...and any directory to view what it contains...
        {
            listView->setRootIndex(index);
        }
}

void MainWindow::on_DirChooseRight_doubleClicked(const QModelIndex &index)          //...same for the second list view
{
    MainWindow::on_DirChooseLeft_doubleClicked(index);
}

void MainWindow::on_Check_btn_clicked()
{
    ui->ResultList->clear();
    spinner->start();
    ui->Warning_lbl->setText("The search may take time... Please wait for a while");
    ui->Check_btn->setEnabled(false);
    QString FirstDir = model->filePath(ui->DirChooseLeft->rootIndex());             //get directories from the list views
    QString SecondDir = model->filePath(ui->DirChooseRight->rootIndex());                                                                 
    emit startOpeartion(FirstDir,SecondDir);
}

void MainWindow::GetData()
{
    FinalMainHash= b_worker->Hash;
    output();
    ui->Check_btn->setEnabled(true);
    spinner->stop();
    ui->Warning_lbl->setText("Done! You can open file directory by double click on it");
}

void MainWindow::output()                                                           //sets the icons (from file info) and also absolute file names as text in the items...
{                                                                                   //...then add generated items to the 'ResultList' widget
    for(auto it=FinalMainHash.begin();it!=FinalMainHash.end(); ++it)
    {
    QListWidgetItem *item = new QListWidgetItem(ui->ResultList);
    item->setText(it.value());
    QFileInfo finfo(it.value());
    QFileIconProvider ip;
    QIcon ic=ip.icon(finfo);
    item->setIcon(ic);
    ui->ResultList->addItem(item);
    }
}

void MainWindow::on_ResultList_itemDoubleClicked(QListWidgetItem *item)
{
    QFileInfo FIleInfo(item->text());
    QDesktopServices::openUrl(QUrl("file:///" + FIleInfo.path()));
}

void MainWindow::on_Refresh_Btn_clicked()
{
    ui->DirChooseLeft->reset();
    ui->DirChooseRight->reset();
    ui->ResultList->reset();
}

