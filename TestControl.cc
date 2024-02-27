
#include "TestControl.h"
#include "TestView.h"
#include "Editor.h"
#include <limits>

using namespace std;
const string videoTitlesInOrder[5] = {"Carleton Experiences","Cornwall Bound!", "My Family","Rants and Ravings","Safari"};


void pressEnterToContinue();

void TestControl::launch(){
    //make a view, get input, launch the appropriate test
    TestView view;
    int choice = 5;
    test();
    while (choice!=0){
        cout<<endl<<"NOTE: Tests 4 and 5 require a manual inspection of the output to determine the mark"<<endl;
        view.showMenu(choice);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(choice){
            case 1: sceneTest(); break;
            case 2: videoTest(); break;
            case 3: videoArrayTest(); break;
            case 4: videoRepoTest(); break;
            case 5: editorTest(); break;
        }
    }
}

void TestControl::initCapture(){
    oldCoutStreamBuf = std::cout.rdbuf();
    ostringstream temp;
    strCout.swap(temp);
    std::cout.rdbuf( strCout.rdbuf() );
}

void TestControl::endCapture(){
    std::cout.rdbuf( oldCoutStreamBuf );
    output = strCout.str();
    std::cout << output;
}

void TestControl::findScenes(vector<int>& rvideo, vector<int>& rscene,
        int& error1, int& error2){
    int found = -1;
    int fcontent = -1;
    error1 = 0; error2 = 0;

    vector<int>::iterator iscene, ivid;

    for (ivid = rvideo.begin(); ivid != rvideo.end(); ++ivid){
        for (iscene = rscene.begin(); iscene != rscene.end(); ++iscene){    
            found = output.find(sceneTitles[*ivid][*iscene]);
            fcontent = output.find(sceneContent[*ivid][*iscene]);
            if (found == string::npos){
                std::cout<<"Scene title "<<sceneTitles[*ivid][*iscene]<<" not found"<<endl;
                ++error1;
            } 
            if (fcontent == string::npos){
                std::cout<<"Scene content for "<<sceneTitles[*ivid][*iscene]<<" not found"<<endl;
                ++error2;
            }  
        }
    }
}

void TestControl::findScenesInOrder(vector<int>& rvideo, vector<int>& rscene, int& error1, int& error2){
    int found = -1;
    int fcontent = -1;
    error1 = 0; error2 = 0;
    vector<int>::iterator iscene, ivid;

    for (ivid = rvideo.begin(); ivid != rvideo.end(); ++ivid){
        for (iscene = rscene.begin(); iscene != rscene.end(); ++iscene){    
            found = output.find(sceneTitles[*ivid][*iscene], found+1);
            fcontent = output.find(sceneContent[*ivid][*iscene], fcontent+1);
            if (found == string::npos){
                std::cout<<"ERROR: Scene title "<<sceneTitles[*ivid][*iscene]<<" not found in correct place"<<endl;
                ++error1;
            } 
            if (fcontent == string::npos){
                std::cout<<"ERROR: Scene content for "<<sceneTitles[*ivid][*iscene]<<" not found in correct place"<<endl;
                ++error2;
            } 
        }
    }
}

void TestControl::findVideosInOrder(vector<int>& rvideo, int& error){
    int found = -1;
    error = 0;
    vector<int>::iterator ivid;
    for (ivid = rvideo.begin(); ivid != rvideo.end(); ++ivid){
        found = output.find(videoTitles[*ivid], found+1);
        if (found == string::npos){
            std::cout<<"ERROR: Video "<<videoTitles[*ivid]<<" not found in order"<<endl;
            ++error;
        } 
    }
}

void TestControl::findVideos(vector<int>& rvideo, int& error){
    int found = -1;
    error = 0;
    vector<int>::iterator ivid;
    for (ivid = rvideo.begin(); ivid != rvideo.end(); ++ivid){
        found = output.find(videoTitles[*ivid]);
        if (found == string::npos){
            std::cout<<"ERROR: Video "<<videoTitles[*ivid]<<" not found"<<endl;
            ++error;
        } 
    }
}

void TestControl::test(){
    vector<int> rvideo;   //random videos
    vector<int>::iterator  ivid; //iterators for the vector

    int count = 0;

    ran(rvideo, 3, 5); // choose 2 out of 5 videos
    
    for (ivid = rvideo.begin(); ivid != rvideo.end(); ++ivid){
        cout<<*ivid<<endl;
    }
}


