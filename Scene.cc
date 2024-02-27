
#include "Scene.h"

//constructor - initialize member variables
Scene::Scene(const string& title, const Date& date, const string& content) {
    this->title = title;
    this->date = date;
    this->content = content;
}


Scene::Scene(const Scene& s) {
    this->title = s.title;
    this->date = s.date;
    this->content = s.content;
}




//returns true if this scene's title matches title param
bool Scene::equals(const string& title) {
    if (this->title == title) return true;
    else return false;
}


//prints Scene metadata
void Scene::print() const {
    cout << "Scene Title: " << this->title << endl;
    cout << "Scene Date: ";
    date.print();
    cout << endl;
}

//plays Scenes - prints metadata followed by content
void Scene::play() const {
    print();
    cout << "Scene Content: " << this->content << endl;
}