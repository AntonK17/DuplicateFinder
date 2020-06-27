#ifndef BACKGROUNDWORKER_H
#define BACKGROUNDWORKER_H

#include <includes.h>

class Worker : public QObject
 {
     Q_OBJECT

 public slots:
     void HashWorker(const QString &DirName, const QString &ExludeDirName, const bool &InsidersAllowed);
 signals:
     void FinishedWork();
     void SendItem(const QString&, const QString&);
 public:
     bool AllowInsiders=0;
     Worker(MyMap& map) : Hash(&map){};
 private:
     void GetFilesInHash(const QString &DirName, const QString &ExludeDirName);
     void ItemSender(const QFileInfo&, MyMap&);
     bool HashSumCheck (const QString& filename1, const QString& filename2); //compare two files with help of md5 Hash-sum
     MyMap *Hash;
 };


#endif // BACKGROUNDWORKER_H
