
#include<opencv2/opencv.hpp>
#include"SaltAndPepper.h"
using namespace std;
using namespace cv;

/*Metodo que crea un efecto de ruido de sal y pimienta.
 * Dependiendo del parametro percent se generara mas o
 * menos ruido. */
void saltAndPepper(int camera, int percent) {

	VideoCapture capture;
	capture.open(camera); //0 es la webcam integrada y 1 es la webcam USB

	capture.set(CV_CAP_PROP_FRAME_WIDTH,600);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,400);

	Mat cameraFeed, output;

	char key = 0;
	bool end = false;
	while(!end){
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
		switch (key){
			case 27:
				destroyAllWindows();
				end = true;
				break;
			case 109:			//m -> mas contraste
				percent = percent + 5;
				break;
			case 108:			//l -> menos contraste
				percent = percent - 5;
				break;
		}
	}
}
