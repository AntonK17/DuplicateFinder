#include "backgroundworker.h"

void Worker::HashWorker(const QString &DirName, const QString &ExludeDirName, const bool &InsidersAllowed)
{
    AllowInsiders=InsidersAllowed;
    GetFilesInHash(DirName,ExludeDirName);
    emit FinishedWork();
}

/*looking for every file (which match filters) in the directory
 if 'info' is a directory then call this function again for it (Won't work if searching inner directories is prohibited)
 if 'info' is a file then call ItemSender to find out what to do with it*/
void Worker::GetFilesInHash(const QString &DirName, const QString &exlude)
{
    if(AbortionW) return;
        QDir dir = QDir(DirName);
        foreach (QFileInfo info, dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot, QDir::DirsLast))
        {
            if (AbortionW) return;
            if (info.absoluteFilePath()==exlude){}
            else
            {

                if (!info.isDir())
                {
                ItemSender(info,*Hash);
                }
                else if (info.isDir() && dir.cd(info.fileName()) && AllowInsiders)
                {
                GetFilesInHash(dir.absolutePath(),exlude);
                dir.cdUp();
                }
            }
        }
}

/* if method won't find any records with the same key as 'info'(name and size pair) create new record
 * if it will then compare all the files records point to with 'info' file. 'HashSumCheck' function will help
 * if the files match then send them to the main thread and flag(it.value().second) that file's information from the record has already been sent*/
void Worker::ItemSender(const QFileInfo &info, MyMap &Hash)
{
    QMutex mutex;
    QMutexLocker locker(&mutex);

    MyMap::iterator it = Hash.find(QPair<QString,int>(info.fileName(),info.size()));
    while((it!=Hash.end()) && (it.key() == QPair<QString,int>(info.fileName(),info.size())))
    {
          if(HashSumCheck(it.value().first,info.absoluteFilePath()))
          {
              emit SendItem(info.absoluteFilePath(), info.fileName());
              if(it.value().second == false)
              {
                  emit SendItem(it.value().first, it.key().first);
                  it.value().second=true;
              }
              return;
          }
          ++it;
    }
    Hash.insertMulti(QPair<QString,int>(info.fileName(),info.size()),QPair<QString,bool>(info.absoluteFilePath(),false));
    return;
}

/*Method checks hash-sums for two files
 * if md5 sum is exact the same for both files then they are duplicates with an almost 100% probability*/
bool Worker::HashSumCheck (const QString &filename1, const QString &filename2)
{
    QCryptographicHash Md5Hash(QCryptographicHash::Md5);
    QByteArray check;
    QFile FirstFile(filename1);
    if (FirstFile.open(QFile::ReadOnly))
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
                   {
                       return true;
                   }
                   else
                   {
                       return false;
                   }}}}}
   return false;
}

void Mydelay()
{
    //helpful delay
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Worker::Abort()
{
    AbortionW = 1;
}
