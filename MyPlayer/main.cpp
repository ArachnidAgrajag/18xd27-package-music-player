#include "playerdialog.h"
#include "musicfile.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerDialog w;
    w.show();
    musicFile mFile("/home/saikrishna/Downloads/random stuff/Chumma Kizhi-Masstamilan.in.mp3");
    w.load_music(&mFile);
    return a.exec();
}
