#pragma once
#include<vector>
#include<memory>
#include "Ribica.h"
#include "Hranilica.h"

class Akvarijum {
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
	std::unique_ptr<Hranilica> hranilica;
	
	static Akvarijum& instance() {
		static Akvarijum instanca;
		if (!instanca.initialized)
			instanca.initialise();
		return instanca;
	}
	void dodaj(unique_ptr<Ribica> ribica) {
		ribice.push_back(move(ribica));
	}

	void crtaj(CDC* pDC) const {
		CRect rc;
		pDC->GetWindow()->GetClientRect(&rc);
		pDC->FillRect(&rc, &Olovke::plava_cetkica);

		for (const auto& r : ribice) {
			r->crtaj(pDC);
		}
		hranilica->crtaj(pDC);
	}
	void initialise() {





		this->initialized = true;
	}

};