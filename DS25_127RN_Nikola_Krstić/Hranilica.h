#pragma once



#include "Olovke.h"
#include "Strategija.h"
#include "Figura.h"
#include "PaketHrane.h"
#include "Visitor.h"

#include<memory>
#include<vector>
#include<thread>


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
		broj_paketa = 0;
		static std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<> distrib(0, 1);
		int br = distrib(gen);
		
		if (br == 0)
			this->strat = std::make_unique<StrategijaLevo>();
		else
			this->strat = std::make_unique<StrategijaDesno>();
	}
	~Hranilica() {
		zaustavi = true;
		if (nit.joinable())
			nit.join();
		
	}

public:
	// dodao sam da bude staticka da se ne brisu paketi hrane kad se budu brisale hranilice
	static std::vector<std::unique_ptr<PaketHrane>> paketi;
	
	int broj_paketa;
	static atomic<bool> paketHraneAktivan;
	static atomic<int> xPaket;
	static atomic<int> yPaket;
	
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
	int accept(Visitor& v) {
		return v.visit(*this);
	}

	void dodajPaketHrane(int x, int y) {
		Hranilica::instanca->broj_paketa += 1;
		Hranilica::paketi.push_back(std::make_unique<PaketHrane>(x, y));
		
		

		// ovde sam stavio da jede redom pakete kako se stvaraju da ne ostane nei nepojeden // ne moze jer onda ih jede redom, ali ceka da se pojavi nova da pojede sledecu u nizu

		Hranilica::xPaket = Hranilica::paketi.at(0).get()->getX();
		Hranilica::yPaket = Hranilica::paketi.at(0).get()->getY();
		
	
		Hranilica::paketHraneAktivan = true;
		/*Hranilica::xPaket = x;
		Hranilica::yPaket = y;*/

	}
	static std::mutex paketiMutex;
	static void pojediPaketHrane(int x, int y) {
		//std::lock_guard<std::mutex> lockPaketi(paketiMutex); 
		
		for (auto it = Hranilica::paketi.begin(); it != Hranilica::paketi.end(); ++it) {
			auto& paket = *it;

			if (paket->getX() == x && paket->getY() == y) {
				//std::lock_guard<std::mutex> lockPaket(paket->hranaMutex); 

				Hranilica::paketHraneAktivan = false;
				Hranilica::paketi.erase(it);
				if (!paketi.empty()) {
					xPaket = paketi.front()->getX();
					yPaket = paketi.front()->getY();
					paketHraneAktivan = true;
				}
				else {
					paketHraneAktivan = false;
				}
				break;
			}
		}
	}
	void pokreni(CView* view) {
		if (pokrenuta) return;
		pokrenuta = true;

		nit =std::thread([this, view]() {
			auto pocetak = std::chrono::steady_clock::now();
		
			while (!zaustavi) {
				auto vremeSad = std::chrono::steady_clock::now();
				auto proteklo = std::chrono::duration_cast<std::chrono::seconds>(vremeSad - pocetak);
				if (proteklo.count() >= 10) {
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