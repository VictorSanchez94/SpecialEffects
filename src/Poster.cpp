#include<opencv2/opencv.hpp>
#include"Poster.h"
using namespace std;
using namespace cv;

void Poster(int numLevels) {
	const int ARRAY_SIZE = 256;
	int levels[numLevels];

	/*if (numLevels != 1){
		for (int i = 0; i < 256; i++){
			levels[i] = 255 * (numLevels*i / 256) / (numLevels-1);
		}
	}*/

	/*int jump = 240 / numLevels;

	for(int i = 0; i < numLevels; i++) {
		levels[i] = jump*i;
	}*/

	VideoCapture capture;
	//open capture object at location zero (default location for webcam)

	capture.open(0);

	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);

	Mat cameraFeed;

	char key = 0;

	while(1){

		//store image to matrix
		capture.read(cameraFeed);

		//cvtColor(cameraFeed, HSVMat, COLOR_BGR2HSV_FULL);

		for(int x=0; x < cameraFeed.rows; x++){
			for(int y=0; y < cameraFeed.cols; y++){
				Point3_<uchar>* p = cameraFeed.ptr<Point3_<uchar> >(x,y);
				//Vec3b &p = HSVMat.at<Vec3b>(x,y);

				/*p->z = levels[p->z];
				p->y = levels[p->y];
				p->x = levels[p->x];*/

				p->x = (numLevels*p->x)/255;
				p->y = (numLevels*p->y)/255;
				p->z = (numLevels*p->z)/255;

			}
		}

		//cvtColor(HSVMat, output, COLOR_HSV2BGR_FULL);

		imshow("Poster Image", cameraFeed);

		key = cv::waitKey(1);
		if(key == 27){
			break;
		}
	}

}
