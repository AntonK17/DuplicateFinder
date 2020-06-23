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
    while((it!=Hash.end()) && (it.key() == QPair<QString,int>(info.fileName(),info.size())))                  //Looking for all files in hash with same key
        {
          if((info.absoluteFilePath() == it.value()))                                                         //If exact same file already in 'Hash' return 'false' which mean it won't be included in 'Hash' twice
          {return false;}
          ++it;
        }
    return true;                                                                                              //return 'true' in other cases
}

bool HashSumCheck (const QString& filename1, const QString& filename2)                                        //Method checks hash-sums for two files
{
    QCryptographicHash Md5Hash(QCryptographicHash::Md5);                                                      //If md5 sums is exact the same for both then files are duplicats with almost 100% probability
    QByteArray check;
    QFile FirstFile(filename1);
    if (FirstFile.open(QFile::ReadOnly))                                                                      //If algorithm cant open one of files then return 'false'
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
