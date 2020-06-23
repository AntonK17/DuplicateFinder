#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Functions.h"

void GetFilesInHash (QDir &dir,MyMap & Hash)
{
    foreach (QFileInfo info, dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot, QDir::DirsFirst)) //Look at every file (which match filters) in the directory
    {
        if (info.isDir() && dir.cd(info.fileName()))                                                          //If 'info' is directory then call this function again for this directory
        {
            GetFilesInHash (dir, Hash);
            dir.cdUp();
        }
        else
        {
            if (IsNotAlreadyExist(info,Hash))                                                                 //If 'info' is a regular file then check if it is not already in 'Hash'
            Hash.insertMulti(QPair<QString,int>(info.fileName(),info.size()), info.absoluteFilePath());       //Insert file in 'Hash'
        }
    }
}

bool IsNotAlreadyExist(const QFileInfo& info,MyMap& Hash)
{
    MyMap::iterator it = Hash.find(QPair<QString,int>(info.fileName(),info.size()));
    while((it!=Hash.end()) && (it.key() == QPair<QString,int>(info.fileName(),info.size())))                  //Looking for all files in hash wit same key
        {
          if((info.absoluteFilePath() == it.value()))                                                         //If exact same file already in 'Hash' return 'false' which mean it won't be included in 'Hash' twice
          {return false;}
          ++it;
        }
    return true;                                                                                              //return 'true' in other cases
}

void Compare(MyMap & Hash, QHash<QString,QString> & FinalList)
{
    MyMap::iterator it;
    for( it=Hash.begin(); it != Hash.end(); ++it)                                                             //Global 'for' for searching through all 'Hash'
    {
       if (Hash.count(it.key())>1 && (*it!="nothing"))                                                        //If this member in the collision bucket and is not flagged yet then algorithm have to compare elements from this bucket with each other
       {
           MyMap::iterator ii = Hash.find(it.key());                                                          //iterator for bucket scan. This iterator will be compared with all next in the same bucket
           while((ii!=(Hash.end()-1)) && ((ii).key() == it.key()))
           {
            MyMap::iterator inner=ii+1;                                                                       //iterator for all next members
                while ((inner!=Hash.end()) && (inner.key() == it.key()))
                {
                    if(HashSumCheck(ii.value(),inner.value()))                                                //If Hash-sum is exact the same for both files...
                    {                                                                                         //...Check if these two elements is not already in 'FinalList'. If they or one of them is then insert them
                        if (IsNotInFinalList(ii.key().first,ii.value(),FinalList))
                    FinalList.insertMulti(ii.key().first,ii.value());
                        if (IsNotInFinalList(inner.key().first,inner.value(),FinalList))
                    FinalList.insertMulti(inner.key().first,inner.value());
                    }
                    ++inner;
                }

            *ii="nothing";                                                                                     //flag elements cause there is no point to work with them multiple times
           ++ii;
           }
       }
    }
}

bool IsNotInFinalList(const QString& StringKey,const QString& value, QHash<QString,QString> &FinalList)         //it works similar to 'IsNotAlreadyExis'
{
    QHash<QString,QString>::iterator it = FinalList.find(StringKey);
    while((it!=FinalList.end()) && (it.key() == FinalList.find(StringKey).key()))
    {
        if (it.value() == value)
        {return false;}
        ++it;
    }
    return true;
}


bool HashSumCheck (const QString& filename1, const QString& filename2)                                          //Method checks hash-sums for two files
{
    QCryptographicHash Md5Hash(QCryptographicHash::Md5);                                                        //If md5 sums is exact the same for both then files are duplicats with almost 100% probability
    QByteArray check;
    QFile FirstFile(filename1);
    if (FirstFile.open(QFile::ReadOnly))                                                                        //If algorithm cant open one of files then return 'false'
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