int TestControl::sceneTest(){
    Scene* scenes[6];
    
    vector<int> rscene;    //random scenes
    vector<int> rvideo;    //random videos

    vector<int>::iterator iscene, ivid; //iterators for the vectors

    int count = 0;

    ran(rvideo, 2, 5); // choose 2 out of 5 videos
    ran(rscene, 3, 5); // choose 3 out of 5 scenes
    
    for (ivid = rvideo.begin(); ivid != rvideo.end(); ++ivid){
        for (iscene = rscene.begin(); iscene != rscene.end(); ++iscene){    
            scenes[count++] = new Scene( sceneTitles[*ivid][*iscene], Date(), sceneContent[*ivid][*iscene]);
            std::cout<<endl<<"Adding "<<sceneTitles[*ivid][*iscene] <<endl;
        }
    }
    
    std::cout<<endl<<"Displaying scenes:"<<endl<<endl;

    initCapture();

    for (int i = 0; i < count; ++i){
        scenes[i]->play(); std::cout<<endl;
        delete scenes[i];
    }

    endCapture();

    int error1 = 0, error2 = 0;

    findScenesInOrder(rvideo, rscene, error1, error2);

    int mark = 0;
    mark += error1==0?1:0;
    mark += error2==0?1:0;
    std::cout <<"Test complete, "<<mark<<" out of 2 marks"<<endl;
    return mark;
}
		
int TestControl::videoTest(){
    vector<int> rscene, rvid;    //random scene
    Video* vids[2];
    vector<int>::iterator iscene, ivid; //iterators for the vectors

    int count = 0;
    ran(rscene, 2, 5); // choose 2 out of 5 scenes
    ran(rvid, 2, 5); // choose 2 out of 5 videos
    for (ivid = rvid.begin(); ivid!=rvid.end(); ++ivid){
        std::cout<<endl<<"Adding Video  "<<videoTitles[*ivid]<<endl;
        vids[count] = new Video(videoTitles[*ivid], descriptions[*ivid]);
        for (iscene = rscene.begin(); iscene != rscene.end(); ++iscene){ 
            std::cout<<"Adding Scene to Video: "<<videoTitles[*ivid]<<endl;
            vids[count]->addScene(sceneTitles[*ivid][*iscene], Date(), sceneContent[(*ivid)][*iscene]);
        }
        ++count;
    }

    std::cout<<endl<<"Playing videos with scenes (should be 2 videos and 2 scenes each video):"<<endl;

    initCapture();

    for (int i = 0; i < 2; ++i){
        vids[i]->play();
    }

    endCapture();

    int error1 = 0, error2 = 0;

    findScenesInOrder(rvid, rscene, error1, error2);

   
    int mark = 0;
    mark += error1==0?1:0;
    mark += error2==0?1:0;
    std::cout <<"Video add scene and play test complete, "<<mark<<" out of 2 marks"<<endl;
    

    pressEnterToContinue();


    for (int i = 0; i < 2; ++i){
        delete vids[i];
    }

    
    std::cout<<"Testing add Scene at index"<<endl;
    Video* video = new Video(videoTitles[0], descriptions[0]);
    rvid = {0}; rscene = {0};
    
    std::cout<<endl<<"Adding scene at bad index (0 scenes, adding at index 2)"<<endl;
    video->addScene(2, sceneTitles[0][0], Date(), sceneContent[0][0]);
    initCapture();
    video->play();
    endCapture();

    findScenes(rvid, rscene, error1, error2);
    if (error1 == 0){
        cout<<"ERROR: scene "<<sceneTitles[0][0]<<" found, -2 marks"<<endl;
    }else{
        std::cout<<"Scene "<< sceneTitles[0][0] <<" did not print, 2 marks"<<endl;
        mark+=2;
    }
    pressEnterToContinue();
    std::cout<<endl<<"Adding 3 scenes at good indices and playing"<<endl;
    video->addScene(0, sceneTitles[0][3], Date(), sceneContent[0][3]);
    video->addScene(0, sceneTitles[0][1], Date(), sceneContent[0][1]);
    video->addScene(1, sceneTitles[0][2], Date(), sceneContent[0][2]);


    rscene = {1, 2, 3};

    std::cout<<"Checking scenes were added in order:"<<endl;
    initCapture();

    video->play();

    endCapture();

    findScenesInOrder(rvid, rscene, error1, error2);

    if (error1 ==0 && error2 ==0){
        std::cout<<"Scenes were in correct order, 2 marks"<<endl;
        mark += 2;
    }else{
        std::cout<<"ERROR at least one scene out of order or not found, -2 marks"<<endl;
    }
    pressEnterToContinue();

    rscene = {1,3};

    std::cout<<"Testing remove scene at index 1 (2 scenes left):"<<endl;
    video->deleteScene(1);
    
    initCapture();
    video->play();
    endCapture();

    findScenesInOrder(rvid, rscene, error1, error2);

    if (error1 ==0 && error2 ==0){
        std::cout<<"Scenes were in correct order, 1 marks"<<endl;
        mark += 1;
    }else{
        std::cout<<"ERROR at least one scene our of order or not found, -1 marks"<<endl;
    }
    pressEnterToContinue();
    
    rscene = {3};
    std::cout<<"Testing remove scene at index 0 (1 scene left):"<<endl;
    video->deleteScene(0);

    initCapture();

    video->play();

    endCapture();

    findScenesInOrder(rvid, rscene, error1, error2);

    if (error1 ==0 && error2 ==0){
        std::cout<<"Scenes were in correct order, 1 marks"<<endl;
        mark += 1;
    }else{
        std::cout<<"ERROR at least one scene our of order or not found, -1 marks"<<endl;
    }
    pressEnterToContinue();


    std::cout<<"Testing remove scene at index 1 (should not remove anything):"<<endl;
    if (video->deleteScene(1)){
        std::cout<<"Remove at bad index should return false, -1 mark"<<endl;
    }else{
        mark+=1;
    }
    std::cout<<"Displaying video (should be 1 scene):"<<endl;

    initCapture();
    video->play();
    endCapture();

    findScenesInOrder(rvid, rscene, error1, error2);

    if (error1 ==0 && error2 ==0){
        std::cout<<"Scenes were in correct order, 1 marks"<<endl;
        mark += 1;
    }else{
        std::cout<<"ERROR at least one scene our of order or not found, -1 marks"<<endl;
    }
    pressEnterToContinue();
   
    std::cout<<"Testing remove scene at index 0 (0 scenes left):"<<endl;
    video->deleteScene(0);

    std::cout<<"Printing video (should be 0 scenes printed)"<<endl;

    initCapture();
    video->play();
    endCapture();

    rscene = {0,1,2,3,4};

    findScenes(rvid, rscene, error1, error2);

    if (error1 ==5 && error2 ==5){
        std::cout<<"No scenes found, 1 marks"<<endl;
        mark += 1;
    }else{
        std::cout<<"ERROR at least one scene found, -1 marks"<<endl;
    }
    pressEnterToContinue();


    
    std::cout<<"Testing remove scene at index 0 (should fail):"<<endl;
    if (video->deleteScene(0)){
        std::cout<<"ERROR: getScene returned true, should return false, printing scene"<<endl;
        video->playScene(0);
    }else{
        std::cout<<"No scene found at index 0"<<endl;
        mark += 1;
    }
   
    delete video;

    float m = mark;
    
    std::cout<<"Marks earned: "<<(m>0?m:0)/2<<" out of 6."<<endl;
    return 0;
}
		
