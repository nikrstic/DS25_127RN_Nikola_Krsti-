#pragma once
#include<vector>
#include<memory>



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
	std::vector<std::unique_ptr<Ribica>> ribice = std::make_unique<Ribica>();
	
	static Akvarijum& instance() {
		static Akvarijum instanca;
		if (!instanca.initialized)
			instanca.initialise();
		return instanca;
	}


	void crtaj(CDC* pDC) const {
		for (Ribica* r : ribice) {
			r->crtaj();
		}
		hranilica->crtaj();
	}
	void initialise() {





		this->initialized = true;
	}

};