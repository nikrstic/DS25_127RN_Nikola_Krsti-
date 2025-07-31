#pragma once

#include<vector>

class Akvarijum;
class Ribica;

class Visitor {
public:
	virtual	vector<float> visit(Akvarijum& akvarijum) = 0;
	virtual int visit(Hranilica& hranilica) = 0;
	virtual ~Visitor() = default;
};