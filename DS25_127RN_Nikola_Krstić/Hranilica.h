#pragma once
#include "Figura.h"
#include "Olovke.h"
#include "Strategija.h"
#include<memory>
#include "pch.h"
class Hranilica : public Figura {
	
private:
	static int  const velicina = 30;

	static Hranilica* instanca;

	Hranilica(){}

	Hranilica(const Hranilica&) = delete;
	Hranilica& operator=(const Hranilica&) = delete;

public:
	
	Hranilica* getInstance() {
		
		if (instanca == nullptr)
			instanca = &Hranilica();
		return instanca;
	}

	void crtaj(CDC* pDC) const{
		pDC->FillRect(CRect(x - 15, y - 15, x + 15, y + 15), &Olovke::crna_cetkica);
	}


	void pokreni() {
		while (true) {

			this->pomeri();


		}
	}
	






};