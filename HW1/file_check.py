import cv2
import numpy as np
import os
import argparse

def str2int(video_path):
    """
    argparse returns and string althout webcam uses int (0, 1 ...)
    Cast to int if needed
    """
    try:
        return int(video_path)
    except ValueError:
        return video_path

def parser():
    parser = argparse.ArgumentParser(description="motion dection")
    parser.add_argument("--input", type=str, default=0,
                        help="file source.")
    return parser.parse_args()

args = parser()
dir_path = str2int(args.input)

#dir_path = "/home/eslab/Documents/msHsiao/homework_opencv/HW1/2021-10-09/"
arr = os.listdir(dir_path)
for file_name in arr:
    if os.path.splitext(file_name)[1] != ".avi" :
        continue
    cap = cv2.VideoCapture(dir_path+file_name)
    print("file name : "+file_name)
    print("Video total # of frames: %d" %cap.get(cv2.CAP_PROP_FRAME_COUNT))
    print("FPS: %f" %cap.get(cv2.CAP_PROP_FPS))
    print("Resolution: %dx%d" %(cap.get(cv2.CAP_PROP_FRAME_WIDTH),cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))
    print("-"*20)
    cap.release()

print("complete")
