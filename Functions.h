#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QHash>
#include <QDebug>
#include <QPair>
#include <QCryptographicHash>
#include <QDir>

typedef QHash<QPair<QString,int>,QString> MyMap;                                                         //MyMap will contain files with same name and size in one bucket (buckets contains members with collsion)

void GetFilesInHash (QDir &dir,MyMap & Hash);                                                            //Method will help to fill up MyMap object
bool IsNotAlreadyExist (const QFileInfo& info,MyMap& Hash);                                              //Method will exlude adding same files (files from same directory)
bool HashSumCheck (const QString& filename1, const QString& filename2);                                  //Compare two files with help of md5 Hash-sum

#endif // FUNCTIONS_H
