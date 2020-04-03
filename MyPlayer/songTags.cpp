#include "songTags.h"

void readTags(const char * file){
    ID3_Tag myTag;
    myTag.Link(file);
    ID3_Tag::Iterator* iter = myTag.CreateIterator();
    ID3_Frame* myFrame = NULL;
    while (NULL != (myFrame = iter->GetNext()))
    {
      //std::cout<<iter;
    }
    delete iter;
}
