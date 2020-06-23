#include "HashTable.h"
#include "mainwindow.h"
#include <QDebug>

HashTable::HashTable()
{
    htable = new list<pair<int,QString>>[SIZE];

};
HashTable::~HashTable()
{
    delete[] htable;
};

int HashTable::HashFunc(const int& key)
{
    return key % SIZE;
}


void HashTable::AddRecord(const int& key,const QString& Data)
{
    int hash_val=HashFunc(key);
    pair<int,QString> p(key,Data);
    htable[hash_val].push_front(p);
    if (htable[hash_val].size()==2)
    {
        CollisionKeys.push_back(hash_val);
        cout<<"Есть коллизия"<<endl;
    }
};
void HashTable::PrintElement (const int& key)
    {
        for(auto it = htable[HashFunc(key)].begin(); it != htable[HashFunc(key)].end(); ++it)
        {
            qDebug()<<"Строка: "<<(*it).second<<","<< "Размер: "<<(*it).first;
        }
        cout<<endl;
    };

void GetFilesInHash (QDir &dir,HashTable & hash)
{
    foreach (QFileInfo info, dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot, QDir::DirsFirst))
    {
        if (info.isDir() && dir.cd(info.fileName()))
        {
            GetFilesInHash (dir, hash);
            dir.cdUp();
        }
        else
        {
            hash.AddRecord(info.size(),info.fileName());
        }
    }
};
