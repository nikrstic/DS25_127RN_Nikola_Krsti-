#pragma once
#include "RibicaFactory.h"

#include<thread>
#include<chrono>
#include<memory>
#include<random>
#include "Strategija.h"
#include "Figura.h"
#include "Olovke.h"

class Ribica: public Figura {
public:
	Ribica(int x, int y, int velicina,float brzina ,CPen* boja,unique_ptr<Strategija> strat) :Figura(x, y, velicina, brzina,boja, move(strat)) {
		
	}
	void crtaj(CDC* pDC) const {
		// TODO sredi ovo sa olovke
		CPen* stara_olovka = pDC->SelectObject(this->boja);
		int cx = x.load();
		int cy = y.load();
		pDC->Ellipse(cx - velicina / 2, cy - velicina / 2, cx + velicina / 2, cy + velicina / 2);
		pDC->SelectObject(stara_olovka);
	}
	void pokreni() {
		std::thread([this]() {
			while (true) {
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				this->pomeri();
			}
			}).detach();
	}

private:
	
	

};
