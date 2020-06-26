#include <includes.h>
#include <WorkerObject.h>

void Worker::GetFilesInHash (const QString& str)
{
    QDir dir = QDir(str);
    foreach (QFileInfo info, dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot, QDir::DirsFirst)) //looking for every file (which match filters) in the directory
    {
        if (info.isDir() && dir.cd(info.fileName()))                                                          //if 'info' is a directory then call this function again for this folder
        {
            GetFilesInHash (dir.absolutePath());
            dir.cdUp();
        }
        else
        {
            if (IsNotAlreadyExist(info,Hash))                                                                 //if 'info' is a regular file then check if it is not already in 'Hash'
            Hash.insertMulti(QPair<QString,int>(info.fileName(),info.size()), info.absoluteFilePath());       //insert file in 'Hash'. Pair of name and size goes to the key argument and absolute path to the value
        }
    }
}

bool Worker::IsNotAlreadyExist(const QFileInfo& info,MyMap& Hash)
{
    MyMap::iterator it = Hash.find(QPair<QString,int>(info.fileName(),info.size()));
    while((it!=Hash.end()) && (it.key() == QPair<QString,int>(info.fileName(),info.size())))                  //looking for all files in hash with the same key
    {
          if((info.absoluteFilePath() == it.value()))                                                         //If the exact same file already in 'Hash' return 'false' which mean it won't be included in 'Hash' twice
          {return false;}
          ++it;
    }
    return true;                                                                                              //return 'true' in other cases
}

void Worker::Compare(MyMap &FinalHash)
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
                         if(HashSumCheck(ii.value(),inner.value()))         //if Hash-sum is exact the same for both files then add absolute path to this file at Hash-table with results...
                         {
                            flag=1;                                         //... and mark (with help of flag) that 'ii' iterator contain duplicate's file name. Also mark 'inner' cause it's already in output
                            FinalHash.insertMulti(ii.key(),ii.value());
                            inner.value()=Sflag;
                         }
                          ++inner;
                       }
                  }
               if(flag) {FinalHash.insertMulti(ii.key(),ii.value());}
               *ii=Sflag;                                                    //flag elements cause there is no point to work with them multiple times
               ++ii;
               flag=0;
              }
            }
        }
    }
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


void Worker::CallAll(const QString& FirstDir, const QString& SecondDir)        //These functions will run in other thread. After work is done main thread will recieve
{                                                                              //... Hash table with final list of duplicates
    GetFilesInHash (FirstDir);
    GetFilesInHash (SecondDir);
    MyMap FinalHash;
    Compare(FinalHash);
    Hash=FinalHash;
    emit SendData();

}
