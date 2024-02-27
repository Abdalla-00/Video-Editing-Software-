
#ifndef SCENEARRAY_H
#define SCENEARRAY_H

#include "Scene.h"
#include "defs.h"

class SceneArray {

public:

    SceneArray(); //ctor
   ~SceneArray(); //dtor

    bool add(Scene* scene); //add scene to back of array
    bool add(Scene* scene, int index); //adds scene @ index
    bool isFull() const; //returns true if array is full

    Scene* get(int index) const; //returns scene @ index, nullptr otherwise
    Scene* remove(int index); //remove + return scene @ index, nullptr otherwise

    int size() const; //returns size of array

private:
    int numPtrs; //number of Scene ptrs in array
    Scene** scenePtrs; //dyn alloc array of Scene ptrs - backing array
};


#endif //SCENEARRAY_H