int TestControl::videoArrayTest(){
    int points = 0;

    vector<int> rvid;  //random artist
    vector<int> rscene;    //random scene
    Video* vids[4];
    vector<int>::iterator ivid, iscene; //iterators for the sets

    ran(rvid, 4, 5);
    ran(rscene, 2, 5); // choose 2 out of 5 scenes
    int count = 0;
    for (ivid = rvid.begin(); ivid!= rvid.end(); ++ivid){
        vids[count] = new Video(videoTitles[*ivid], descriptions[*ivid]);
        for (iscene = rscene.begin(); iscene != rscene.end(); ++iscene){ 
                vids[count]->addScene(vids[count]->numScenes(), sceneTitles[*ivid][*iscene], Date(), sceneContent[*ivid][*iscene]);
        }
        ++count;
    }
    
    std::cout<<"Adding Videos to VideoArray"<<endl;

    VideoArray* aa = new VideoArray();
    for (int i = 0; i < 4; ++i){
        std::cout<<"Adding: ";
        vids[i]->print();
        aa->add(vids[i]);
    }

    std::cout<<"VideoArray size (should be 4): "<<aa->size()<<endl;

    if (aa->size() ==4){
        std::cout<<"Correct size, +1 mark"<<endl;
        points += 1;
    }

    pressEnterToContinue();

    for (int i = 0; i < aa->size(); ++i){
        aa->get(i)->print();
    }
    
    const Video* vid;
     
    std::cout<<endl<<"Test get(title):   "<<endl<<endl;
    bool foundall = true;
    for (int i = 0; i < aa->size(); ++i){
        vid = aa->get(vids[i]->getTitle());
        if (vid != vids[i]){
            std::cout <<"Could not find "<<endl;
            vids[i]->print();
            foundall = false;
        }else{
            std::cout<<"Found "<<endl;
            vid->print();
        }
    }

    if (foundall){
        std::cout<<"Found all videos, +1 mark"<<endl<<endl;
        points += 1;
    }else{
        std::cout<<"Did not find all videos, 0 marks (out of 1)"<<endl;
    }

    pressEnterToContinue();
    vid = aa->get("TOP SECRET");
    if(vid!=NULL){
        std::cout<<"ERROR: Found non-existent TOP SECRET video, attempting to print:"<<endl;
        vid->print();
    }else{
        std::cout<<"Success: Did not find the (non-existent) TOP SECRET video, +1 marks"<<endl;
        points += 1;
    }
    
    std::cout<<endl<<"Test Video* get(int) (proper order): "<<endl<<endl;

    pressEnterToContinue();
    bool inorder = true;
    
    const Video *a1, *a2;
    for (int i = 1; i < aa->size(); ++i){
        a1 = aa->get(i-1);
        a2 = aa->get(i);
        if (a1 == NULL){
            std::cout<<"Error, video at index "<<i-1<<" not found"<<endl;
            inorder = false;
        }
        if (a2 == NULL){
            std::cout<<"Error, video at index "<<i<<" not found"<<endl;
            inorder = false;
        }

        if (inorder && a2->lessThan(*a1)){
            a1->print();
            a2->print();
            inorder = false;
            std::cout<<endl<<"Previous two videos are out of order"<<endl;
        }
    }

    for (int i = 0; i < aa->size(); ++i){
        aa->get(i)->print();
    }

    std::cout<<endl<<(inorder ? "In correct order, +2 marks": "Not in correct order")<<endl;
    if (inorder){points+=2;}

    pressEnterToContinue();

    int num = ran(0,4);
    std::cout << "Removing "<<endl;
    vids[num]->print();
    vid = aa->remove(vids[num]->getTitle());
    if (vid!=vids[num]){
        std::cout<<"ERROR: Could not find the above video, deducting 1 mark"<<endl;
        points -= 1;
    }

    if (aa->size() != 3){
        std::cout<<"VideoArray size error, should be 3, instead: "<<aa->size()<<endl;
    }else{
        std::cout<<"Size is correct after removal, +1 mark" <<endl;
        points += 1;
    }

    pressEnterToContinue();
    std::cout<<endl<<"Test proper order after remove: "<<endl<<endl;
    inorder = true;
    for (int i = 1; i < aa->size(); ++i){
        a1 = aa->get(i-1);
        a2 = aa->get(i);
        if (a2->lessThan(*a1)){
            a1->print();
            a2->print();
            inorder = false;
            std::cout<<endl<<"Previous two videos are out of order"<<endl;
        }
        if (vids[num]==a1 || vids[num]==a2){
            std::cout<<"Deleted video found"<<endl;
            inorder = false;
        }
    }

    for (int i = 0; i < aa->size(); ++i){
        aa->get(i)->print();
    }
    
    std::cout<<endl<<(inorder ? "In correct order": "Not in correct order")<<endl<<endl;
    if (inorder){std::cout<<"Delete successfull, +1 mark"<<endl; points += 1;}

    pressEnterToContinue();

    std::cout<<"Removing all videos from VideoArray..."<<endl;
    while (aa->size()>0){
        vid = aa->remove(0);
        std::cout<<"Removed: "<<endl;
        vid->print();
    }

    std::cout<<"VideoArray size (should be 0): "<<aa->size()<<endl;
    if (aa->size() == 0){
       std::cout<<"Success, +1 mark"<<endl;
        points += 1;
    }
    
    pressEnterToContinue();

    std::cout<<endl<<"Adding video back: "<<endl;
    vids[2]->print();
    pressEnterToContinue();
    aa->add(vids[2]);
    std::cout<<"Printing all videos (should be same video as above):"<<endl;
    for (int i = 0; i < aa->size(); ++i){
        a1 = aa->get(i);
        a1->print();
        if (a1 != vids[2]){
            std::cout<<"Wrong video added"<<endl;
        }else{
            std::cout<<"Delete all then add test passed, +2 marks"<<endl;
            points += 2;
        }
    }

    pressEnterToContinue();

    std::cout<<"Deleting VideoArray..."<<endl;
    delete aa;
    pressEnterToContinue();

    // You may uncomment this if your VideoArray does not delete Videos
//     std::cout<<"Deleting videos..."<<endl;
//     for (int i = 0; i < 4; ++i){
//         delete vids[i];
//     }

    std::cout<<"Note: this test may cause memory leaks depending on how memory management was implemented."<<endl;
    std::cout<<"Marks earned: "<<points/2<<" out of 5"<<endl;

    return points;
}

