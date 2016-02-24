#include<opencv2/opencv.hpp>
#include"SkinDetector.h"
#include"ChangeColor.h"

using namespace std;
using namespace cv;

void changeFaceColor(char color) {
	VideoCapture capture;
	//open capture object at location zero (default location for webcam)

	capture.open(0);

	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);

	Mat cameraFeed;

	SkinDetector mySkinDetector;

	Mat skinMat, HSVMat, output;

	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop
	char key = 0;
	while(1){

		//store image to matrix
		capture.read(cameraFeed);
		imshow("REAL", cameraFeed);

		//show the current image
		//imshow("Original Image",cameraFeed);

		skinMat= mySkinDetector.getSkin(cameraFeed);

		imshow("Skin Image",skinMat);

		cvtColor(cameraFeed,HSVMat,COLOR_BGR2HSV_FULL);
		//imshow("HSV", HSVMat);



		for(int x=0; x < skinMat.rows; x++){
			for(int y=0; y < skinMat.cols; y++){
				if(skinMat.at<uchar>(x,y) == 255){
					//Point3_<uchar>* p = cameraFeed.ptr<Point3_<uchar> >(x,y);
					Vec3b &p = HSVMat.at<Vec3b>(x,y);
					if(color == 'b'){
						p[0]=160;
						p[1] = p[1]+100;
					}else if(color == 'g'){
						p[0] = 80;
						p[1] = p[1]+100;
					}else if(color == 'r'){
						p[0] = 0;
						p[1] = p[1]+100;
					}else if(color == 'm'){
						p[0] = 200;
						p[1] = p[1]+100;
					}else if(color == 'c'){
						p[0] = 120;
						p[1] = p[1]+100;
					}else if(color == 'y'){
						p[0] = 40;
						p[1] = p[1]+100;
					}
				}
			}
		}
		cvtColor(HSVMat,output,COLOR_HSV2BGR_FULL);
		imshow("Alien Image", output);

		key = cv::waitKey(1);

		switch (key){
			case 114:
				color = 'r';
				break;
			case 103:
				color = 'g';
				break;
			case 98:
				color = 'b';
				break;
			case 99:
				color = 'c';
				break;
			case 109:
				color = 'm';
				break;
			case 121:
				color = 'y';
				break;
			case 27:
				exit(0);
		}
	}
}
