
#ifndef T5_V2_VIDEO_H
#define T5_V2_VIDEO_H

#include "SceneArray.h"

class Video {

public:

    Video(const string& title, const string& description); //ctor
    Video(const Video& video); //copy ctor
    ~Video(); //dtor

    string getTitle() const; //returns title

    //returns true if title matches
    bool equals(const string& title);
    //returns true if this title comes before vid's title
    bool lessThan(const Video& vid) const;
    //adds scene to scenes array @ index - false if full
    bool addScene(int index, const string& title, const Date& date, const string& content);
    //adds scene to back of scenes array - false if full
    bool addScene(const string& sceneTitle, const Date& date, const string& content);
    //deletes scene @ index - false if fails
    bool deleteScene(int index);

    //replace current scenes with copy of video's scenes
    void updateScenes(const Video& video);

    int numScenes() const; //returns number of scenes
    void print() const; //prints video metadata
    void printScenes() const; //prints vid metadata followed by all scenes
    void play() const; //prints vid metadata and plays all scenes

    Scene* playScene(int index) const; //plays scene @ index

private:
    string title;
    string description;
    SceneArray* scenes;

};


#endif //T5_V2_VIDEO_H