int TestControl::videoRepoTest(){
   
    int points = 6;
    VideoRepo videoRepo;
    std::cout<<"Initializing with Videos and scenes"<<endl;
    initialize(videoRepo);

    std::cout<<"Printing all videos (should be 5 videos) "<<endl<<endl;

    initCapture();
    videoRepo.printVideos();
    endCapture();

    vector<int> rvid = {0,1,2,3,4};
    int error = 0;

    findVideos(rvid, error);

    if (error > 0){
        std::cout<<"At least one video not found, -1 marks"<<endl;
        points -= 1;
    }else{
        std::cout<<"All videos found, 1 marks"<<endl;
    }
    pressEnterToContinue();
    
    std::cout<<endl<<"Playing all videos (should be 5 videos, 5 scenes each video): "<<endl;

    initCapture();
    videoRepo.playVideos();
    endCapture();

    vector<int> rscene = {0,1,2,3,4};
    findVideos(rvid, error);

    if (error > 0){
        std::cout<<"At least one video not found, -1 marks"<<endl;
        points -= 1;
    }else{
        std::cout<<"All videos found, 1 marks"<<endl;
    }
    pressEnterToContinue();
    std::cout<<"Searching for scenes"<<endl;
   
    int error2 = 0;

    findScenes(rvid, rscene, error, error2);

    if (error > 0 || error2 > 0){
        std::cout<<"At least one scene not found, -1 marks"<<endl;
        points -= 1;
    }else{
        std::cout<<"All scenes found, 1 marks"<<endl;
    }
    pressEnterToContinue();
    int tempMark = 0;
    std::cout<<endl<<"Testing getVideo, playVideo, and playScene..."<<endl;
    const Video* video;
    initCapture();
    for (int i = 0; i < 5; ++i){
        switch (i%3){
            case 0: videoRepo.downloadVideo(i, &video);
                    video->play(); 
                    break;
            case 1: for (int j = 0; j < 5; ++j){
                        videoRepo.playScene(i, j);
                    } break;
            case 2: videoRepo.playVideo(i); break;
        }              
        if (i%3==0){
            for (int j = 0; j < 5; ++j){
                videoRepo.playScene(i, j);
            }
        }else{
            videoRepo.playVideo(i);
        }
    }
    endCapture();
    rvid = {0,1,2,3,4};
    findScenes(rvid, rscene, error, error2);
    if (error>0||error2>0){
        // lose at most 3 marks
        tempMark = error+error2>2?3:error+error2;
        std::cout<<error+error2<<" errors found, -"<<tempMark<<" marks"<<endl;
        ++tempMark;
    }else{
        std::cout<<"All scenes found correctly"<<endl;
    }

    points -= tempMark;

    pressEnterToContinue();

    int videoIndex = ran(0,4);
    std::cout<<"Testing deleteVideo, printing Video that will be deleted:"<<endl<<endl;
    std::cout <<"********deleted Video START********"<<endl;
    //TODO remove following line
    initCapture();
    videoRepo.playVideo(videoIndex);
    endCapture();

    std::cout<<"********deleted Video END********"<<endl<<endl;

    videoRepo.deleteVideo(videoIndex);
        
    std::cout<<"Video deleted, printing videos, ensure video listed above is not found"<<endl;
    pressEnterToContinue();
    videoRepo.printVideos();
    pressEnterToContinue();
    cout<<endl<<"Downloading and printing again, ensure video listed above is not found:"<<endl;
    pressEnterToContinue();
    videoRepo.downloadVideo(videoIndex, &video);
    video->print();
    
    cout<<endl<<"***********MANUAL 1 MARK*************"<<endl;
    cout<<"Deleted video did not get printed in either step"<<endl<<endl;

    std::cout<<endl<<"Points earned: "<<(points>0?points:0)<<" out of 7 plus 1 mark if deleted video is not printed"<<endl;
    return (points>0?points:0);
}




