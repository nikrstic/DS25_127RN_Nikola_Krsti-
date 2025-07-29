#include "pch.h"
#include "PaketHrane.h"
#include "Olovke.h"



int PaketHrane::velicina = 15;

void PaketHrane::crtaj(CDC* pDC) const {
    pDC->FillRect(
        CRect(x.load() - velicina / 2, y.load() - velicina / 2,
            x.load() + velicina / 2, y.load() + velicina / 2),
        &Olovke::crna_cetkica
    );
}
