#include "musicqueue.h"

musicQueueSpecial::musicQueueSpecial(int c){
    capacity=c;
    end = 0;
    queue = new musicFile [capacity];
}

musicQueueSpecial::~musicQueueSpecial(){
    delete [] queue;
}

musicQueueSpecial::musicQueueSpecial(const musicQueueSpecial &mQueue)
{
    this->end=mQueue.end;
    this->capacity=mQueue.capacity;
    queue = new musicFile [capacity];
    for(int i=0;i<end;i++){
        this->queue[i]=mQueue.queue[i];
    }

}

musicQueueSpecial &musicQueueSpecial::operator =(const musicQueueSpecial mQueue)
{
    if(this!=&mQueue){
        this->end=mQueue.end;
        this->capacity=mQueue.capacity;
        for(int i=0;i<=end;i++){
            this->queue[i]=mQueue.queue[i];
        }
    }

    return *this;
}

void musicQueueSpecial::enqueue(const char *FileLoc){
    if(capacity!=end){
        queue[end].set_fileLoc(FileLoc);
        end++;
    }
}

void musicQueueSpecial::dequeue() {
    if (end != 0) {
        for (int i = 0; i < end ; i++) {
            queue[i] = queue[i + 1];
        }
        end--;
    }
}

void musicQueueSpecial::push(const char * FileLoc){
    if(capacity!=end){
        for(int i = end; i>=0; i-- ){
            queue[i+1]=queue[i];
        }
        queue[0].set_fileLoc(FileLoc);
        end++;
    }
}

musicFile musicQueueSpecial::pop(){
    musicFile temp = queue[0];
    dequeue();
    return temp;
}

musicFile musicQueueSpecial::peek(){
    return queue[0];
}

void musicQueueSpecial::jumpTill(int index, musicQueueSpecial *previous, musicFile* curFile){
    if(end!=0){
        push(curFile->get_fileLoc());
        for(int i=0; i<=index; i++){
            previous->push(pop().get_fileLoc());
        }
        *curFile=queue[0];
        dequeue();
    }
}

void musicQueueSpecial::jumpBack(int index, musicQueueSpecial *previous, musicFile* curFile)
{
    push(curFile->get_fileLoc());
    for(int i=0; i<=index; i++){
        push(previous->pop().get_fileLoc());
    }
    *curFile=queue[0];
    dequeue();
}

void musicQueueSpecial::playNext(musicQueueSpecial * previous,musicFile * curFile){
    previous->push(curFile->get_fileLoc());
    *curFile = queue[0];
    dequeue();
}

void musicQueueSpecial::playPrev(musicQueueSpecial *previous, musicFile* curFile){
    push(curFile->get_fileLoc());
    *curFile=previous->pop();
}

void musicQueueSpecial::display(){
    for(int i=0;i<=end;i++){
        std::cout<<queue[i].get_title().toStdString()<< "  ";
    }
    std::cout<<std::endl<<std::endl;
}

int musicQueueSpecial::count()
{
    return end;
}

musicFile musicQueueSpecial::get_mFile(int index)
{
    return queue[index];
}

void musicQueueSpecial::reset(musicQueueSpecial *previous, musicFile *curFile)
{
    jumpBack(previous->count()-1,previous,curFile);
}

void musicQueueSpecial::shuffle(musicQueueSpecial *previous, musicFile *curFile)
{
    reset(previous,curFile);
    push(curFile->get_fileLoc());
    musicFile temp;
    int randomIndex = 0;
    for(int i=0;i<end;i++){
        randomIndex=rand()%(end);
        temp = queue[i];
        queue[i]=queue[randomIndex];
        queue[randomIndex]=temp;
    }
    *curFile=pop();
}