int TestControl::editorTest(){

    /*
    * List of things to test:
    *   1. newVideo, addScene and upload new video are tested in initialize
    *   2. download a random video, test editor print functions
    *   3. delete a scene, try and find in editor and in repo (should find scene in repo, not in editor)
    *   4. upload video to repo, try and play scene in repo again (should not find scene in repo)
    *   5. delete video from repo, test editor again.
    */
    VideoRepo videoRepo;
    Editor editor;

    std::cout <<"Initializing VideoRepo using Editor"<<endl<<endl;

    initialize(videoRepo, editor);

    int videoIndex = 1;


    std::cout <<"Testing download...downloading "<<endl<<videoTitles[videoIndex]<<endl<<
            " or "<<endl<<videoTitlesInOrder[videoIndex]<<endl<<" depending on whether Videos are stored in order or not"<<endl;

    //TODO: CHANGE HERE
    editor.downloadVideo(videoIndex, videoRepo);

    cout<<"Attempting to play downloaded video"<<endl;

    pressEnterToContinue();

    editor.playVideo();

    cout<<"***********MANUAL 2 MARKs*************"<<endl;
    cout<<"Ensure the Scenes match one of"<<endl;
    for (int i = 0; i < 5; ++i){
        cout<<sceneTitles[1][i]<<" ";
    }

    cout<<endl<<" or "<<endl;

    for (int i = 0; i < 5; ++i){
        cout<<sceneTitles[2][i]<<" ";
    }
    cout<<endl;
    pressEnterToContinue();
 
    std::cout<<endl<<"Deleting random scene in Editor. The Video will be played once in the VideoRepo and once in the Editor. "<<endl;
    std::cout<<"The first time it is played (in VideoRepo) it should have 5 scenes, the second time it is played (in Editor) it should have 4 scenes."<<endl;
    std::cout<<"You must visually inspect the output to verify it is correct. "<<endl<<endl;

    int sceneIndex = ran(0,4);

    editor.deleteScene(sceneIndex);

    /*compare editor playVideo to videoRepo playVideo. I guess. This will require manuel inspection*/
    cout<<"***********MANUAL 1 MARK*************"<<endl;
    cout<<"Ensure that exactly one Scene is different in the two videos played below."<<endl;
    pressEnterToContinue();

    videoRepo.playVideo(videoIndex);
    cout<<endl<<"************COMPARE TO*************"<<endl;
    pressEnterToContinue();
    editor.playVideo();
    cout<<endl<<"Please inspect for correctness."<<endl;
    pressEnterToContinue();

    std::cout<<endl<<"Uploading editted Video to VideoRepo and testing again"<<endl;
    std::cout<<endl<<"(Now the two videos should be identical)"<<endl<<endl;
   

    cout<<"***********MANUAL 1 MARK*************"<<endl;
    cout<<"Ensure all **4** Scenes are the same"<<endl<<endl;
    pressEnterToContinue();
    editor.uploadVideo(videoRepo);
    videoRepo.playVideo(videoIndex);
    cout<<endl<<"************COMPARE TO*************"<<endl;
    pressEnterToContinue();
    editor.playVideo();
    cout<<endl<<"Please inspect for correctness."<<endl;
    pressEnterToContinue();
    //we would expect a different scene to play here

    std::cout<<endl<<"Deleting video from VideoRepo (should still exist in Editor if you correctly did deep copy)"<<endl<<endl;
    pressEnterToContinue();
    videoRepo.deleteVideo(videoIndex);
    std::cout<<"Attempting to play video in editor:"<<endl;
       
    cout<<"***********MANUAL 1 MARK*************"<<endl;
    cout<<"Ensure all **4** Scenes are there"<<endl;
    pressEnterToContinue();
    
    editor.playVideo();
    cout<<endl<<"Please inspect for correctness."<<endl;
    pressEnterToContinue();
    
    cout<<endl<<"All Editor tests complete, manually determine the mark out of 5"<<endl;
    return 0;
   
}

