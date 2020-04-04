#include "playerdialog.h"
#include "musicfile.h"
#include <QApplication>
#include "musicqueue.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerDialog w;
    musicQueueSpecial curQueue;
    curQueue.enqueue("/home/saikrishna/Downloads/random stuff/Chumma Kizhi-Masstamilan.in.mp3");
    curQueue.enqueue("/home/saikrishna/Downloads/random stuff/VIP_(Title_Song)-StarMusiQ.Com.mp3");
    curQueue.enqueue("/home/saikrishna/Downloads/random stuff/Yaanji-MassTamilan.com.mp3");
    w.show();
    w.load_playingQueue(&curQueue);
    return a.exec();
}
