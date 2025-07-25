#include<memory>
#include<atomic>

class Figura {
protected:
	std::unique_ptr<Strategija> strat;
	CBrush* boja;
	std::atomic<int> x, y;
	int velicina;
public:
	virtual void crtaj(CDC* pDC) const = 0;
	Figura();
	Figura(int x, int y, int velicina, std::unique_ptr<Strategija> strat) : x(x), y(y), velicina(velicina), strat(strat) {};
	void pomeri() {
		if (strat)
			strat->pomeri(x, y, korak);
	}
	
};