#ifndef HASHTABLE_H
#define HASHTABLE_H

#endif // HASHTABLE_H
#include <list>
#include <vector>
#include <iostream>
#include <QString>
#include <QDir>

using namespace std;
const int SIZE = 128;

class HashTable
{
private:
    list<pair<int,QString>> * htable;
    vector<int> CollisionKeys;                                  //Храним hash ключи коллизий
public:
    HashTable();
    ~HashTable();
    int HashFunc(const int& key);
    void AddRecord(const int& key,const QString& Data);
    void PrintElement(const int& key);
};

void GetFilesInHash (QDir &dir,HashTable & hash);

