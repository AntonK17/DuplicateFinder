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
void Compare (MyMap& Hash, QHash<QString,QString> & FinalList);                                          //Method for bucket members comparison
bool HashSumCheck (const QString& filename1, const QString& filename2);                                  //Compare two files with help of md5 Hash-sum
bool IsNotInFinalList (const QString& StringKey,const QString& value, QHash<QString,QString> &FinalList);//Exlude adding same files in Final QHash

#endif // FUNCTIONS_H
