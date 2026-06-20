#include<opencv4/opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;

struct ColorRange{
    Scalar lower;
    Scalar upper;
    string name;
};

int main(){
    VideoCapture cam("/dev/v4l/by-id/usb-Chicony_Electronics_Co._Ltd._Integrated_Camera_0001-video-index0");

    if(!cam.isOpened()){
        cout << "Error: Tidak dapat mengakses kamera!" << endl;
        return -1;
    }
    vector<ColorRange>colors={
        {{0, 150, 50}, {5, 255, 255}, "MERAH"},
        {{20, 100, 50}, {35, 255, 255}, "KUNING"},
        {{40, 100, 50}, {80, 255, 255}, "HIJAU"},
        {{95, 100, 50}, {135, 255, 255}, "BIRU"}
    };

    Mat frame, hsv;
    while(true){
        cam >> frame;
        if(frame.empty()){
            cout << "Error: Frame kosong!" << endl;
            break;
        }
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        for (const auto& color : colors){
            Mat mask;
            inRange(hsv, color.lower, color.upper, mask);
            vector<vector<Point>> contours;
            findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
            for(const auto& contour : contours){
                double area = contourArea(contour);
                if(area > 1000){
                    Rect boundRect = boundingRect(contour);
                    rectangle(frame, boundRect, Scalar(0, 0, 0), 2);
                    putText(frame, color.name, 
                               Point(boundRect.x, boundRect.y - 10),
                               FONT_HERSHEY_SIMPLEX, 0.7, 
                               Scalar(0, 0, 0), 2);
                }
            }
        }
        imshow("Color Detection", frame);
        if(waitKey(1) == 27){
            break;
        }
    }
    cam.release();
    destroyAllWindows();
    return 0;
}




