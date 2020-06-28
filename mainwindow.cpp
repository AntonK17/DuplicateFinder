#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backgroundworker.h"
#include <includes.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //create and set FileSystemModel
    model = new QFileSystemModel(this);
    model->setFilter(QDir::QDir::AllEntries);
    model->setRootPath("");
    ui->UpperList->setModel(model);
    ui->LowerList->setModel(model);

    //create workers and threads for them
    Worker *worker1=new Worker(HashTable);
    Worker *worker2=new Worker(HashTable);
    thread1=new QThread();
    thread2=new QThread();
    worker1->moveToThread(thread1);
    worker2->moveToThread(thread2);

    //connections to manipulate workers from main thread
    connect (this, &MainWindow::StartHashing1, worker1, &Worker::HashWorker);
    connect (worker1, &Worker::SendItem, this, &MainWindow::GetData);
    connect (this, &MainWindow::StartHashing2, worker2, &Worker::HashWorker);
    connect (worker2, &Worker::SendItem, this, &MainWindow::GetData);
    connect (worker1, &Worker::FinishedWork, this, &MainWindow::WorkerFinished);
    connect (worker2, &Worker::FinishedWork, this, &MainWindow::WorkerFinished);

    //setup other stuff for better visual performance
    spinner = new WaitingSpinnerWidget(ui->ForSpinner);
    ui->ForSpinner->setStyleSheet("background color: transparent;");
    ui->HelpfulFrame1->setFrameShape(QFrame::NoFrame);
    ui->HelpfulFrame2->setFrameShape(QFrame::NoFrame);
    spinner->setInnerRadius(5);
    spinner->setLineLength(5);

    ui->StopButton->setIcon(QIcon(":/icons/Stop.png"));
    ui->CheckButton->setIcon(QIcon(":/icons/Start.png"));

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
    /*double click on two dots to view the upper directory,
    on one dot to view the root and on any directory to view what it contains*/
    ui->UpperList =(QListView*) sender();
    QFileInfo fileinfo =  model->fileInfo(index);
    if (fileinfo.fileName() == "..")
        {
            QDir dir = fileinfo.dir();
            dir.cd("..");
            ui->UpperList->setRootIndex(index);
        }
    else if (fileinfo.fileName()== ".")
        {
            ui->UpperList->setRootIndex(model->index(""));
        }
    else if (fileinfo.isDir())
        {
            ui->UpperList->setRootIndex(index);
        }
    ui->UpperLine->setText(model->filePath(ui->UpperList->rootIndex()));
}

void MainWindow::on_LowerList_doubleClicked(const QModelIndex &index)
{
    //same for the lower list
    ui->LowerList =(QListView*) sender();
    QFileInfo fileinfo =  model->fileInfo(index);
    if (fileinfo.fileName() == "..")
        {
            QDir dir = fileinfo.dir();
            dir.cd("..");
            ui->LowerList->setRootIndex(index);
        }
    else if (fileinfo.fileName()== ".")
        {
            ui->LowerList->setRootIndex(model->index(""));
        }
    else if (fileinfo.isDir())
        {
            ui->LowerList->setRootIndex(index);
        }
    ui->LowerLine->setText(model->filePath(ui->LowerList->rootIndex()));
}

void MainWindow::on_CheckButton_clicked()
{
    QString FirstDir = model->filePath(ui->UpperList->rootIndex());
    QString SecondDir = model->filePath(ui->LowerList->rootIndex());
    if (IsDirNotDifferent(FirstDir,SecondDir))
    {
    HashTable.clear();
    ui->ResultList->clear();
    spinner->start();
    ui->SortButton->setEnabled(false);
    ui->CheckButton->setEnabled(false);
    ui->StopButton->setEnabled(true);
    ui->HelperLabel->setText("Double click on file to open its directory in explorer");
    }
}

bool MainWindow::IsDirNotDifferent(const QString &str1, const QString &str2)
{
    /*check if selected folders are the same or if one include anothother. Then start the threads.
     due to this check we can exlude one folder so the threads won't scan it twice */
    if (str1 == str2)
    {
        ui->HelperLabel->setText("What's the point to select identical directories?");
        return false;
    }
    else if(str1.indexOf(str2) == 0 && str2.count("/") != str1.count("/"))
    {
        thread1->start();
        thread2->start();
        emit StartHashing1(str1,NULL,InsidersAllowedFlag1);
        emit StartHashing2(str2,str1,InsidersAllowedFlag2);
    }
    else if(str2.indexOf(str1) == 0 && str2.count("/") != str1.count("/"))
    {
        thread1->start();
        thread2->start();
        emit StartHashing1(str1,str2,InsidersAllowedFlag1);
        emit StartHashing2(str2,NULL,InsidersAllowedFlag2);
    }
    else
    {
        thread1->start();
        thread2->start();
        emit StartHashing1(str1,NULL,InsidersAllowedFlag1);
        emit StartHashing2(str2, NULL,InsidersAllowedFlag2);
    }
    return true;
}

void MainWindow::on_RefreshButton_clicked()
{
    ui->UpperList->reset();
    ui->LowerList->reset();
    ui->ResultList->reset();
    ui->LowerLine->setText(NULL);
    ui->UpperLine->setText(NULL);
}

void MainWindow::on_ResultList_itemDoubleClicked(QListWidgetItem *item)
{
    QFileInfo FIleInfo(item->text());
    QDesktopServices::openUrl(QUrl("file:///" + FIleInfo.path()));
}

void MainWindow::GetData(const QString &itemPath, const QString &name)
{
    /*Get data from one of the workers. Create item from it and add it to the Result list*/

    QListWidgetItem *item = new QListWidgetItem(ui->ResultList);
    item->setText("(" + name + ") " + "Path:" + itemPath );
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
    /*helps to find out both workers finished their tasks*/

    ++ThreadCounter;
    if (ThreadCounter == NumberOfThreads)
    {
        spinner->stop();
        ui->SortButton->setEnabled(true);
        ui->CheckButton->setEnabled(true);
        ui->StopButton->setEnabled(false);
        ThreadCounter=0;
        if (ui->ResultList->count()==0)
            ui->HelperLabel->setText("Looks like no duplicates there");
    }
}

void MainWindow::on_StopButton_clicked()
{
    /*quit the threads right way but takes long...*/
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
void MainWindow::on_UpperInsideDirs_toggled(bool checked)
{
    InsidersAllowedFlag1=checked;
}

void MainWindow::on_LowerInsideDirs_toggled(bool checked)
{
    InsidersAllowedFlag2=checked;
}


void MainWindow::on_UpperLine_textChanged(const QString &arg1)
{
    if (model->index(arg1).isValid())
        ui->UpperList->setRootIndex(model->index(arg1));
}

void MainWindow::on_LowerLine_textChanged(const QString &arg1)
{
    if (model->index(arg1).isValid())
        ui->LowerList->setRootIndex(model->index(arg1));
}

