#pragma once
#include "Figura.h"
#include "Olovke.h"
#include "Strategija.h"
#include<memory>
#include "pch.h"
#include<thread>

class Hranilica : public Figura {
	
private:
	static int  const velicina = 30;
	static int const brzina = 10;

	static Hranilica* instanca;
	bool pokrenuta = false;

	Hranilica(const Hranilica&) = delete;
	Hranilica& operator=(const Hranilica&) = delete;

	Hranilica(int x, int y) :Figura(x, y, velicina, brzina, &Olovke::crvena_olovka, std::make_unique<StrategijaMiruj>()) {
		static std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<> distrib(0, 1);
		int br = distrib(gen);

		if (br == 0)
			this->strat = std::make_unique<StrategijaLevo>();
		else
			this->strat = std::make_unique<StrategijaDesno>();
	}
public:
	
	static Hranilica* getInstance() {
		return instanca;
	}
	static Hranilica* getInstance(int x, int y) {

		if (!instanca)
			instanca = new Hranilica(x, y);
		/*else {
			instanca.get()->x = x;
			instanca.get()->y = y;
		}*/
		return instanca;
	}
	/*bool initialized() {
		instanca ? true : false;
	}*/

	void crtaj(CDC* pDC) const{
		pDC->FillRect(CRect(x - 15, y - 15, x + 15, y + 15), &Olovke::crna_cetkica);
	}
	void promeniPoz(int x, int y) {
		this->x= x;
		this->y= y;
	}

	void pokreni(CView* view) {
		if (pokrenuta) return;
		pokrenuta = true;

		std::thread([this, view]() {
			while (true) {
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				this->pomeri();
				CRect rc;
				view->GetClientRect(&rc); 
				int granicaX = rc.Width();
				int cx = x.load();
				
				if (cx <= 0) {
					this->strat = std::make_unique<StrategijaDesno>();
				}
				else if (cx >= granicaX) {
					this->strat = std::make_unique<StrategijaLevo>();
				}
			}
			}).detach();
	}




};