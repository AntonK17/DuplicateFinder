#ifndef INCLUDES_H
#define INCLUDES_H

#include <QHash>
#include <QPair>
#include <QCryptographicHash>
#include <QDir>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QTreeWidget>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFileIconProvider>
#include <QLabel>
#include <QThread>
#include <QMutexLocker>
#include <QMutex>
#include <QTime>
#include <QEventLoop>
#include <QCoreApplication>
#include <QtGui>
#include <QFile>

/*The key will generate from pair of file's name and size
 QString from value is for absolute path and bool is for flag
which will be used as indicator that information about this file has already sent*/
typedef QHash<QPair<QString,int>,QPair<QString,bool>> MyMap;

void Mydelay();

#endif // INCLUDES_H
