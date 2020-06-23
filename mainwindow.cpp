#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Functions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);                                 // allocate the memory for QFileSystemModel object model
    model->setFilter(QDir::QDir::AllEntries);                           // set filter AllEntries to see all files in current directory
    model->setRootPath("");                                             // this method helps to observe all the changes in current directory permamently
    ui->DirChooseRight->setModel(model);
    ui->DirChooseLeft->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_DirChooseLeft_doubleClicked(const QModelIndex &index)
{
    QListView* listView = (QListView*)sender();
    QFileInfo fileinfo =  model->fileInfo(index);
    if (fileinfo.fileName() == "..")
        {
            QDir dir = fileinfo.dir();
            dir.cd("..");
            listView->setRootIndex(model->index(dir.absolutePath()));
        }
    else if (fileinfo.fileName()== ".")
        {
            listView->setRootIndex(model->index(""));
        }
    else if (fileinfo.isDir())
        {
            listView->setRootIndex(index);
        }
}

void MainWindow::on_DirChooseRight_doubleClicked(const QModelIndex &index)
{
    MainWindow::on_DirChooseLeft_doubleClicked(index);
}

void MainWindow::on_Check_btn_clicked()
{
    ui->ResultList->clear();
    QDir FirstDir = QDir (model->filePath(ui->DirChooseLeft->rootIndex()));
    QDir SecondDir = QDir (model->filePath(ui->DirChooseRight->rootIndex()));

    MyMap FilesMap;                                                                 //Creating 'QHash' object with collisions allowed
    QHash<QString,QString> FinalList;
    GetFilesInHash (FirstDir,FilesMap);
    GetFilesInHash (SecondDir,FilesMap);
    Compare(FilesMap, FinalList);
    output(FinalList);
}

void MainWindow::output (const QHash<QString,QString>& FinalList)
{
    for (auto it=FinalList.begin(); it!=FinalList.end();++it)
    ui->ResultList->addItem(*it);
}


