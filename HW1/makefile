CC=g++ -std=c++14 -pthread

CFLAGS1 = `pkg-config --libs opencv4`
CFLAGS2 = `pkg-config --cflags opencv4`

clip_video: clip_video.cpp
	$(CC) clip_video.cpp -o clip_video $(CFLAGS1) $(CFLAGS2) 