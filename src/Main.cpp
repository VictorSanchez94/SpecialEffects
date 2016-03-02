#include<opencv2/opencv.hpp>
#include"ChangeColor.h"
#include"Poster.h"
#include"BarrelDistorsion.h"
#include"Contrast.h"
#include"SaltAndPepper.h"
#include"HistogramEqualization.h"

int main(int argc, char *argv[]) {
	int CAMERA = 0;

	cout << "Elija efecto:" << endl;
	cout << "\t-0: Salir." << endl;
	cout << "\t-1: Efecto alien." << endl;
	cout << "\t-2: Efecto poster." << endl;
	cout << "\t-3: Distorsión de barril." << endl;
	cout << "\t-4: Distorsión de cojín." << endl;
	cout << "\t-5: Aumento del contraste." << endl;
	cout << "\t-6: Ecualización del histograma." << endl;
	cout << "\t-7: Inserción de ruido de 'sal y pimienta'.\n" << endl;
	cout << "ELECCIÓN: ";

	int key;
	cin >> key;
	if(key == 0){
		exit(0);
	}else if(key == 1){
		changeFaceColor(CAMERA, 'g');
	}else if(key == 2){
		Poster(CAMERA, 6);
	}else if(key == 3){
		barrelDistorsion(CAMERA, 0.00001);
	}else if(key == 4){
		barrelDistorsion(CAMERA,-0.000002);
	}else if(key == 5){
		contrast(CAMERA, 3.2);
	}else if(key == 6){
		histogramEqualization(CAMERA);
	}else if(key == 7){
		saltAndPepper(CAMERA, 3);
	}

}
