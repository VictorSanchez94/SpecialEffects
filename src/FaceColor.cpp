#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	CascadeClassifier detector;

	if(!detector.load("/home/victor/opencv-2.4.9/data/haarcascades/haarcascade_frontalface_alt.xml"))
		cout << "No se puede abrir clasificador." << endl;

	if(!cap.open(0))
		cout << "No se puede acceder a la webcam." << endl;

	while(true)
	{
		Mat dest, gray, imagen;

		cap >> imagen;

		cvtColor(imagen, gray, CV_BGR2GRAY);
		equalizeHist(gray, dest);

		vector<Rect> rect;
		detector.detectMultiScale(dest, rect, 1.2, 3, 0, Size(60,60));


		for(size_t i = 0; i < rect.size(); i++ ) {

			rectangle(imagen,Point(rect[i].x, rect[i].y),Point(rect[i].x + rect[i].width, rect[i].y + rect[i].height),CV_RGB(0,255,0), 1);

			for(int y = rect[i].y+1; y < rect[i].y + rect[i].height; y++){
			    for(int x = rect[i].x+1; x < rect[i].x + rect[i].width; x++){

					Point3_<uchar>* p = imagen.ptr<Point3_<uchar> >(y,x);
					cout << (int)p->z << "   ";
					if(p->z *1.05 > 255){
						p->z = 255;
						cout << "SE FUE" << endl;
					}else{
						p->z *= 1.25;
					}
					cout << (int)p->z << endl;
			    }
			}

		}

		imshow("Deteccion de rostros", imagen);

		if(waitKey(1) >= 0) break;
	}

	return 1;
}
