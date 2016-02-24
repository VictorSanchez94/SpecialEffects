#include<opencv2/opencv.hpp>
#include"Poster.h"
using namespace std;
using namespace cv;

void Poster(int numLevels) {
	const int ARRAY_SIZE = 256;
	int levels[numLevels];

	float jump = 255/numLevels;


	/*if (numLevels != 1){
		for (int i = 0; i < 256; i++){
			levels[i] = 255 * (numLevels*i / 256) / (numLevels-1);
		}
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


				int a = p->x/jump;
				int b = p->y/jump;
				int c = p->z/jump;

				p->x = jump*a;
				p->y = jump*b;
				p->z = jump*c;

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
