
#include "Editor.h"

//ctor
Editor::Editor() {
    Video* curVideo = nullptr;
}

//dtor
Editor::~Editor() {
    delete curVideo;
}

//creates new video w/ arguments
//store it in 'video' member variable
//delete prev vid if exists
void Editor::newVideo(const string& title, const string& description) {
    if (curVideo == nullptr) {
        curVideo = new Video(title, description);
    }
    else {
        for (int i = curVideo->numScenes() - 1; i >= 0; i--) {
            curVideo->deleteScene(i);
        }
        delete curVideo;
        curVideo = new Video(title, description);
    }
}

//adds scene to SceneArray @ index
void Editor::addScene(int index, const string& title, const Date& date, const string& content) {
    curVideo->addScene(index, title, date, content);
}

//adds scene to back of SceneArray
void Editor::addScene(const string& title, const Date& date, const string& content) {
    curVideo->addScene(title, date, content);
}

//deletes scene @ index
void Editor::deleteScene(int index) {
    curVideo->deleteScene(index);
}

//attempt to download video from repo @ index
//if successful, replace 'video' member variable w/ copy of downloaded video
void Editor::downloadVideo(int index, VideoRepo& repo) {
    if (repo.downloadVideo(index, &curVideo) == true) {
        Video* copy = new Video(*curVideo);
        delete curVideo;
        curVideo = copy;
        cout << "successfully downloaded video: " << curVideo->getTitle() << endl;
    } else {
        cout << "Failed to download video." << endl;
    }

}

//attempt to save/update video to repo
void Editor::uploadVideo(VideoRepo& repo) {
    repo.saveVideo(*curVideo);
}

void Editor::printVideo() const {
    curVideo->print();
}

void Editor::playVideo() const {
    curVideo->play();
}

void Editor::playScene(int index) const {
    curVideo->playScene(index);
}
