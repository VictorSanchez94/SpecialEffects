#include<opencv2/opencv.hpp>
#include"HistogramEqualization.h"

using namespace std;
using namespace cv;

/*Metodo que ecualiza el histograma de cada frame capturado por la
 * camara. Si se pulsa la tecla 'c', la imagen se ecualiza en color
 * y si se pulsa la letra 'b' la imagen se muestra en blanco y
 * negro. */

void histogramEqualization(int camera) {
	VideoCapture capture;
	capture.open(camera); //0 es la webcam integrada y 1 es la webcam USB

	capture.set(CV_CAP_PROP_FRAME_WIDTH,600);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,400);

	Mat cameraFeed, output;
	char key = 0;
	bool color = true;
	vector<Mat> channels;
	bool end = false;
	while(!end){
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
			destroyAllWindows();
			end = true;
			break;
		}else if(key=='c'){
			color = true;
		}else if(key=='b'){
			color = false;
		}
	}
}

