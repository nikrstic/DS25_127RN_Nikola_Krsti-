
#pragma once

#include <memory>
#include <thread>
#include <chrono>
#include <random>
#include "Strategija.h"
#include "Figura.h"
#include "Olovke.h"
#include "Ribica.h"


class Ribica;
namespace RibicaFactory {
	static int generisi_broj(int a, int b) {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(a, b);
		return dist(gen);
	}
	
	static unique_ptr<Ribica> napravi_ribicu(int x, int y) {
		int velicina = generisi_broj(5, 10);
		int brojBoje = generisi_broj(1, 3);
		//crvena, tamno plava, zelena
		float brzina = velicina / 2.0;
		CPen* boja;
		switch (brojBoje) {
		case 1:
			boja = &Olovke::crvena_olovka;
			break;
		case 2:
			boja = &Olovke::tamnoPlava_olovka;
			break;
		case 3:
			boja = &Olovke::zelena_olovka;
			break;
		default:
			boja = &Olovke::zelena_olovka;
		}
		return std::make_unique<Ribica>(x, y, velicina, brzina, boja, std::make_unique<StrategijaHaoticno>());
	}
};