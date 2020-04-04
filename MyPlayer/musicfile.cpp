#include "musicfile.h"

musicFile::musicFile(const char * fileLoc){
    this->fileLoc = new char[strlen(fileLoc)];
    strcpy(this->fileLoc,fileLoc);
    if(strlen(this->fileLoc)!=0){
        readTags();
    }
}

void musicFile::set_fileLoc(const char *fileLoc){
    this->fileLoc = new char[strlen(fileLoc)];
    strcpy(this->fileLoc,fileLoc);
    if(strlen(this->fileLoc)!=0){
        readTags();
    }
}

musicFile::~musicFile(){
    delete fileLoc;
}
musicFile::musicFile(const musicFile & mFile){
    this->fileLoc = new char[strlen(mFile.fileLoc)];
    strcpy(fileLoc,mFile.fileLoc);
     title=mFile.title;
     album=mFile.album;
     artist=mFile.artist;
     coverArt=mFile.coverArt;
}

musicFile& musicFile::operator = (const musicFile &mFile){
    if(this != &mFile){
        this->fileLoc = new char[strlen(mFile.fileLoc)];
        strcpy(fileLoc,mFile.fileLoc);
        title=mFile.title;
        album=mFile.album;
        artist=mFile.artist;
        coverArt=mFile.coverArt;
    }
    return *this;
}

QImage musicFile::imageForTag(TagLib::ID3v2::Tag *tag)
{
    TagLib::ID3v2::FrameList l = tag->frameList("APIC");

    QImage image;

    if(l.isEmpty())
        return image;

    TagLib::ID3v2::AttachedPictureFrame *f = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(l.front());

    image.loadFromData((const uchar *) f->picture().data(), f->picture().size());

    return image;
}

void musicFile::readTags(){
    TagLib::MPEG::File f(fileLoc);
    title = f.tag()->title().toCString();
    album = f.tag()->album().toCString();
    artist = f.tag()->artist().toCString();
    coverArt = imageForTag(f.ID3v2Tag(true));
}
