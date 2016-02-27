#include<opencv2/opencv.hpp>
#include"Poster.h"
using namespace std;
using namespace cv;

/*Metodo que reduce el numero de colores de cada frame capturado
 * por la webcam creando un efecto de poster. */
void Poster(int numLevels) {
	const int ARRAY_SIZE = 256;
	int levels[numLevels];
	float jump = 255/numLevels;

	VideoCapture capture;
	capture.open(0); //0 es la webcam integrada y 1 es la webcam USB

	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);

	Mat cameraFeed;
	char key = 0;

	while(1){
		capture.read(cameraFeed);

		for(int x=0; x < cameraFeed.rows; x++){
			for(int y=0; y < cameraFeed.cols; y++){
				Point3_<uchar>* p = cameraFeed.ptr<Point3_<uchar> >(x,y);
				int a = p->x/jump;
				int b = p->y/jump;
				int c = p->z/jump;
				p->x = jump*a;
				p->y = jump*b;
				p->z = jump*c;

			}
		}

		imshow("Poster Image", cameraFeed);

		key = cv::waitKey(1);
		if(key == 27){
			break;
		}
	}

}
