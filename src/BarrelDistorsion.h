#ifndef __BARRELDISTORSION_H__
#define __BARRELDISTORSION_H__

#include<opencv2/opencv.hpp>

using namespace cv;

void barrelDistorsion(double k);

Mat barrelDistorsionAux(Mat img, double Cx,double Cy,double kx,double ky);

#endif
