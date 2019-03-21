#pragma once

#include <stdint.h>

typedef struct
{
  uint8_t* buffer; // Pointer to the data buffer
  int width;       // Width of the image
  int height;      // Height of the image
  int stride;      // Number of bytes between two lines
} image2d;

image2d *load_image(const char *filename);
void save_image(const char *filename, image2d *ima);

image2d *create_image(int width, int height);
image2d *clone_image(const image2d* input);
void     destroy_image(image2d* image);


