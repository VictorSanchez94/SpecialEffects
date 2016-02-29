#include<opencv2/opencv.hpp>
#include"Poster.h"
using namespace std;
using namespace cv;

/*Metodo que reduce el numero de colores de cada frame capturado
 * por la webcam creando un efecto de poster. */
void Poster(int camera, int numLevels) {
	const int ARRAY_SIZE = 256;
	int levels[numLevels];
	float jump = 255/numLevels;

	VideoCapture capture;
	capture.open(camera); //0 es la webcam integrada y 1 es la webcam USB

	capture.set(CV_CAP_PROP_FRAME_WIDTH,600);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,400);

	Mat cameraFeed;
	char key = 0;
	bool end = false;
	while(!end){
		capture.read(cameraFeed);
		imshow("REAL", cameraFeed);

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
		switch (key){
			case 27:
				destroyAllWindows();
				end = true;
				break;
			case 109:			//m -> mas colores
				numLevels++;
				jump = 255/numLevels;
				break;
			case 108:			//l -> menos distorsion
				if(numLevels > 1){
					numLevels--;
					jump = 255/numLevels;
				}
				break;
		}
	}

}
