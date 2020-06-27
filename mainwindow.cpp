#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backgroundworker.h"
#include <includes.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QFileSystemModel(this);                                         //allocate memory for QFileSystemModel object model
    model->setFilter(QDir::QDir::AllEntries);                                   //set filter 'AllEntries' to see all files in current directory
    model->setRootPath("");                                                     //this method helps to observe all the changes in current directory permamently
    ui->UpperList->setModel(model);                                             //set both view lists
    ui->LowerList->setModel(model);
    Worker *worker1=new Worker();
    Worker *worker2=new Worker();
    worker1->setMap(HashTable);
    worker2->setMap(HashTable);

    connect (this, &MainWindow::StartHashing1, worker1, &Worker::HashWorker);
    connect (worker1, &Worker::SendItem, this, &MainWindow::GetData);
    connect (this, &MainWindow::StartHashing2, worker2, &Worker::HashWorker);
    connect (worker2, &Worker::SendItem, this, &MainWindow::GetData);
    connect (worker1, &Worker::FinishedWork, this, &MainWindow::WorkerFinished);
    connect (worker2, &Worker::FinishedWork, this, &MainWindow::WorkerFinished);

    thread1=new QThread();
    thread2=new QThread();
    worker1->moveToThread(thread1);
    worker2->moveToThread(thread2);


    spinner = new WaitingSpinnerWidget(ui->ForSpinner);
    ui->ForSpinner->setStyleSheet("background color: transparent;");
    spinner->setInnerRadius(5);
    spinner->setLineLength(5);

    ui->SortButton->setEnabled(false);
    ui->StopButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    thread1->quit();
    thread2->quit();
    thread1->wait();
    thread2->wait();
    delete ui;
}

void MainWindow::on_UpperList_doubleClicked(const QModelIndex &index)
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

void MainWindow::on_LowerList_doubleClicked(const QModelIndex &index)
{
    MainWindow::on_UpperList_doubleClicked(index);
}

void MainWindow::on_CheckButton_clicked()
{
    thread1->start();
    thread2->start();
    HashTable.clear();
    ui->ResultList->clear();
    spinner->start();
    ui->SortButton->setEnabled(false);
    ui->CheckButton->setEnabled(false);
    QString FirstDir = model->filePath(ui->UpperList->rootIndex());                 //get directories names from the list views
    QString SecondDir = model->filePath(ui->LowerList->rootIndex());
    emit StartHashing1(FirstDir);
    emit StartHashing2(SecondDir);
    ui->StopButton->setEnabled(true);
    ui->HelperLabel->setText("Double click on file to open its directory in explorer");
}

bool MainWindow::IsDirNotDifferent(const QString &str1, const QString &str2)
{
    if((str1.contains(str2)) || (str2.contains(str1)))
        return true;
    else
        return false;
}

void MainWindow::on_RefreshButton_clicked()
{
    ui->UpperList->reset();
    ui->LowerList->reset();
    ui->ResultList->reset();
}

void MainWindow::on_ResultList_itemDoubleClicked(QListWidgetItem *item)
{
    QFileInfo FIleInfo(item->text());
    QDesktopServices::openUrl(QUrl("file:///" + FIleInfo.path()));
}

void MainWindow::GetData(const QString& itemPath, const QString& name)
{
    QListWidgetItem *item = new QListWidgetItem(ui->ResultList);
    item->setText(name + " ( " + itemPath + " ) ");
    QFileInfo finfo(itemPath);
    QFileIconProvider ip;
    QIcon ic=ip.icon(finfo);
    item->setIcon(ic);
    ui->ResultList->addItem(item);
}

void MainWindow::on_SortButton_clicked()
{
    ui->ResultList->sortItems(Qt::AscendingOrder);
}

void MainWindow::WorkerFinished()
{
    ++ThreadCounter;
    if (ThreadCounter == 2)
    {
        spinner->stop();
        ui->SortButton->setEnabled(true);
        ui->CheckButton->setEnabled(true);
        ui->StopButton->setEnabled(false);
        ThreadCounter=0;
    }
}

void MainWindow::on_StopButton_clicked()
{
    ui->StopButton->setEnabled(false);
    ui->HelperLabel->setText("Exiting...Please wait...");
    Mydelay();
    thread1->quit();
    thread2->quit();
    thread1->wait();
    thread2->wait();
    ui->CheckButton->setEnabled(true);
    ui->SortButton->setEnabled(true);
    spinner->stop();
    ui->HelperLabel->setText("Double click on file to open its directory in explorer");
}
