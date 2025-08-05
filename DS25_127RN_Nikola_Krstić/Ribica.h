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
	static atomic<bool> pojeden;
	static std::mutex paketiMutex;
	void pokreni(CView* view) {
		if (pokrenuta) return;
		else
			pokrenuta = true;

		std::thread([this, view]() {
			while (true) {
				// ako nema aktivnih paketa hrane vrati se na staro
				if (!Hranilica::paketHraneAktivan && ubrzana) {
					this->strat = make_unique<StrategijaHaoticno>();
					this->ubrzana = false;
					this->brzina = this->brzina * 0.5;
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				// da se ne desi da kad kliknem x nestane ClientRect ribice ga traze i izbace exception
				if (view == nullptr || !::IsWindow(view->GetSafeHwnd()))
					break;
				CRect rc;
				view->GetClientRect(&rc);
				
				// ulazimo ovde ako ima paketa
				if (!Hranilica::paketi.empty() ) {
					if (!ubrzana)
						this->brzina = this->brzina * 2;
					//usmereno ka paketu
					this->strat = make_unique<StrategijaUsmereno>(
						Hranilica::xPaket.load(), Hranilica::yPaket.load());
					this->ubrzana = true;

					int dx = this->x - Hranilica::xPaket;
					int dy = this->y - Hranilica::yPaket;

					bool jaJedem = false;
					
					{
						//zakljucamo ovaj blok i kazemo da je paket pojeden, jednoj ribici dajemo zadatak da jede paket
						
						std::lock_guard<std::mutex> lock(Hranilica::paketiMutex);
						
						if (dx * dx + dy * dy < 100 && !pojeden ) {
							pojeden = true;
							Hranilica::pojediPaketHrane(Hranilica::xPaket, Hranilica::yPaket);
							Hranilica::paketHraneAktivan = false;
							jaJedem = true;
						}
					}

					if (jaJedem) {
						pojeden = false;
						this->strat = make_unique<StrategijaMiruj>();
						this->jela = true;

						auto tmpBoja = this->boja;
						this->boja = &Olovke::crna_cetkica;
						this->velicina += 2;

						std::this_thread::sleep_for(std::chrono::seconds(3));

						this->velicina -= 2;
						this->boja = tmpBoja;
						this->jela = false;
						this->strat = make_unique<StrategijaHaoticno>();

						
					}
				}

			
				this->pomeri();
				if (this->strat->jeHaoticna()) {
					int cx = x.load();
					int cy = y.load();
					if (cx <= 0) x.store(velicina);
					if (cx > rc.Width() - velicina) x.store(rc.Width() - velicina);
					if (cy <= 0) y.store(velicina);
					if (cy > rc.Height() - velicina) y.store(rc.Height() - velicina);
				}
			}
			}).detach();
	}

private:
	
	

};
