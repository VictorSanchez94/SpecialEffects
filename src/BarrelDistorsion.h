#ifndef __BARRELDISTORSION_H__
#define __BARRELDISTORSION_H__

#include<opencv2/opencv.hpp>

void barrelDistorsion(double Cx,double Cy,double kx,double ky);

IplImage* barrelDistorsionAux(IplImage* img, double Cx,double Cy,double kx,double ky);

#endif
