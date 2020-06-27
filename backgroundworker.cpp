#include "backgroundworker.h"

void Worker::setMap(MyMap &MainMap)
{
    Hash=&MainMap;
}

void Worker::HashWorker(const QString& DirName)
{
    GetFilesInHash(DirName);
    emit FinishedWork();
}

void Worker::GetFilesInHash(const QString& DirName)
{
        QDir dir = QDir(DirName);
        foreach (QFileInfo info, dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot, QDir::DirsFirst)) //looking for every file (which match filters) in the directory
        {
            if (info.isDir() && dir.cd(info.fileName()))                                                          //if 'info' is a directory then call this function again for this folder
            {
                GetFilesInHash(dir.absolutePath());
                dir.cdUp();
            }
            else
            {
                if (ItemSender(info,*Hash))
                Hash->insertMulti(QPair<QString,int>(info.fileName(),info.size()),QPair<QString,bool>(info.absoluteFilePath(),false));
            }
        }
}


bool Worker::ItemSender(const QFileInfo & info, MyMap &Hash)
{
    MyMap::iterator it = Hash.find(QPair<QString,int>(info.fileName(),info.size()));
    while((it!=Hash.end()) && (it.key() == QPair<QString,int>(info.fileName(),info.size())))
    {
          if(HashSumCheck(it.value().first,info.absoluteFilePath()))
          {
              emit SendItem(info.absoluteFilePath(), info.fileName());
              if(it.value().second == false)
              {
                  emit SendItem(it.value().first, it.key().first);
                  it.value().first=true;
              }
              return false;
          }
          ++it;
    }
    return true;
}

bool Worker::HashSumCheck (const QString& filename1, const QString& filename2)   //Method checks hash-sums for two files
{
    QCryptographicHash Md5Hash(QCryptographicHash::Md5);                         //if md5 sum is exact the same for both files then they are duplicates with an almost 100% probability
    QByteArray check;
    QFile FirstFile(filename1);
    if (FirstFile.open(QFile::ReadOnly))                                         //if the algorithm can't open one of the files then return 'false'
    {
        QFile SecondFile(filename2);
        if (SecondFile.open(QFile::ReadOnly))
        {
            Md5Hash.reset();
            if (Md5Hash.addData(&FirstFile))
            {
                check=Md5Hash.result();
                Md5Hash.reset();
                if (Md5Hash.addData(&SecondFile))
                {
                   if (Md5Hash.result() == check)
                       return true;
                   else
                       return false;
                }
            }
        }

    }
   return false;
}
void Mydelay()                                                                     //helpful delay
{
    QTime dieTime= QTime::currentTime().addSecs(2);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
