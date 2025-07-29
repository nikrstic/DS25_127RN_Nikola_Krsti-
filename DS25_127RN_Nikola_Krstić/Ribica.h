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
	Ribica(int x, int y, int velicina,float brzina ,CBrush* boja,unique_ptr<Strategija> strat) :Figura(x, y, velicina, brzina,boja, move(strat)) {
		
	}
	bool pokrenuta = false;
	void crtaj(CDC* pDC) const {
		// TODO sredi ovo sa olovke
		CBrush* stara_olovka = pDC->SelectObject(this->boja);
		int cx = x.load();
		int cy = y.load();
		
		pDC->Ellipse(cx - velicina / 2, cy - velicina / 2, cx + velicina / 2, cy + velicina / 2);
		pDC->SelectObject(stara_olovka);
	}
	void pokreni(CView* view) {
		if (pokrenuta) return;
		else
			pokrenuta = true;

		std::thread([this, view]() {
			while (true) {
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				CRect rc;
				view->GetClientRect(&rc);
				
				this->pomeri();
				
				if (x < 0) x = 0;
				if (x > rc.Width() - velicina) x = rc.Width() - velicina;
				if (y < 0) y = 0;
				if (y > rc.Height() - velicina) y = rc.Height() - velicina;
				
			}
			}).detach();
	}

private:
	
	

};
