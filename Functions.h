#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QHash>
#include <QPair>
#include <QCryptographicHash>
#include <QDir>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QListWidget>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFileIconProvider>

typedef QHash<QPair<QString,int>,QString> MyMap;                                                         //'MyMap' will contain files with the same name and size (this pair is the 'key') in one bucket (buckets contain collsion members )...
                                                                                                         //...It'll help to find duplicates. The 'value' in MyMap is the absolute path to the file
void GetFilesInHash (QDir &dir,MyMap &Hash);                                                            //method will fill up MyMap object
bool IsNotAlreadyExist (const QFileInfo &info,MyMap &Hash);                                              //method will exlude adding same files (files from same directories)
bool HashSumCheck (const QString &filename1, const QString &filename2);                                  //compare two files with help of md5 Hash-sum

#endif // FUNCTIONS_H
