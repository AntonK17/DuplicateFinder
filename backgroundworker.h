#ifndef BACKGROUNDWORKER_H
#define BACKGROUNDWORKER_H

#include <includes.h>

class Worker : public QObject
 {
     Q_OBJECT

 public slots:
     void HashWorker(const QString&);
 signals:
     void FinishedWork();
     void SendItem(const QString&, const QString&);
 public:
     void setMap(MyMap&);
 private:
     void GetFilesInHash(const QString& DirName);
     bool ItemSender(const QFileInfo&, MyMap&);
     bool HashSumCheck (const QString& filename1, const QString& filename2); //compare two files with help of md5 Hash-sum                                       //method for bucket members comparison (from 'Hash'). It'll generate 'FinalHash' which will be sent to main process
     MyMap* Hash;
 };


#endif // BACKGROUNDWORKER_H
