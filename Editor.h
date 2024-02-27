
#ifndef EDITOR_H
#define EDITOR_H

#include "VideoRepo.h"

class Editor {

    public:

        Editor(); //ctor
        ~Editor(); //dtor

        //creates new video w/ arguments
        //store it in 'video' member variable
        //delete prev vid if exists
        void newVideo(const string& title, const string& description);

        //adds scene to SceneArray @ index
        void addScene(int index, const string& title, const Date& date, const string& content);

        //adds scene to back of SceneArray
        void addScene(const string& title, const Date& date, const string& content);

        //deletes scene @ index
        void deleteScene(int index);

        //attempt to download video from repo @ index
        //if successful, replace 'video' member variable w/ copy of downloaded video
        void downloadVideo(int index, VideoRepo& repo);

        //attempt to save/update video to repo
        void uploadVideo(VideoRepo& repo);

        void printVideo() const;  //print video stored in Editor
        void playVideo() const;   //play video stored in Editor
        void playScene(int index) const;  //play scene @ index in video stored in Editor

    private:
        Video* curVideo; //video currently being edited
};


#endif //EDITOR_H
