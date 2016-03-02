#include<opencv2/opencv.hpp>
#include"SkinDetector.h"
#include"bocadillo.h"

using namespace std;
using namespace cv;

/*Metodo que selecciona la piel humana con un filtro y la cambia de
 * color. Dependiendo de la tecla que se pulse se cambiara a un color
 * o a otro. */

void bocadillo(int camera) {
	VideoCapture capture;
	capture.open(camera); //0 es la webcam integrada y 1 es la webcam USB

	capture.set(CV_CAP_PROP_FRAME_WIDTH,600);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,400);

	Mat cameraFeed;
	SkinDetector mySkinDetector;
	Mat skinMat, HSVMat, output;

	char key = 0;
	bool end = false;
	while(!end){

		capture.read(cameraFeed);
		imshow("REAL", cameraFeed);

		/*for(int x=0; x < skinMat.rows; x++){
			for(int y=0; y < skinMat.cols; y++){
				if(skinMat.at<uchar>(x,y) == 255){
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
		}*/
		output.copyTo(cameraFeed(cv::Rect(x,y,output.cols, output.rows)));
		imshow("Alien Image", output);

		key = cv::waitKey(1);

		switch (key){
			case 27:
				destroyAllWindows();
				end = true;
				break;
		}
	}
}
