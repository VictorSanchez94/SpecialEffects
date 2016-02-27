#include<opencv2/opencv.hpp>
#include"ChangeColor.h"
#include"Poster.h"
#include"BarrelDistorsion.h"

int main() {
	//changeFaceColor('b');
	//Poster(6);
	barrelDistorsion(2*std::pow(10,-5));
}
