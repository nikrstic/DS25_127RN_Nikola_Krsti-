#pragma once
#include<atomic>
#include<math.h>
#include<random>

using namespace std;


class Strategija {
public:
	virtual void pomeri(atomic<int> &x, atomic<int> &y, atomic<int> korak) = 0;
	
};

// usmereno levo desno haoticno


class StrategijaLevo : public Strategija {
public:
    void pomeri(std::atomic<int>& x, std::atomic<int>& y, atomic<int> korak) override {
        x -= korak;
    }
};

class StrategijaDesno : public Strategija {
public:
    void pomeri(std::atomic<int>& x, std::atomic<int>& y, atomic<int> korak) override {
        x += korak;
    }
};

class StrategijaUsmereno : public Strategija {
public:
    int xx, yy;
    StrategijaUsmereno(int xx, int yy) : xx(xx), yy(yy) {}

    void pomeri(std::atomic<int>& x, std::atomic<int>& y, atomic<int> korak) override {
        int xv = xx - x.load();
        int yv = yy - y.load();
        float norma = sqrt(xv * xv + yv * yv);
        x += static_cast<int>(xv / norma * korak);
        y += static_cast<int>(yv / norma * korak);
    }
};

class StrategijaHaoticno : public Strategija {
public:
    void pomeri(std::atomic<int>& x, std::atomic<int>& y, atomic<int>korak) override {
        float ug = rand() / static_cast<float>(RAND_MAX);
        ug *= atan(1) * 4 * 2;
        x += static_cast<int>(korak * cos(ug));
        y -= static_cast<int>(korak * sin(ug));
    }
};

class StrategijaMiruj : public Strategija {
public:
    void pomeri(std::atomic<int>& x, std::atomic<int>& y, atomic<int> korak) override {}
};
