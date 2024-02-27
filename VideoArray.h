
#ifndef VIDEOARRAY_H
#define VIDEOARRAY_H

#include "Video.h"
#include "defs.h"


class VideoArray {

    public:

        VideoArray(); //ctor
        ~VideoArray(); //dtor

        bool add(Video* video); //adds video as defined by Video::lessThan()
        bool isFull() const; //returns true if array is full

        int size() const; //returns size of array

        Video* get(const string& title) const; //returns video w/ matching title, nullptr otherwise
        Video* get(int index) const; //returns video @ index, nullptr otherwise
        Video* remove(const string& title); //remove + return video w/ matching title, nullptr otherwise
        Video* remove(int index); //remove + return video @ index, nullptr otherwise


    private:
        int numVids; //number of Video ptrs in array
        Video** videoPtrs; //dyn alloc array of Video ptrs - backing array

};


#endif //VIDEOARRAY_H
