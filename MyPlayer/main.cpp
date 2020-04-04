#include "playerdialog.h"
#include "musicfile.h"
#include <QApplication>
#include "musicqueue.h"
#include<cstring>

#include <sys/types.h>
#include <sys/stat.h>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
struct stat info;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlayerDialog w;
    std::string direc;
    musicQueueSpecial allSongs;
    bool dirExists = false;

    while(!dirExists){
        w.show();
        direc=w.getDirectory().toStdString();
        if(direc.length()!=0){
            if( stat( direc.c_str(), &info ) != 0 ){
                if(errno==ENOENT)
                    w.showMessage(QString::fromStdString("ERROR:The specified directory does not exists or cannot Access "+direc),true);
                if(errno==ENOTDIR)
                    w.showMessage(QString::fromStdString("ERROR: "+direc+" is not a directory"),true);
            }
            else
                dirExists=true;
        }
        else
            dirExists=true;
    }


    if(direc.length()!=0){
        for (const auto & entry : fs::recursive_directory_iterator(direc)){
            if(entry.path().extension()==".mp3"){
                allSongs.enqueue(entry.path().c_str());
            }
        }
        w.load_allSongs(allSongs);
    }

    else {
        w.close();
    }

    return a.exec();
}
