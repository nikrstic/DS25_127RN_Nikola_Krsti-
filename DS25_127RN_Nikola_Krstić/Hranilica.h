#pragma once
#include "Figura.h"
#include "Olovke.h"
#include "Strategija.h"
#include<memory>
#include "pch.h"
#include<thread>
#include "PaketHrane.h"

class Hranilica : public Figura {
	
private:
	static int  const velicina = 30;
	static int const brzina = 10;
	bool zaustavi = false;
	
	static Hranilica* instanca;
	bool pokrenuta = false;
	std::thread nit;
	Hranilica(const Hranilica&) = delete;
	Hranilica& operator=(const Hranilica&) = delete;

	Hranilica(int x, int y) :Figura(x, y, velicina, brzina, &Olovke::crna_cetkica, std::make_unique<StrategijaMiruj>()) {
		static std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<> distrib(0, 1);
		int br = distrib(gen);

		if (br == 0)
			this->strat = std::make_unique<StrategijaLevo>();
		else
			this->strat = std::make_unique<StrategijaDesno>();
	}
public:
	vector<unique_ptr<PaketHrane>> paketi;
	static int getVelicina() {
		return velicina;
	}
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
	static void unistiHranilicu() {
		if (instanca) {
			instanca->zaustavi = true;
			instanca->pokrenuta = false;
			if (instanca->nit.joinable())
				instanca->nit.join();
			delete instanca;
			instanca = nullptr;
		}
	}
	void crtaj(CDC* pDC) const{
		pDC->FillRect(CRect(x - 15, y - 15, x + 15, y + 15), this->boja);
	}
	void promeniPoz(int x, int y) {
		this->x= x;
		this->y= y;
	}
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	void obrisiNit() {
		zaustavi = true;
		if (nit.joinable()) nit.join();
		pokrenuta = false;
	}

	void dodajPaketHrane(int x, int y) {
		paketi.push_back(std::make_unique<PaketHrane>(x, y));

	}
	void pokreni(CView* view) {
		if (pokrenuta) return;
		pokrenuta = true;

		nit =std::thread([this, view]() {
			auto pocetak = std::chrono::steady_clock::now();
		
			while (!zaustavi) {
				auto vremeSad = std::chrono::steady_clock::now();
				auto proteklo = std::chrono::duration_cast<std::chrono::seconds>(vremeSad - pocetak);
				if (proteklo.count() >= 3) {
					pocetak = vremeSad;
					this->dodajPaketHrane(x.load(), y.load());
				}
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
			});
	}




};