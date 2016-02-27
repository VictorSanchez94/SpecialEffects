#include<opencv2/opencv.hpp>
#include"HistogramEqualization.h"

using namespace std;
using namespace cv;

/*Metodo que ecualiza el histograma de cada frame capturado por la
 * camara. Si se pulsa la tecla 'c', la imagen se ecualiza en color
 * y si se pulsa la letra 'b' la imagen se muestra en blanco y
 * negro. */

void histogramEqualization() {
	VideoCapture capture;
	capture.open(1); //0 es la webcam integrada y 1 es la webcam USB

	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH,320);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);

	Mat cameraFeed, output;
	char key = 0;
	bool color = true;
	vector<Mat> channels;

	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop
	while(1){

		//store image to matrix
		capture.read(cameraFeed);
		imshow("REAL", cameraFeed);
		if(color){
			cvtColor(cameraFeed, output, CV_BGR2YCrCb);
			split(output,channels);
			equalizeHist(channels[0], channels[0]);
			merge(channels,output);
			cvtColor(output, output, CV_YCrCb2BGR);
			imshow("Histogram Equalization", output);
		}else{
			cvtColor(cameraFeed, cameraFeed, CV_BGR2GRAY);
			equalizeHist(cameraFeed, output);
			imshow("Histogram Equalization", output);
		}

		key = cv::waitKey(1);
		if(key==27){
			break;
		}else if(key=='c'){
			color = true;
		}else if(key=='b'){
			color = false;
		}
	}
}

