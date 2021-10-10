#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


using namespace cv;
using namespace std;

int clip(string file_path,string output_path){
    Mat frame;
    string name = "";
    VideoCapture cap(file_path);
    string input = file_path;
    string dir_path = output_path;

    int frame_counter = 0,video_counter = 0;
    auto time_now = chrono::system_clock::now();
    time_t convert_time = chrono::system_clock::to_time_t(time_now);

    stringstream date;
    date << put_time(localtime(&convert_time),"%Y-%m-%d");
    
    dir_path += date.str();
    struct stat st={0};
    if(stat(dir_path.c_str(),&st) == -1){
        mkdir(dir_path.c_str() ,0700);
        cout << "mkdir : "<<dir_path<<endl;
    }


    if(!cap.isOpened()){
        cout <<"ERROR! Unable to open camera"<<endl;
        return -1;
        
    }
    else{
        if(input !="0")
            cout<<"Video total # of frames: "<<cap.get(CAP_PROP_FRAME_COUNT)<<endl;
        cout<<"FPS: "<<cap.get(CAP_PROP_FPS)<<endl;
        cout<<"Resolution: "<<cap.get(CAP_PROP_FRAME_WIDTH)<<"x"<<cap.get(CAP_PROP_FRAME_HEIGHT)<<endl;
    }

    while(1){
        name = "/output_" + to_string(video_counter) + ".avi";
        VideoWriter writer(dir_path + name,
                            VideoWriter::fourcc('H','2','6','4'),
                            30,
                            Size(cap.get(CAP_PROP_FRAME_WIDTH),cap.get(CAP_PROP_FRAME_HEIGHT))
        );
        while(1){
            cap.read(frame);
            if(frame.empty()){
                cout <<"ERROR! Blank frame grabbed"<<endl;
                cap.release();
                writer.release();
                break;
            }
            else{
                if(frame_counter == 300){
                    frame_counter=0;
                    cout << "complete video " << video_counter << endl;
                    video_counter++;
                    break;
                }    
                else{
                    writer.write(frame);
                }
                frame_counter++;
            }

            //if((strcmp(argv[2], "--dont_show") != 0)){
            //    imshow("Image",frame);
            //    waitKey(1);           
            //}

        }
        writer.release();

        if(!cap.isOpened())
            break;
    }
    cap.release();
    return 0;
}

int main(int argc, char* argv[]){
    if ((argc != 3)){
        cout << "./clip_video <file_path> <output_path>" << endl;
        //cout<< argc<<argv[1]<<argv[2];
        return 1;
    }
    string input = argv[1];
    string dir_path = argv[2];
    //string dir_path = "/home/eslab/Documents/msHsiao/homework_opencv/HW1/";
    clip(input,dir_path);


    return 0;
}