#pragma once
#include<vector>
#include<memory>
#include "Ribica.h"
#include "Hranilica.h"


class Akvarijum :public Figura {
private:
	// moderniji pristup singletona
	bool initialized;

	Akvarijum(): initialized(false) {}
	Akvarijum(const Akvarijum&) = delete;
	Akvarijum& operator=(const Akvarijum&) = delete;

public:
	// unique jer su nezavisni da vise delvova koda koristi ribicu isli bi sa shared
	// mozda shared nije los zbog onog brojanja koje sprovodi nevidljivi entitet
	std::vector<std::unique_ptr<Ribica>> ribice;
	Hranilica* hranilica = nullptr;
	
	static Akvarijum& instance() {
		static Akvarijum instanca;
		if (!instanca.initialized)
			instanca.initialise();
		return instanca;
	}
	void dodaj(unique_ptr<Ribica> ribica) {
		ribice.push_back(move(ribica));
	}
	void postaviHranilicu(Hranilica *hranilica) {
		this->hranilica = hranilica;

	}

	void crtaj(CDC* pDC) const {
		CRect rc;
		pDC->GetWindow()->GetClientRect(&rc);
		pDC->FillRect(&rc, &Olovke::plava_cetkica);

		for (const auto& r : ribice) {
			r->crtaj(pDC);
		}
		if (hranilica->getInstance()) {
			hranilica->getInstance()->crtaj(pDC);
			
		}
		for (const auto& paket : hranilica->getInstance()->paketi) {
			paket->crtaj(pDC);
		}
	}
	int getX()const {
		return this->x;
	}
	void initialise() {


		this->initialized = true;
	}

};