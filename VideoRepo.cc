
#include "VideoRepo.h"

//ctor
VideoRepo::VideoRepo() {
    videos = new VideoArray();
    numVids = 0;
}

//dtor
VideoRepo::~VideoRepo() {
    delete videos;
}

//if video !exist, add copy to repo
//if video exists, update -> Video::updateScenes()
//else fail
void VideoRepo::saveVideo(const Video& video) {
    if (videos->isFull()) {
        cout << "failed to add/update - repository is full." << endl;
        return;
    }
    else {
        //if video !exist - create copy & add to repo
        if ((videos->get(video.getTitle())) == nullptr) {
            Video* vid = new Video(video);
            videos->add(vid);
            numVids++;
            cout << "video " << vid->getTitle() << " created successfully" << endl;
            return;
        }
        else {
            //if video exists - update scenes
            videos->get(video.getTitle())->updateScenes(video);
            cout << "video exists - scenes updated successfully" << endl;
            return;
        }
    }
}

//if video exists, remove from repo
//else fail - "error msg"
void VideoRepo::deleteVideo(int index) {
    //check if video exists
    if (videos->get(index) == nullptr) {
        cout << "failed to delete - video does not exist." << endl;
        return;
    }
    else {
        videos->remove(index);
        numVids--;
        cout << "video deleted successfully" << endl;
        return;
    }
}



//if video exists, return Video* + true
//else return nullptr + false
bool VideoRepo::downloadVideo(int index, const Video** video) {
    //check if video exists
    if (videos->get(index) == nullptr) {
        cout << "failed to download - video does not exist." << endl;
        *video = nullptr;
        return false;
    }
    else {
        *video = videos->get(index);
        cout << "video " << video << " downloaded successfully" << endl;
        return true;
    }
}

bool VideoRepo::downloadVideo(int index, Video** video) {
//check if video exists
    if (videos->get(index) == nullptr) {
        cout << "failed to download - video does not exist." << endl;
        *video = nullptr;
        return false;
    }
    else {
        *video = videos->get(index);
        cout << "video " << video << " downloaded successfully" << endl;
        return true;
    }
}

//print all videos in repo
void VideoRepo::printVideos() const {
    for (int i = 0; i < videos->size(); i++) {
        videos->get(i)->print();
    }
}

//play all videos in repo
void VideoRepo::playVideos() const {
    for (int i = 0; i < videos->size(); i++) {
        videos->get(i)->play();
    }
}

//play video @ index
void VideoRepo::playVideo(int index) const {
    if (videos->get(index) == nullptr) {
        cout << "failed to play - video does not exist." << endl;
        return;
    }
    else videos->get(index)->play();
}

//play scene @ index in video @ index
void VideoRepo::playScene(int videoIndex, int sceneIndex) const {
    videos->get(videoIndex)->playScene(sceneIndex);
}