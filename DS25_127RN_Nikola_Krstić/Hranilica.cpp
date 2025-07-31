#include "pch.h"
#include<vector>
#include<memory>
#include "PaketHrane.h"
#include "Hranilica.h"


Hranilica* Hranilica::instanca = nullptr;


atomic<bool> Hranilica::paketHraneAktivan = false;
atomic<int> Hranilica::xPaket = -1;
atomic<int> Hranilica::yPaket;

std::vector<std::unique_ptr<PaketHrane>> Hranilica::paketi;

std::mutex Hranilica::paketiMutex;