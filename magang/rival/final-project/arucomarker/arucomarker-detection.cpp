#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<opencv2/aruco.hpp>
using namespace std;
using namespace cv;

int main(){
    VideoCapture cam("http://10.124.28.141:8080/video");    
    if(!cam.isOpened()){
        cout << "Error: Tidak dapat mengakses kamera!" << endl;
        return -1;
    }
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_5X5_1000);    
    Mat frame;
    while(true){
        cam >> frame;
        if(frame.empty()){
            cout << "Error: Frame kosong!" << endl;
            break;
        }
        //Deteksi ArUcoMarker
        vector<int> markerIds;
        vector<vector<Point2f>> markerCorners;
        vector<vector<Point2f>> rejectedCandidates;
        
        aruco::detectMarkers(frame, dictionary, markerCorners, markerIds);
        aruco::drawDetectedMarkers(frame, markerCorners, markerIds);
            
        for(size_t i=0; i<markerIds.size(); i++){
            Point2f center = (markerCorners[i][0] + markerCorners[i][1] + markerCorners[i][2] + markerCorners[i][3]) / 4;
        
            //ID ArUcoMarker & titik pusat
            string text = "ID: " + to_string(markerIds[i]);
            putText(frame, text, Point(center.x - 30, center.y - 20), 
                    FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
            circle(frame, center, 5, Scalar(0, 0, 255), -1);
            cout << "Marker ID: " << markerIds[i] 
                     << " | Center: (" << center.x << ", " << center.y << ")" << endl;
                
            //Kotak ArUcoMarker         
            for(int j=0; j<4; j++){
                    line(frame, markerCorners[i][j], markerCorners[i][(j+1)%4], 
                         Scalar(255, 0, 0), 2);
                }
            }
        imshow("ArUco Marker Detection", frame);
        if(waitKey(1) == 27){
            break;
        }
    }
    cam.release();
    destroyAllWindows();
    return 0;
}