int TestControl::editorTestHelper(Editor& editor, int videoIndex, vector<int>& sceneIndices){

    initCapture();
    editor.printVideo();
    endCapture();

    int found = -1;
    
    found = output.find(videoTitles[videoIndex], found+1);
    if (found == string::npos){
        std::cout<<"Video "<<videoTitles[videoIndex]<<" not found"<<endl;
        std::cout<<"Cannot set video in editor abort"<<endl;
        return 5;
    }  
    
    int errors = 0;
    pressEnterToContinue();

    cout<<"Test play video from editor"<<endl;

    initCapture();
    editor.playVideo();
    endCapture();

    int error1 = 0, error2 = 0;

    vector<int> rvid = {videoIndex};

    findScenes(rvid, sceneIndices, error1, error2);

    if (error1>0||error2>0){
        std::cout<<"Could not find (at least one) scene"<<endl;
        errors = (error1 + error2>2?3:error1+error2);
    }  else{
        cout<<"All scenes found"<<endl;
    }
    

    std::cout<<endl<<"Testing editor play scenes "<<endl<<endl;

    initCapture();
    for (int scene: sceneIndices){
        editor.playScene(scene);
    }   
    endCapture();

    findScenes(rvid, sceneIndices, error1, error2);

    if (error1>0||error2>0){
        std::cout<<"Could not find (at least one) scene"<<endl;
        errors = (error1 + error2>2?3:error1+error2);
    }  else{
        cout<<"All scenes found"<<endl;
    }

    return errors;
    
}

void TestControl::initialize(VideoRepo& videoRepo){
    // intialize 5 videos with 5 scenes each
    for (int i = 0; i < 5; ++i){
        Video* v = new Video(videoTitles[i], descriptions[i]);
        //scene loop
        for (int j = 0; j < 5; ++j){
            v->addScene(sceneTitles[i][j], Date(),sceneContent[i][j]);
        }
        videoRepo.saveVideo(*v);
        delete v;
    }

}

void TestControl::initialize(VideoRepo& videoRepo, Editor& editor){
    // intialize 5 videos with 5 scenes each
   for (int i = 0; i < 5; ++i){
        editor.newVideo(videoTitles[i], descriptions[i]);
        //scene loop
        for (int j = 0; j < 5; ++j){
            editor.addScene(sceneTitles[i][j], Date(),sceneContent[i][j]);
        }
        editor.uploadVideo(videoRepo);
    }

}

