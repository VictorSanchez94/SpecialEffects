#include<opencv2/opencv.hpp>
#include"BarrelDistorsion.h"
using namespace std;
using namespace cv;

void barrelDistorsion(int camera, double k) {
	VideoCapture capture;
	//open capture object at location zero (default location for webcam)

	capture.open(camera);

	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	double Cx, Cy;

	Mat cameraFeed, output;

	char key = 0;
	while(1){
		//store image to matrix
		capture.read(cameraFeed);
		imshow("Real Image", cameraFeed);

		Cx = cameraFeed.cols / 2;
		Cy = cameraFeed.rows / 2;

		output = barrelDistorsionAux(cameraFeed, Cx, Cy, k, k);
		imshow("Distorsion", output);

		key = cv::waitKey(1);
		switch (key){

			case 27:
				exit(0);
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

    /*float r;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
        	r = sqrt(pow((x-Cx),2) + pow((y-Cy),2));
            //mapx.at<float>(y,x) = Cx+(x-Cx)*(1+kx*((x-Cx)*(x-Cx)+(y-Cy)*(y-Cy)));
        	mapx.at<float>(y,x) = Cy + (x-Cx) * (1 + kx*pow(r,2));
        	//mapy.at<float>(y,x) = Cx + (y-Cy) * (1 + ky*pow(r,2));
        }
    }
    for (int y = 0;y < h; y++) {
        for (int x = 0; x < w; x++) {
        	//mapy.at<float>(y,x) = Cy+(y-Cy)*(1+ky*((x-Cx)*(x-Cx)+(y-Cy)*(y-Cy)));
        	//mapy.at<float>(y,x) = Cy + (y-Cy) * (1 + ky * pow((y-Cy),2));
        	mapy.at<float>(y,x) = Cx + (y-Cy) * (1 + ky*pow(r,2));
        }
    }*/

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
