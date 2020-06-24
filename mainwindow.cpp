#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Functions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);                                  //allocate the memory for QFileSystemModel object model
    model->setFilter(QDir::QDir::AllEntries);                            //set filter 'AllEntries' to see all files in current directory
    model->setRootPath("");                                              //this method helps to observe all the changes in current directory permamently
    ui->DirChooseRight->setModel(model);                                 //set both view lists
    ui->DirChooseLeft->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_DirChooseLeft_doubleClicked(const QModelIndex &index) //this method makes possible to navigate the file system
{
    QListView* listView = (QListView*)sender();
    QFileInfo fileinfo =  model->fileInfo(index);
    if (fileinfo.fileName() == "..")                                      //double click on two dots to view the upper directory...
        {
            QDir dir = fileinfo.dir();
            dir.cd("..");
            listView->setRootIndex(model->index(dir.absolutePath()));
        }
    else if (fileinfo.fileName()== ".")                                   //...one dot to view the root...
        {
            listView->setRootIndex(model->index(""));
        }
    else if (fileinfo.isDir())                                            //...and any directory to view what it contains...
        {
            listView->setRootIndex(index);
        }
}

void MainWindow::on_DirChooseRight_doubleClicked(const QModelIndex &index)//...same for the second list view
{
    MainWindow::on_DirChooseLeft_doubleClicked(index);
}

void MainWindow::on_Check_btn_clicked()
{
    ui->ResultList->clear();
    QDir FirstDir = QDir (model->filePath(ui->DirChooseLeft->rootIndex()));      //get directories from the list views
    QDir SecondDir = QDir (model->filePath(ui->DirChooseRight->rootIndex()));

    MyMap FilesMap;                                                              //creating 'QHash' object with collisions allowed
    GetFilesInHash (FirstDir,FilesMap);
    GetFilesInHash (SecondDir,FilesMap);
    Compare(FilesMap);
    ui->ResultLabel->setText("Results (Double click to open file directory)");
}

void MainWindow::Compare(MyMap & Hash)
{
    bool flag = 0;
    QString Sflag="\0";
    MyMap::iterator it;
    for( it=Hash.begin(); it != Hash.end(); ++it)                           //global 'for' for searching through all 'Hash'
    {
       if (Hash.count(it.key())>1 && (*it!=Sflag))                          //if this member in the collision bucket and not flagged yet then algorithm have to compare elements with each other from this bucket
       {
           MyMap::iterator ii = Hash.find(it.key());                        //iterator for bucket scan. This iterator's content will be compared with all next in the same bucket
           while((ii!=(Hash.end()-1)) && ((ii).key() == it.key()))
           {
              if (ii.value() == Sflag)                                      //skip marked elements
              {
                ++ii;
              }
              else
              {
                 MyMap::iterator inner=ii+1;                                //iterator for all next members...
                 while ((inner!=Hash.end()) && (inner.key() == it.key()))
                 {
                      if (inner.value()==Sflag)                             //...except marked ones
                      {
                          ++inner;
                      }
                      else
                      {
                         if(HashSumCheck(ii.value(),inner.value()))         //if Hash-sum is exact the same for both files then add absolute path to this file at result list...
                         {
                            flag=1;                                         //... and mark (with help of flag) that 'ii' iterator contain duplicate's file name. Also mark 'inner' cause it's already in output
                            output(inner.value());
                            inner.value()=Sflag;
                         }
                          ++inner;
                       }
                  }
               if(flag) {output(ii.value());}
               *ii=Sflag;                                                   //flag elements cause there is no point to work with them multiple times
               ++ii;
               flag=0;
              }
            }
        }
    }
}

void MainWindow::output(const QString &StringPath)                          //set the icon (from file info) and also absolute file name as text in the item...
{                                                                           //...the add this item to the 'ResultList' widget
    QListWidgetItem *item = new QListWidgetItem(ui->ResultList);
    item->setText(StringPath);
    QFileInfo finfo(StringPath);
    QFileIconProvider ip;
    QIcon ic=ip.icon(finfo);
    item->setIcon(ic);
    ui->ResultList->addItem(item);
}

void MainWindow::on_ResultList_itemDoubleClicked(QListWidgetItem *item)
{
    QFileInfo FIleInfo(item->text());
    QDesktopServices::openUrl(QUrl("file:///" + FIleInfo.path()));
}