// s is the set to store count random numbers from 0 to range - 1
void TestControl::ran(vector<int>& list, int count, int range){
    unordered_set<int> s;
    const int range_from  = 0;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range-1);

    while (s.size() < count){
        s.insert(distr(generator));
    }
    unordered_set<int>::iterator it;
    for (it = s.begin(); it!=s.end();++it){
        list.push_back(*it);
    }
}

// generate and return a single random number in the range range_from to range_to - 1
int TestControl::ran(int range_from, int range_to){
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to-1);
    return distr(generator);
}

// strangely difficult to get this to work correctly
void pressEnterToContinue(){
    std::cout << "Press enter to continue..."<<endl;
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    char c = cin.get();
    while ( c != '\n') { 
        c = cin.get();
    }
}


// random titles
const string TestControl::videoTitles[5] = {"Safari", "My Family", "Cornwall Bound!", "Carleton Experiences", "Rants and Ravings"};


const string TestControl::descriptions[5] = {"My African safari", "Funny family video", "My trips to Cornwall", "Friends and fellow students", "My thoughts on anything and everything"};

const string TestControl::sceneTitles[5][5] =
{"Lion", "Tiger", "Fishbowl", "Alien", "Castle", "Love", "Anonymous", "Games","Music","Welcome","Monkey", "Stranger","Ant","Turtle","Smile","Crab","City","Apple","Pig","Dog","Helicopter","Unlock","Santa's Sleigh", "Guitar","Whale"};

const string TestControl::sceneContent[5][5] = {
R"(
 ▄▀▀▀▀▀───▄█▀▀▀█▄
▐▄▄▄▄▄▄▄▄██▌▀▄▀▐██
▐▒▒▒▒▒▒▒▒███▌▀▐███
 ▌▒▓▒▒▒▒▓▒██▌▀▐██
 ▌▓▐▀▀▀▀▌▓─▀▀▀▀▀)",

R"(
┼┼┼┼┼┼┼┼▓▓▓▓┼┼┼
┼╔═▒▒▒▒▓▄░░▄▓┼┼
┼▀┼▒▒▒▓▓▒──▒▓▓┼
┼┼┼▒▌▒▐┼▓▓▓▓┼┼┼)",

R"(
─▀▀▌───────▐▀▀
─▄▀░◌░░░░░░░▀▄
▐░░◌░▄▀██▄█░░░▌
▐░░░▀████▀▄░░░▌
═▀▄▄▄▄▄▄▄▄▄▄▄▀═
)",

