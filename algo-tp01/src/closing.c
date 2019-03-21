#include "closing.h"
#include <assert.h>


// A implementer
image2d* closing_1(const image2d* input, int N)
{
  // Implémentation à fournir
  // Pour l'instant: une simple copie
  return clone_image(input);
}


image2d* closing_2(const image2d* input, int N)
{
  // Implémentation à fournir
  // Pour l'instant: une simple copie
  return clone_image(input);
}

image2d* closing_3(const image2d* input, int N)
{
  // Implémentation à fournir
  // Pour l'instant: une simple copie
  return clone_image(input);
}



// Calcule le résidu "g - f" et le stocke dans g
// \param f est l'image d'entrée (avant fermeture)
// \param g est l'image traitée (après fermeture)
void compute_residu(const image2d* f, image2d* g)
{
  assert(f->width == g->width);
  assert(f->height == g->height);

  int height = f->height;
  int width = f->width;
  int stride = f->stride;

  const uint8_t* fptr = f->buffer;
  uint8_t* gptr = g->buffer;

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
      gptr[x] = gptr[x] - fptr[x];
    gptr += stride;
    fptr += stride;
  }
}
