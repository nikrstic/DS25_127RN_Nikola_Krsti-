#pragma once
#include<atomic>
#include<math.h>

using namespace std;
class Strategija {
public:
	virtual void pomeri(atomic<int> &x, atomic<int> &y, int &korak) = 0;
	virtual ~Strategija();
};

// usmereno levo desno haoticno

class StrategijaLevo : public Strategija {

	void pomeri(atomic<int> &x, atomic<int>& y, int korak) {
		x -= korak;
	}


};

class StrategijaDesno : public Strategija {
public:
	void pomeri(atomic<int> x, atomic<int> y, int korak) {
		x += korak;
	}
};
class StrategijaUsmereno : public Strategija {
public:
	int xx, yy;
	
	StrategijaUsmereno(int xx, int yy) : xx(xx), yy(yy) {}
	void pomeri(int x, int y, int korak) {

		int xv = xx - x;
		int yv = yy - y;
		float norma = sqrt(xv * xv + yv * yv);
		x += (int) xv / norma * korak;
		y += (int)yv / norma * korak;

	}
};