file included:

	defs.h
	Date.h/.cc
	Scene.h/.cc - Entity object, ontains Scene data (title, Date, content)
	SceneArray.h/.cc - Collection object, data structure for Scenes
	Video.h/.cc - Entity object, contains Video information (title, description), manages Scene collections
	VideoArray.h/.cc - Collection object, data structure for Videos
	VideoRepo.h/.cc - Manages Video collections and provides access, save, delete & play Video features
	Editor.h/.cc - connects to a Videorepo object to save/download current Video, add/remove Scenes from Video, print error messages to std::cout
	TestView.h/.cc - Presents a menu, takes input from the user performing the tests
	TestControl.h/.cc - controls runing of tests on application, interacts with TestView
	main.cc
	Makefile
	README.txt
	

compilation & execution:

    compile:

        open a terminal window from projrct file and enter the command: make 

    excute:

        enter the command: ./main

        user will then be prompted to choose/enter options from 0 - 5
