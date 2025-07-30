#pragma once

#include "pch.h"
#include "Strategija.h"
using namespace std;

class Figura {
protected:

	std::unique_ptr<Strategija> strat;
	CBrush* boja;
	std::atomic<int> x, y;
	int velicina;
	std::atomic<int> brzina;
public:
	virtual void crtaj(CDC* pDC) const = 0;
	Figura(){}
	Figura(int x, int y, int velicina,atomic<int> brzina,CBrush* boja ,std::unique_ptr<Strategija> strat) : x(x), y(y), velicina(velicina),brzina(brzina.load()),boja(boja), strat(move(strat)) {};
	void pomeri() {
		if (strat)
			strat->pomeri(x, y, brzina.load());
	}
	
};