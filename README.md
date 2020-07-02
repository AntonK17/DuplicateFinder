# DuplicateFinder

DuplicateFinder is a simple application allows you to find copies of files on your computer. You can scan two folders (with inside directories or without them) to find out if there are duplicates in them.
After main algorithm finishes it work you can scroll the list and open each duplicate in the explorer if you want to. Look doc file for more information.

# 02.07 update:
-Now HashTable calls 'clear' method in the right place
-added counter for duplicates
-since i see no point in adding items at the widget as soon as possible (cause user cannot interract with them anyway, they are coming too fast) i decided to use QList with filepaths in it for final results
-replaced QListWidget with QTreeWidget cause this widget have convienient columns.
-Abortion doidnt work. I tried different methods to stop a recursive function from main thread. two or three times (it was like a strange random) signal was emitted from the main thread and flag was changed. Now abortion is working. I dont feel like this is the right method but im sure i have to dig deeper at signal/slots between threads and event loops themes 
# WhatToDo:
-Columns not conveniant enough. I guess QTreeView will be better cause i didnt find any signals for clicking on headers events.
