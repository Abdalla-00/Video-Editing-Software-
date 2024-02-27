
#ifndef VIDEOREPO_H
#define VIDEOREPO_H

#include "VideoArray.h"

class VideoRepo {

    public:

        VideoRepo(); //ctor
        ~VideoRepo(); //dtor

        //if video !exist, add copy to repo
        //if video exists, update -> Video::updateScenes()
        //else fail - "error msg"
        void saveVideo(const Video& video);

        //if video exists, remove from repo
        //else fail - "error msg"
        void deleteVideo(int index);

        //if video exists, return Video* + true
        //else return nullptr + false
        bool downloadVideo(int index, const Video** video) ;
        bool downloadVideo(int index, Video** video) ;

        void printVideos() const; //print all videos in repo
        void playVideos() const; //play all videos in repo
        void playVideo(int index) const; //play video @ index
        void playScene(int videoIndex, int sceneIndex) const; //play scene @ index in video @ index

    private:
        VideoArray* videos; //array of Video ptrs
        int numVids; //number of videos in repo
};


#endif //VIDEOREPO_H
