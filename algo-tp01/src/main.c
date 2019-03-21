#include <stdlib.h>
#include <stdio.h>
#include "image.h"
#include "closing.h"


int main(int argc, char** argv)
{
  if (argc != 4)
  {
    fprintf(stderr, "Usage: %s input.png N output.png\n", argv[0]);
    return EXIT_FAILURE;
  }

  int N = atoi(argv[2]);
  if (! (N > 0 && N % 2 == 1))
  {
    fprintf(stderr, "N doit être positif et impair (reçu N=%d)\n", N);
    return EXIT_FAILURE;
  }

  image2d* input = load_image(argv[1]);
  if (input == NULL)
  {
    fprintf(stderr, "Error while loading file %s.\n", argv[1]);
    return EXIT_FAILURE;
  }

  image2d* output = closing_1(input, N);
  compute_residu(input, output);

  save_image(argv[3], output);
  destroy_image(output);
  destroy_image(input);


  return EXIT_SUCCESS;
}
