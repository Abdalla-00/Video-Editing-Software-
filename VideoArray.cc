
#include "VideoArray.h"

//ctor
VideoArray::VideoArray() {
    numVids = 0;
    videoPtrs = new Video* [MAX_ARRAY];
}

//dtor
VideoArray::~VideoArray() {
    for (int i = 0; i < numVids; i++) {
        delete videoPtrs[i];
    }
//    delete [] videoPtrs;
}


//adds video as defined by Video::lessThan()
bool VideoArray::add(Video* video) {
    if (isFull()) return false; //array is full - fail
    else {
//        Video* newVid = new Video(*video); - deep copy results in diff address, fails test
        int i = 0;
        if (numVids == 0) {
            videoPtrs[0] = video;
            numVids++;
            return true; //success
        }
        else {
            while (i < numVids && (video->lessThan(*videoPtrs[i]) == false)) {
                i++;
            }
            for (int j = numVids; j > i; j--) {
                videoPtrs[j] = videoPtrs[j - 1];
            }
            videoPtrs[i] = video;
            numVids++;
            return true; //success
        }
    }
}

//returns true if array is full
bool VideoArray::isFull() const {
    if (numVids == MAX_ARRAY) return true;
    else return false;
}

//returns size of array
int VideoArray::size() const {
    return numVids;
}

//returns video w/ matching title, nullptr otherwise
Video* VideoArray::get(const string& title) const {
    for (int i = 0; i < numVids; i++) {
        if (videoPtrs[i]->getTitle() == title) {
            return videoPtrs[i];    //success
        }
    }
    return nullptr; //failure
}

//returns video @ index, nullptr otherwise
Video* VideoArray::get(int index) const {
    if (index < 0 || index >= numVids) return nullptr; //failure
    else {
        return videoPtrs[index]; //success
    }
}

//remove + return video w/ matching title, nullptr otherwise
Video* VideoArray::remove(const string& title) {
    for (int i = 0; i < numVids; i++) {
        if (videoPtrs[i]->getTitle() == title) {
            Video* vid = videoPtrs[i];
            delete videoPtrs[i];
            for (int j = i; j < numVids - 1; j++) {
                videoPtrs[j] = videoPtrs[j + 1];
            }
            numVids--;
            return vid;    //success
        }
    }
    return nullptr; //failure
}

//remove + return video @ index, nullptr otherwise
Video* VideoArray::remove(int index) {
    if (index < 0 || index >= numVids) return nullptr; //failure
    else {
//        Video* copy = new Video(*videoPtrs[index]);
//        delete videoPtrs[index];
//        for (int i = index; i < numVids - 1; i++) {
//            videoPtrs[i] = videoPtrs[i + 1];
//        }
        numVids--;
//        return copy; //success

        return videoPtrs[index];
    }
}