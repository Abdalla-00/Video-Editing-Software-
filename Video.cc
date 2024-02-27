
#include "Video.h"

//constructor - initialize member variables
Video::Video(const string& title, const string& description) {
    this->title = title;
    this->description = description;
    scenes = new SceneArray();
}

//copy constructor - create deep copy of video
Video::Video(const Video& vid) {
    //Video(vid.title, vid.description);
    this->title = vid.title;
    this->description = vid.description;
    this->scenes = new SceneArray();
    for (int i = 0; i < vid.scenes->size(); i++) {
        Scene* s = new Scene(*vid.scenes->get(i));
        scenes->add(s);
    }
}

//destructor - deallocate memory for Video
Video::~Video() {
    // for (int i = 0; i < scenes->size(); i++) {
    //     delete scenes->get(i);
    // }
    delete scenes;
}


//returns video title
string Video::getTitle() const {
    return title;
}

//returns true if this video's title matches title param
bool Video::equals(const string& vidTitle) {
    if (this->title == vidTitle) return true;
    else return false;
}


//returns true if this video's title comes before vid's title
bool Video::lessThan(const Video& vid) const {
    if (title < vid.title) return true;
    else return false;
}

//adds scene to scenes array @ index
bool Video::addScene(int index, const string& sceneTitle, const Date& date, const string& content) {
    Scene* scene = new Scene(sceneTitle, date, content); //create new scene w given data
    if (scenes->add(scene, index)) return true; //success
    else return false; //fail
}

//adds scene to back of scenes array
bool Video::addScene(const string& sceneTitle, const Date& date, const string& content) {
    Scene* s = new Scene(sceneTitle, date, content);
    if (scenes->add(s)) return true; //success
    else return false; //fail
}

//deletes scene @ index
bool Video::deleteScene(int index) {
    if (scenes->remove(index)) return true; //success
    else return false; //fail
}

//replace current scenes with copy of video's scenes
void Video::updateScenes(const Video& video) {
//    delete scenes;
    scenes = new SceneArray(*video.scenes);
}


//returns number of scenes in this video
int Video::numScenes() const {
    return scenes->size();
}

//prints video metadata
void Video::print() const {
    cout << "Video: " << title << endl;
    cout << "Description: " << description << endl;
    cout << "Number of scenes: " << scenes->size() << endl;
}

//prints video metadata followed by all scenes
void Video::printScenes() const {
    print();
    for (int i = 0; i < scenes->size(); i++) {
        scenes->get(i)->print();
    }
}

//prints video metadata and plays all scenes
void Video::play() const{
    print();
    for (int i = 0; i < scenes->size(); i++) {
        scenes->get(i)->play();
    }
}

//plays scene @ index
Scene* Video::playScene(int index) const {
    if (index < scenes->size()) {
        scenes->get(index)->play();
        return scenes->get(index);
    }
    else return nullptr;
}
