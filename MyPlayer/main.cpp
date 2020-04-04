#include "playerdialog.h"
#include "musicfile.h"
#include <QApplication>
#include "musicqueue.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerDialog w;
    musicQueueSpecial allSongs;
    allSongs.enqueue("/home/saikrishna/Downloads/random stuff/Chumma Kizhi-Masstamilan.in.mp3");
    allSongs.enqueue("/home/saikrishna/Downloads/random stuff/VIP_(Title_Song)-StarMusiQ.Com.mp3");
    allSongs.enqueue("/home/saikrishna/Downloads/random stuff/Yaanji-MassTamilan.com.mp3");
    allSongs.enqueue("/home/saikrishna/Downloads/random stuff/Aalaporan_Thamizhan-5StarMusiQ.Com.mp3");
    allSongs.enqueue("/home/saikrishna/Downloads/random stuff/Adiye-Sakkarakatti-MassTamilan.com.mp3");
    allSongs.enqueue("/home/saikrishna/Downloads/random stuff/Azhaipaiya_Azhaipaya-VmusiQ.Com.mp3");
    w.show();
    w.load_allSongs(allSongs);
    return a.exec();
}
