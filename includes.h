#ifndef INCLUDES_H
#define INCLUDES_H

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
#include <QLabel>
#include <QThread>

typedef QHash<QPair<QString,int>,QString> MyMap;                                                         //'MyMap' will contain files with the same name and size (this pair is the 'key') in one bucket (buckets contain collsion members )...
                                                                                                         //...It'll help to find duplicates. The 'value' in MyMap is the absolute path to the file



#endif // INCLUDES_H
