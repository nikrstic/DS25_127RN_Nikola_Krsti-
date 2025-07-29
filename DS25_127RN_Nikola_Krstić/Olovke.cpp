#include "pch.h"
#include "Olovke.h"
CPen Olovke::crvena_olovka(PS_SOLID, 5, RGB(255,0,0));
CPen Olovke::tamnoPlava_olovka(PS_SOLID, 5, RGB(0, 0, 139));
CPen Olovke::zelena_olovka(PS_SOLID, 5, RGB(0, 255, 0));



CBrush Olovke::crvena_cetkica(RGB(255, 0, 0));
CBrush Olovke::tamnoPlava_cetkica(RGB(0, 0, 139));
CBrush Olovke::zelena_cetkica(RGB(0, 255, 0));

CBrush Olovke::crna_cetkica(RGB(0,0,0));
CBrush Olovke::plava_cetkica(RGB(200, 224, 252));
