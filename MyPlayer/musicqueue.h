#ifndef MUSICQUEUE_H
#define MUSICQUEUE_H
#include"musicfile.h"
#include <iostream>

class musicQueue
{

public:
    musicQueue();
};

class musicQueueSpecial{
    int end;
    int capacity;
    musicFile * queue;
public:
    musicQueueSpecial(int c = 100);
    ~musicQueueSpecial();
    void enqueue(const char * FileLoc);
    void dequeue();
    void push(const char * FileLoc);
    musicFile  pop();
    musicFile  peek();
    void jumpTill(int index, musicQueueSpecial * previous,musicFile* curFile);
    void jumpBack(int index, musicQueueSpecial * previous,musicFile* curFile);
    void playNext(musicQueueSpecial * previous, musicFile * curFile);
    void playPrev(musicQueueSpecial * previous, musicFile* curFile);
    void display();
    int count();
    musicFile get_mFile(int index);
};

#endif // MUSICQUEUE_H
