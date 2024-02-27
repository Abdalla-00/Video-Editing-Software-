all: main

main: main.cc TestControl.o TestView.o Editor.o VideoRepo.o VideoArray.o Video.o SceneArray.o Scene.o Date.o
	g++ -o main main.cc TestControl.o TestView.o Editor.o VideoRepo.o VideoArray.o Video.o SceneArray.o Scene.o Date.o

TestControl.o: TestControl.cc TestControl.h
	g++ -c TestControl.cc

TestView.o: TestView.cc TestView.h
	g++ -c TestView.cc

Editor.o: Editor.cc Editor.h
	g++ -c Editor.cc

VideoRepo.o: VideoRepo.cc VideoRepo.h
	g++ -c VideoRepo.cc

VideoArray.o: VideoArray.cc VideoArray.h
	g++ -c VideoArray.cc

Video.o: Video.cc Video.h
	g++ -c Video.cc

SceneArray.o: SceneArray.cc SceneArray.h
	g++ -c SceneArray.cc

Scene.o: Scene.cc Scene.h
	g++ -c Scene.cc

Date.o: Date.cc Date.h
	g++ -c Date.cc

clean:
	rm -f test *.o