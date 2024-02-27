
#ifndef T5_V2_SCENE_H
#define T5_V2_SCENE_H

#include "Date.h"


class Scene {

public:
    Scene(const string& title, const Date& date, const string& content);    //ctor
    Scene(const Scene&);

    bool equals(const string& title); //true if title param = title member

    void print() const;   //prints Scene metadata
    void play() const;    //prints metadata followed by content

private:
    string title;   //Scene title
    string content; //Scene content
    Date date;    //Scene date

};


#endif //T5_V2_SCENE_H
