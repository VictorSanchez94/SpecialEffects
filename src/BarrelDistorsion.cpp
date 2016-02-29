#include<opencv2/opencv.hpp>
#include"BarrelDistorsion.h"
using namespace std;
using namespace cv;

/* Metodo que implementa el efecto de distorsion de barril y de
 * distorsion de cojin. Dependiendo del parametro k se acentua
 * uno u otro. */
void barrelDistorsion(int camera, double k) {
	VideoCapture capture;
	capture.open(camera);

	capture.set(CV_CAP_PROP_FRAME_WIDTH, 600);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 400);

	double Cx, Cy;

	Mat cameraFeed, output;
	bool end = false;
	char key = 0;
	while(!end){
		capture.read(cameraFeed);
		imshow("Real Image", cameraFeed);

		Cx = cameraFeed.cols / 2;
		Cy = cameraFeed.rows / 2;

		output = barrelDistorsionAux(cameraFeed, Cx, Cy, k, k);
		imshow("Distorsion", output);

		key = cv::waitKey(1);
		switch (key){
			case 27:
				//exit(0);
				destroyAllWindows();
				end = true;
				break;
			case 109:			//m -> mas distorsion
				k = k + 0.00001;
				break;
			case 108:			//l -> menos distorsion
				k = k - 0.00001;
				break;
		}
	}

}

Mat barrelDistorsionAux(Mat img, double Cx, double Cy, double kx, double ky) {
    Mat mapx, mapy;
    mapx.create( img.size(), CV_32FC1 );
    mapy.create( img.size(), CV_32FC1 );

    int w = img.cols;
    int h = img.rows;

    for (int y = 0; y < h; y++) {
        int ty= y-Cy;
        for (int x = 0; x < w; x++) {
            int tx= x-Cx;
            int rt= tx*tx+ty*ty;

            mapx.at<float>(y,x) = (float)(tx*(1+kx*rt)+Cx);
        }
    }

    for (int y = 0;y < h; y++) {
        int ty= y-Cy;
        for (int x = 0; x < w; x++) {
            int tx= x-Cx;
            int rt= tx*tx+ty*ty;

            mapy.at<float>(y,x) = (float)(ty*(1+ky*rt)+Cy);
        }
    }

    Mat output;
    remap( img, output, mapx, mapy, INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0,0) );

    return output;
}
