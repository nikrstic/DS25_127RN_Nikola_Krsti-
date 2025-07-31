#include "Hranilica.h"
#include "Akvarijum.h"
#include "Ribica.h"
#include "Visitor.h"
#include<limits.h>

class StatistikaVisitor : public Visitor {
public:
	int visit(Hranilica& hranilica) override {
		if (Hranilica::getInstance())
			return hranilica.broj_paketa;
		return -1;
		
	}
	vector<float> visit(Akvarijum& akvarijum) override {
		vector<float> resenje;
		int broj_ribica = 0;
		int min = INT_MAX;
		int max = -1;
		int sum = 0;
		for (auto&& ribica: akvarijum.ribice )
		{
			int a = ribica.get()->getVelicina();
			a > max ? max = a : max = max;
			a < min ? min = a : min = min;
			sum += a;
			broj_ribica++;
		}
		if (max != -1) {
			resenje.push_back(max);
			resenje.push_back(min);
			resenje.push_back(sum / broj_ribica);
		}
		else {
			resenje.push_back(0);
			resenje.push_back(0);
			resenje.push_back(0);
		}

		return resenje;
	}


};