#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void comic(int camera, String text)
{
	VideoCapture cap;
	CascadeClassifier detector;
	Mat bocadillo = imread("data\\bocadillo2.png",CV_LOAD_IMAGE_COLOR);

	bool end = false;

	if(!detector.load("C:\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml"))
		cout << "No se puede abrir clasificador." << endl;

	if(!cap.open(0))
		cout << "No se puede acceder a la webcam." << endl;

	Mat dest, gray, imagen;
	while(!end)
	{
		cap >> imagen;

		putText(bocadillo, text, cvPoint(80,50),
			FONT_ITALIC, 0.7, cvScalar(0,0,0), 1, CV_AA);

		cvtColor(imagen, gray, CV_BGR2GRAY);
		equalizeHist(gray, dest);

		vector<Rect> rect;
		detector.detectMultiScale(dest, rect, 1.2, 3, 0, Size(60,60));


		for(size_t i = 0; i < rect.size(); i++ ) {

			rectangle(imagen,Point(rect[i].x, rect[i].y),Point(rect[i].x + rect[i].width, rect[i].y + rect[i].height),CV_RGB(0,255,0), 1);
			if(rect[i].x + rect[i].width + 300 < imagen.cols){
				bocadillo.copyTo(imagen.rowRange(rect[i].y, rect[i].y  + 100).colRange(rect[i].x + rect[i].width, rect[i].x + rect[i].width + 300));
			}
		}

		imshow("Inserción de bocadillo", imagen);

		if(waitKey(1) == 27){
			destroyAllWindows();
			end = true;
			break;
		}
	}

}
