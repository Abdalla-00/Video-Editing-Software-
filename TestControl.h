#ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <iostream>
#include <string>
#include "VideoRepo.h"
#include <random>
#include <unordered_set>
#include "Editor.h"
#include <sstream>

using namespace std;

class TestControl {
		
	public:
		void launch();
	
	private:
		int  sceneTest();
		int  videoTest();
		int  videoArrayTest();
		int  videoRepoTest();
		int  editorTest();

		

		//initialize with some Songs and Albums
		void initialize(VideoRepo&, Editor&);

		void initialize(VideoRepo&);

		int editorTestHelper(Editor&, int videoIndex, vector<int>& sceneIndex);

		void initCapture();
		void endCapture();		
		void test();

		// the return value is the number of mistakes found
		void findScenes(vector<int>& rvideo, vector<int>& rscene,int& error1, int& error2);
		void findScenesInOrder(vector<int>& rvideo, vector<int>& rscene, int& error1, int& error2);
		void findVideos(vector<int>& rvideo,int& error);
		void findVideosInOrder(vector<int>& rvideo, int& error);

		// generate a set (no duplicates) of "count" random integers
		// from 0 to "range"
		void ran(vector<int>& list, int count, int range);
		// generate a random integer in the given range
		int ran(int range_from, int range_to);

		// Some initial data
		const static string videoTitles[5];
		const static string descriptions[5];
		const static string sceneTitles[5][5];
		const static string sceneContent[5][5];

		streambuf* oldCoutStreamBuf;
    	ostringstream strCout;
		string output;
	
};
#endif