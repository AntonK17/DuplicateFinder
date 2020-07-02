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
    Worker *worker1=new Worker(HashTable, MainList);
    Worker *worker2=new Worker(HashTable, MainList);
    thread1=new QThread();
    thread2=new QThread();
    worker1->moveToThread(thread1);
    worker2->moveToThread(thread2);

    //context menu and other setups for result list
    ui->ResultList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->ResultList->setColumnCount(4);
    ui->ResultList->setColumnWidth(0,1);
    ui->ResultList->setColumnWidth(1,150);
    ui->ResultList->setColumnWidth(2,75);
    QList<QString> ListOfStrings;
    ListOfStrings.push_back("");
    ListOfStrings.push_back("File Name");
    ListOfStrings.push_back("Size");
    ListOfStrings.push_back("Path");
    QStringList list(ListOfStrings);
    ui->ResultList->setHeaderLabels(list);
    ui->ResultList->setRootIsDecorated(false);

    Ww=new WarningWindow(this);

    //connections between Main Window and Warning Window
    connect (Ww, &WarningWindow::YesNoClicked, this, &MainWindow::deleteFile);

    //connections for workers manipulation from main thread
    connect (this, &MainWindow::StartHashing1, worker1, &Worker::HashWorker);
    connect (this, &MainWindow::StartHashing2, worker2, &Worker::HashWorker);
    connect (worker1, &Worker::FinishedWork, this, &MainWindow::WorkerFinished);
    connect (worker2, &Worker::FinishedWork, this, &MainWindow::WorkerFinished);
    connect (this, &MainWindow::CountDuplicatesSe, this, &MainWindow::CountDuplicatesRe);

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

    connect(this, &MainWindow::AbortionStart, worker1 ,&Worker::Abort);
    connect(this, &MainWindow::AbortionStart, worker2 ,&Worker::Abort);

    thread1->start();
    thread2->start();
}

MainWindow::~MainWindow()
{
    thread1->quit();
    thread2->quit();
    thread1->wait();
    thread2->wait();
    delete ui;
}

/*double click on two dots to view the upper directory,
on one dot to view the root and on any directory to view what it contains*/
void MainWindow::on_UpperList_doubleClicked(const QModelIndex &index)
{
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

//same for the lower list
void MainWindow::on_LowerList_doubleClicked(const QModelIndex &index)
{
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
    ui->ResultList->clear();
    spinner->start();
    ui->SortButton->setEnabled(false);
    ui->CheckButton->setEnabled(false);
    ui->StopButton->setEnabled(true);
    ui->HelperLabel->setText("Searching...");
    counting=1;
    emit CountDuplicatesSe();
    }
}

/*check if selected folders are the same or if one include anothother. Then start the threads.
 due to this check we can exlude one folder so the threads won't scan it twice */
bool MainWindow::IsDirNotDifferent(const QString &str1, const QString &str2)
{
    if (str1 == str2)
    {
        ui->HelperLabel->setText("What's the point to select identical directories?");
        return false;
    }
    else if(str1.indexOf(str2) == 0 && str2.count("/") != str1.count("/"))
    {
        emit StartHashing1(str1,NULL,InsidersAllowedFlag1);
        emit StartHashing2(str2,str1,InsidersAllowedFlag2);
    }
    else if(str2.indexOf(str1) == 0 && str2.count("/") != str1.count("/"))
    {
        emit StartHashing1(str1,str2,InsidersAllowedFlag1);
        emit StartHashing2(str2,NULL,InsidersAllowedFlag2);
    }
    else
    {
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

/*Get data from one of the workers. Create item from it and add it to the Result list*/
void MainWindow::GetData()
{
    for(auto it=MainList.begin();it!=MainList.end();++it)
    {
        QFileInfo finfo(*it);
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(1,finfo.fileName());
        item->setText(2,QString::number(finfo.size()));
        item->setText(3,finfo.absoluteFilePath());
        QFileIconProvider ip;
        QIcon ic=ip.icon(finfo);
        item->setIcon(0,ic);
        ui->ResultList->addTopLevelItem(item);
    }
}

void MainWindow::on_SortButton_clicked()
{
    ui->ResultList->sortItems(1,Qt::AscendingOrder);
}

/*helps to find out both workers finished their tasks*/
void MainWindow::WorkerFinished()
{
    ++ThreadCounter;
    if (ThreadCounter == NumberOfThreads)
    {
        GetData();
        spinner->stop();
        ui->SortButton->setEnabled(true);
        ui->CheckButton->setEnabled(true);
        ui->StopButton->setEnabled(false);
        ThreadCounter=0;
        counting=0;
        MainList.clear();
        HashTable.clear();
    }
}

/*quiting doesnt work for now...*/
void MainWindow::on_StopButton_clicked()
{
    ui->StopButton->setEnabled(false);
    ui->HelperLabel->setText("Exiting...Please wait...");
    emit AbortionStart();
}

void MainWindow::on_UpperInsideDirs_toggled(bool checked)
{
    InsidersAllowedFlag1=checked;
}

void MainWindow::on_LowerInsideDirs_toggled(bool checked)
{
    InsidersAllowedFlag2=checked;
}

/*Synchronize file system lists with line edits */
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

//Context menu for the result list
void MainWindow::on_ResultList_customContextMenuRequested(const QPoint &pos)
{
    if (ui->ResultList->itemAt(pos) != NULL)
    {
    QMenu menu;
    QAction Delete;
    Delete.setShortcut(QKeySequence::Delete);
    Delete.setText("REMOVE");
    Delete.setStatusTip("COMPLETELY remove file from your computer");
    Delete.setIcon(QIcon(":/icons/Stop.png"));
    connect (&Delete, &QAction::triggered, this, &MainWindow::DeleteEnabledChecker);
    menu.addAction(&Delete);
    menu.exec(ui->ResultList->viewport()->mapToGlobal(pos));
    }
}

/* delete file slot. It can be called from signal by Warning window or by
 * 'DeleteEnabledChecker' if DeleteEnabled flag is true
 * (which means user set checked 'Don't ask me again' on Warning window)*/
void MainWindow::deleteFile(const bool &DeleteEn, const bool& YesOrNo)
{
    if (DeleteEn)
        DeleteEnabled=true;

    if (YesOrNo)
    {
    QTreeWidgetItem* item = ui->ResultList->currentItem();
    QString path = item->text(3);
    QFile file (path);
    file.remove();
    ui->ResultList->takeTopLevelItem(ui->ResultList->indexOfTopLevelItem(
                                         ui->ResultList->currentItem()));
    }
}

// delete selected file
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete && ui->ResultList->currentItem() != NULL)
       DeleteEnabledChecker();
}

// check if user really want to delete chosen file
void MainWindow::DeleteEnabledChecker()
{
    if (DeleteEnabled)
        deleteFile(DeleteEnabled, true);
    else
    {
        Ww->exec();
    }
}

// duplicates counter
void MainWindow::CountDuplicatesRe()
{
    ui->HelperLabel->setText("Searching... Duplicates: " + QVariant(MainList.size()).toString());
      if (counting)
    QTimer::singleShot(2, this, &MainWindow::CountDuplicatesSe);
      else
      {
      if (ui->ResultList->topLevelItemCount()==0)
          ui->HelperLabel->setText("Looks like no duplicates there");
      else
          ui->HelperLabel->setText("Double click on file to open its directory in explorer");
      }
}

void MainWindow::on_ResultList_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QFileInfo FIleInfo(item->text(3));
    QDesktopServices::openUrl(QUrl("file:///" + FIleInfo.path()));
}
