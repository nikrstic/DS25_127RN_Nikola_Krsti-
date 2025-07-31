#pragma once

#include "Figura.h"
#include "Olovke.h"
#include "Strategija.h"

#include<memory>
#include<mutex>
class Hranilica;

class PaketHrane :public Figura {
public:
	static int velicina;
	
	std::mutex hranaMutex;
	PaketHrane(int x, int y):Figura(x, y,velicina,0, &Olovke::crna_cetkica, std::make_unique<StrategijaMiruj>()){}
	
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}

	void crtaj(CDC* pDC)const;

};