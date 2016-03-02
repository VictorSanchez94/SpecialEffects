#include<opencv2/opencv.hpp>
#include"Contrast.h"
using namespace std;
using namespace cv;

/*Metodo que incrementa el contraste de cada frame capturado
 * por la webcam. Dependiendo del parametro alpha habra mas
 * o menos contraste. */
void contrast(int camera, double alpha, bool automatic) {
	VideoCapture capture;
	capture.open(camera); //0 es la webcam integrada y 1 es la webcam USB

	capture.set(CV_CAP_PROP_FRAME_WIDTH,600);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,400);

	Mat cameraFeed, output;

	char key = 0;
	bool end = false;
	String s;
	while(!end){
		capture.read(cameraFeed);
		imshow("Real", cameraFeed);
		output = cameraFeed;

		if(automatic){
			double num = sum(cameraFeed)[0];
			num = num/(cameraFeed.cols*cameraFeed.rows);
			if(num>200){
				alpha = 0.001;
				s = "Por arriba";
			}else if(num<50){
				s = "Por abajo";
				alpha = 2;
			}else{
				s = "Por ninguno";
				alpha = 1;
			}

		}else{
			alpha = 1;
		}

		for(int x=0; x < cameraFeed.rows; x++){
			for(int y=0; y < cameraFeed.cols; y++){
				Vec3b p = output.at<Vec3b>(x,y);
				p[0] = saturate_cast<uchar>(p[0]*alpha);
				p[1] = saturate_cast<uchar>(p[1]*alpha);
				p[2] = saturate_cast<uchar>(p[2]*alpha);
				output.at<Vec3b>(x,y) = p;
			}
		}

		imshow(s, output);

		key = cv::waitKey(1);
		switch (key){
			case 27:
				destroyAllWindows();
				end = true;
				break;
			case 109:			//m -> mas contraste
				alpha = alpha + 0.5;
				break;
			case 108:			//l -> menos contraste
				alpha = alpha - 0.5;
				break;
		}
	}
}
