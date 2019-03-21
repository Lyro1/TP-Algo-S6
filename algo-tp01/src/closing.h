#pragma once
#include "image.h"

// A implementer
image2d* closing_1(const image2d* input, int N);
image2d* closing_2(const image2d* input, int N);
image2d* closing_3(const image2d* input, int N);



// Calcule le résidu "g - f" et le stocke dans g
// \param f est l'image d'entrée (avant fermeture)
// \param g est l'image traitée (après fermeture)
void compute_residu(const image2d* f, image2d* g);


