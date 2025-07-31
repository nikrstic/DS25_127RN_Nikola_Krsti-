#pragma once
#include "RibicaFactory.h"

#include<thread>
#include<chrono>
#include<memory>
#include<random>
#include<mutex>



#include "Strategija.h"
#include "Figura.h"
#include "Olovke.h"
#include "Hranilica.h"



class Ribica: public Figura {
public:
	
	bool jela = false;
	bool ubrzana = false;
	
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
	int getVelicina() {
		return this->velicina;
	}
	static std::mutex paketiMutex;
	void pokreni(CView* view) {
		if (pokrenuta) return;
		else
			pokrenuta = true;

		std::thread([this, view]() {
			while (true) {

				if (!Hranilica::paketHraneAktivan && ubrzana) {
					this->strat = make_unique<StrategijaHaoticno>();
					this->ubrzana = false;
					this->brzina = this->brzina * 0.5;
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				CRect rc;
				view->GetClientRect(&rc);
				if (!Hranilica::paketi.empty()&& Hranilica::paketHraneAktivan) {
					if (!ubrzana)
						this->brzina = this->brzina * 2;
					this->strat = make_unique<StrategijaUsmereno>(Hranilica::xPaket.load(), Hranilica::yPaket.load());
					this->ubrzana = true;

					int dx = this->x - Hranilica::xPaket;
					int dy = this->y - Hranilica::yPaket;
					
					// dodam neki boolean koji proverava jel pojeden paket, ako jeste da ne ulaze

					
					if (dx * dx + dy * dy < 100) {
						//std::lock_guard<std::mutex> lock(Hranilica::paketiMutex);
						if (Hranilica::paketHraneAktivan) {
							this->strat = make_unique<StrategijaMiruj>();
							this->jela = true;
							auto tmpBoja = this->boja;
							this->boja = &Olovke::crna_cetkica;
							this->velicina += 2;

							Hranilica::pojediPaketHrane(Hranilica::xPaket, Hranilica::yPaket);
							//std::lock_guard<std::mutex> unlock(Hranilica::paketiMutex);

							Hranilica::paketHraneAktivan = false;
							std::this_thread::sleep_for(std::chrono::seconds(3));
							this->velicina -= 2;
							this->boja = tmpBoja;
							this->jela = false;
							this->strat = make_unique<StrategijaHaoticno>();
							
						}
					}
				}
				/*else if (!Hranilica::paketHraneAktivan && ubrzana) {
					this->strat = std::make_unique<StrategijaHaoticno>();
					this->ubrzana = false;
					this->brzina = this->brzina * 0.5;
				}*/
				
				this->pomeri();
				if (this->strat == unique_ptr<StrategijaHaoticno>()) {
					if (x < 0) x = 0;
					if (x > rc.Width() - velicina) x = rc.Width() - velicina;
					if (y < 0) y = 0;
					if (y > rc.Height() - velicina) y = rc.Height() - velicina;
				}
			}
			}).detach();
	}

private:
	
	

};
