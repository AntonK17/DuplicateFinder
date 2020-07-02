#ifndef BACKGROUNDWORKER_H
#define BACKGROUNDWORKER_H

#include <includes.h>

class Worker : public QObject
 {
     Q_OBJECT

 public slots:
     void HashWorker(const QString &DirName, const QString &ExludeDirName, const bool &InsidersAllowed);
     void Abort();
 signals:
     //signals for main thread. 'FinishedWork' will be emitted at the 'HashWorker' end
     //'SendItem' will send the name and absolute path of duplicate
     void FinishedWork();
 public:
     Worker(MyMap& map, QList<QString> &res) : Hash(&map), Results(&res){};
 private:   
     void  GetFilesInHash(const QString &DirName, const QString &ExludeDirName);
     void  ItemSender(const QFileInfo&, MyMap&);
     bool  HashSumCheck (const QString& filename1, const QString& filename2);
     MyMap *Hash;
     QList<QString> *Results;
     bool AbortionW;
     bool AllowInsiders=0;
 };


#endif // BACKGROUNDWORKER_H
