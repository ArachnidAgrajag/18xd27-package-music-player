#ifndef MUSICFILE_H
#define MUSICFILE_H
#include<taglib/fileref.h>
#include <taglib/tag.h>
#include<taglib/attachedpictureframe.h>
#include<taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include<QDialog>

class musicFile
{
private:
    QString title;
    QString album;
    QString artist;
    QImage coverArt;
    musicFile * next;

    QImage imageForTag(TagLib::ID3v2::Tag *tag);
public:
    musicFile(const char * fileLoc = "");
    ~musicFile();
    musicFile(const musicFile & mFile);
    musicFile& operator = (const musicFile &mFile);
    void readTags();
    void set_fileLoc(const char * fileLoc);
    char * get_fileLoc(){
        return fileLoc;
    }
    QString get_title(){
        return title;
    }
    QString get_album(){
        return album;
    }
    QString get_artist(){
        return artist;
    }
    QImage get_coverArt(){
        return coverArt;
    }
private:
    char * fileLoc;
 };

#endif // MUSICFILE_H
