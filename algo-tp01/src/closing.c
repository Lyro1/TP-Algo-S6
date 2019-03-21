#include "closing.h"
#include <assert.h>
 #define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

image2d* closing_1(const image2d* input, int N)
{
    int N_ = N/2;   
    image2d *out = create_image(input->width, input->height);
    uint8_t *ilineptr = input->buffer;
    uint8_t *olineptr = out->buffer;

    for (int y = 0; y < input->height; y++)
    {
        for (int x = 0; x < input->width; x++)
        {
            uint8_t m = 0;
            for (int p = -N_; p <= N_; p++)
            {
                for (int q = x - N_; q <= x + N_; q++)
                    m = max(m, ilineptr[p * input->width + q]);
                olineptr[x] = m;
            }
        }
        ilineptr += input->width;
        olineptr += input->width;
    }
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