R"(
▒▒▄▀▀▀▀▀▄▒▒▒▒▒▄▄▄▄▄▒▒▒
▒▐░▄░░░▄░▌▒▒▄█▄█▄█▄█▄▒
▒▐░▀▀░▀▀░▌▒▒▒▒▒░░░▒▒▒▒
▒▒▀▄░═░▄▀▒▒▒▒▒▒░░░▒▒▒▒
▒▒▐░▀▄▀░▌▒▒▒▒▒▒░░░▒▒▒▒
)",
R"(
─────────█▄██▄█
█▄█▄█▄█▄█▐█┼██▌█▄█▄█▄█▄█
███┼█████▐████▌█████┼███
█████████▐████▌█████████
)",
R"(
█───▄▀▀▀▀▄─▐█▌▐█▌▐██
█──▐▄▄────▌─█▌▐█─▐▌─
█──▐█▀█─▀─▌─█▌▐█─▐██
█──▐████▄▄▌─▐▌▐▌─▐▌─
███─▀████▀───██──▐██
)",
R"(
─────█─▄▀█──█▀▄─█─────
────▐▌──────────▐▌────
────█▌▀▄──▄▄──▄▀▐█────
───▐██──▀▀──▀▀──██▌───
──▄████▄──▐▌──▄████▄──
)",
R"(
─▄▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▄
█░░░█░░░░░░░░░░▄▄░██░█
█░▀▀█▀▀░▄▀░▄▀░░▀▀░▄▄░█
█░░░▀░░░▄▄▄▄▄░░██░▀▀░█
─▀▄▄▄▄▄▀─────▀▄▄▄▄▄▄▀
)",
R"(
║░█░█░║░█░█░█░║░█░█░║
║░█░█░║░█░█░█░║░█░█░║
║░║░║░║░║░║░║░║░║░║░║
╚═╩═╩═╩═╩═╩═╩═╩═╩═╩═╝
)",
R"(
█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█
█░░╦─╦╔╗╦─╔╗╔╗╔╦╗╔╗░░█
█░░║║║╠─║─║─║║║║║╠─░░█
█░░╚╩╝╚╝╚╝╚╝╚╝╩─╩╚╝░░█
█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█

)",
R"(
───▄██▄─────────────▄▄
──█████▄▄▄▄───────▄▀
────▀██▀▀████▄───▄▀
───▄█▀▄██▄████▄─▄█
▄▄█▀▄▄█─▀████▀██▀
)",
R"(
█▓▒▓█▀██▀█▄░░▄█▀██▀█▓▒▓█
█▓▒░▀▄▄▄▄▄█░░█▄▄▄▄▄▀░▒▓█
█▓▓▒░░░░░▒▓░░▓▒░░░░░▒▓▓█
)",
R"(
──▄──▄────▄▀
───▀▄─█─▄▀▄▄▄
▄██▄████▄██▄▀█▄
─▀▀─█▀█▀▄▀███▀
──▄▄▀─█──▀▄▄
)",
R"(
─▄▀▀▀▄────▄▀█▀▀█▄
▄▀─▀─▀▄▄▀█▄▀─▄▀─▄▀▄
█▄▀█───█─█▄▄▀─▄▀─▄▀▄
──█▄▄▀▀█▄─▀▀▀▀▀▀▀─▄█
─────▄████▀▀▀▀████─▀▄
)",
R"(
╔══╗░░░░╔╦╗░░╔═════╗
║╚═╬════╬╣╠═╗║░▀░▀░║
╠═╗║╔╗╔╗║║║╩╣║╚═══╝║
╚══╩╝╚╝╚╩╩╩═╝╚═════╝
)",
R"(
░░▄█▀▀▀░░░░░░░░▀▀▀█▄
▄███▄▄░░▀▄██▄▀░░▄▄███▄
▀██▄▄▄▄████████▄▄▄▄██▀
░░▄▄▄▄██████████▄▄▄▄
░▐▐▀▐▀░▀██████▀░▀▌▀▌▌
)",
R"(
▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
▒▒▄▄▄▒▒▒█▒▒▒▒▄▒▒▒▒▒▒▒▒
▒█▀█▀█▒█▀█▒▒█▀█▒▄███▄▒
░█▀█▀█░█▀██░█▀█░█▄█▄█░
░█▀█▀█░█▀████▀█░█▄█▄█░
████████▀█████████████
)",
R"(
┊┊┊┊┊┊┊╱▏┊┊┊┊┊┊┊
┊┊┊┊┊┊▕╱┊┊┊┊┊┊┊┊
┊┊┊╱▔▔╲┊╱▔▔╲┊┊┊┊
┊┊▕┈┈┈┈▔┈┈┈╱┊┊┊┊
┊┊▕┈┈┈┈┈┈┈┈╲┊┊┊┊
┊┊┊╲┈┈┈┈┈┈┈╱┊┊┊┊
┊┊┊┊╲▂▂▂▂▂╱┊┊┊┊┊
)",
R"(
▂╱▔▔╲╱▔▔▔▔╲╱▔▔╲▂
╲┈▔╲┊╭╮┈┈╭╮┊╱▔┈╱
┊▔╲╱▏┈╱▔▔╲┈▕╲╱▔┊
┊┊┊┃┈┈▏┃┃▕┈┈┃┊┊┊
┊┊┊▏╲┈╲▂▂╱┈╱▕┊┊┊
)",
R"(
╥━━━━━━━━╭━━╮━━┳
╢╭╮╭━━━━━┫┃▋▋━▅┣
╢┃╰┫┈┈┈┈┈┃┃┈┈╰┫┣
╢╰━┫┈┈┈┈┈╰╯╰┳━╯┣
╢┊┊┃┏┳┳━━┓┏┳┫┊┊┣
╨━━┗┛┗┛━━┗┛┗┛━━┻
)",
R"(
▀▀▀▀█▀▀▀▀
─▄▀█▀▀█──────▄
█▄▄█▄▄██████▀
▀▀█▀▀▀█▀▀
─▀▀▀▀▀▀▀
)",
R"(
──▄▀▀▀▄───────────────
──█───█───────────────
─███████─────────▄▀▀▄─
░██─▀─██░░█▀█▀▀▀▀█░░█░
░███▄███░░▀░▀░░░░░▀▀░░
)",
R"(
░╔╔╩╩╝
▄██▄
░░██████▄░░░░░░▄▄▄▄▄▄█
░░█▀█▀█▀█░░▄░▄████████
░▄▌▄▌▄▌▄▌░▀▄▄▄▄█▄▄▄▄█▄
)",
R"(
░▄▀▀▀▀▄░░▄▄
█░░░░░░▀▀░░█░░░░░░▄░▄
█░║░░░░██░████████████ 
█░░░░░░▄▄░░█░░░░░░▀░▀
░▀▄▄▄▄▀░░▀▀
)",
R"(
─────▀▄▀─────▄─────▄
──▄███████▄──▀██▄██▀
▄█████▀█████▄──▄█
███████▀████████▀
─▄▄▄▄▄▄███████▀
)"
};
