#ifndef WORKEROBJECT_H
#define WORKEROBJECT_H

#include "includes.h"

class Worker : public QObject
 {
     Q_OBJECT

 public slots:
     void CallAll(const QString&, const QString&);
 signals:
     void SendData();
 public:
     MyMap Hash;
 private:
     void GetFilesInHash (const QString&);                                   //adds pair of filename and size as a key and absolute path as a value in Hash table from the file system
     bool IsNotAlreadyExist(const QFileInfo&, MyMap&);                       //check if file not already in Hash-table
     bool HashSumCheck (const QString& filename1, const QString& filename2); //compare two files with help of md5 Hash-sum
     void Compare(MyMap& FinalHash);                                         //method for bucket members comparison (from 'Hash'). It'll generate 'FinalHash' which will be sent to main process
 };

#endif // WORKEROBJECT_H
