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
#include <QTime>
#include <QDebug>
#include <QEventLoop>
#include <QCoreApplication>

typedef QHash<QPair<QString,int>,QPair<QString,bool>> MyMap;

void Mydelay();

#endif // INCLUDES_H
