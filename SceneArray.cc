
#include "SceneArray.h"

//ctor
SceneArray::SceneArray() {
    numPtrs = 0;
    scenePtrs = new Scene* [MAX_ARRAY];
}

//dtor
SceneArray::~SceneArray() {
   for (int i = 0; i < numPtrs; i++) {
       delete scenePtrs[i];
   }
//   delete [] scenePtrs;
}


//adds scene to back of array
bool SceneArray::add(Scene* scene) {
    if (isFull()) return false; //array is full - fail
    else {
        scenePtrs[numPtrs] = scene;
        numPtrs++;
        return true; //success
    }
}

//adds scene to array at index
bool SceneArray::add(Scene* scene, int index) {
    if (isFull() || index > numPtrs) return false; //array is full - fail
    else {
        if (numPtrs == index) {
            scenePtrs[index] = scene;
            numPtrs++;
            return true; //success
        }
        else {
            for (int i = numPtrs; i > index; i--) {
                scenePtrs[i] = scenePtrs[i - 1];
            }
            scenePtrs[index] = scene;
            numPtrs++;
            return true; //success
        }
    }
}

//returns true if array is full
bool SceneArray::isFull() const {
    if (numPtrs == MAX_ARRAY) return true;
    else return false;
}

//returns scene @ index, nullptr otherwise
Scene* SceneArray::get(int index) const {
    if (index < 0 || index >= numPtrs) {
        return nullptr; //index OOB - fail
    }
    else {
        return scenePtrs[index]; //success
    }
}

//remove + return scene @ index, nullptr otherwise
Scene* SceneArray::remove(int index) {
    if (index < 0 || index >= numPtrs) {
        return nullptr; //index OOB - fail
    }
    else {
        Scene* s = scenePtrs[index];
        delete scenePtrs[index];
        for (int i = index; i < numPtrs - 1; i++) {
            scenePtrs[i] = scenePtrs[i + 1];
        }
        numPtrs--;
//        cout << s << endl;
        return s;
    }
}

//returns size of array
int SceneArray::size() const {
    return numPtrs;
}