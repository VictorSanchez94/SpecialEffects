
#include<opencv2/opencv.hpp>
#include"SaltAndPepper.h"
using namespace std;
using namespace cv;

/*Metodo que crea un efecto de ruido de sal y pimienta.
 * Dependiendo del parametro percent se generara mas o
 * menos ruido. */
void saltAndPepper(int percent) {

	VideoCapture capture;
	capture.open(1); //0 es la webcam integrada y 1 es la webcam USB

	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH,600);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,400);

	Mat cameraFeed, output;

	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop
	char key = 0;
	while(1){

		//store image to matrix
		capture.read(cameraFeed);
		imshow("Real", cameraFeed);
		output = cameraFeed;

		int numPixels = cameraFeed.rows*cameraFeed.cols;
		for(int i=0; i<numPixels*percent/100; i++){
			int xRandSalt = rand() % cameraFeed.rows;
			int yRandSalt = rand() % cameraFeed.cols;
			int xRandPepper = rand() % cameraFeed.rows;
			int yRandPepper = rand() % cameraFeed.cols;
			Vec3b &p = output.at<Vec3b>(xRandPepper,yRandPepper);
			p[0]=0;
			p[1]=0;
			p[2]=0;
			Vec3b &s = output.at<Vec3b>(xRandSalt,yRandSalt);
			s[0]=255;
			s[1]=255;
			s[2]=255;

		}
		imshow("SaltAndPepper", output);

		key = cv::waitKey(1);
		if(key==27){
			break;
		}
	}
}
