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

    MyMap FilesMap;                                                              //Creating 'QHash' object with collisions allowed
    GetFilesInHash (FirstDir,FilesMap);
    GetFilesInHash (SecondDir,FilesMap);
    Compare(FilesMap);
}

void MainWindow::output (const QString& value)
{
    ui->ResultList->addItem(value);
}

void MainWindow::Compare(MyMap & Hash)
{
    bool flag = 0;
    MyMap::iterator it;
    for( it=Hash.begin(); it != Hash.end(); ++it)                               //Global 'for' for searching through all 'Hash'
    {
       if (Hash.count(it.key())>1 && (*it!="nothing"))                          //If this member in the collision bucket and not flagged yet then algorithm have to compare elements with each other from this bucket
       {
           MyMap::iterator ii = Hash.find(it.key());                            //iterator for bucket scan. This iterator's content will be compared with all next in the same bucket
           while((ii!=(Hash.end()-1)) && ((ii).key() == it.key()))
           {
              if (ii.value() == "nothing")                                      //skip marked elements
              {
                ++ii;
              }
              else
              {
                 MyMap::iterator inner=ii+1;                                     //iterator for all next members...
                 while ((inner!=Hash.end()) && (inner.key() == it.key()))
                 {
                      if (inner.value()=="nothing")                              //...except marked ones
                      {
                          ++inner;
                      }
                      else
                      {
                         if(HashSumCheck(ii.value(),inner.value()))              //If Hash-sum is exact the same for both files then add absolute path to this file at result list...
                         {
                            flag=1;                                              //... and mark (with help of flag) that 'ii' iterator contain duplicate's file name. Also mark 'inner' cause it's already in output
                            output(inner.value());
                            inner.value()="nothing";
                         }
                          ++inner;
                       }
                  }
               if(flag) {output(ii.value());}
               *ii="nothing";                                                    //flag elements cause there is no point to work with them multiple times
               ++ii;
               flag=0;
              }
            }
        }
    }
}


