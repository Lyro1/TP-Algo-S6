#include "image.h"
#include <string.h>
#include <stdlib.h>
#include <png.h>

void save_image(const char *filename, image2d *ima)
{
  png_structp png_ptr =
    png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    return;

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_write_struct(&png_ptr, NULL);
    return;
  }

  FILE* fp = fopen(filename, "wb");
  png_init_io(png_ptr, fp);

  png_set_IHDR(png_ptr, info_ptr,
               ima->width,
               ima->height,
               8,
               PNG_COLOR_TYPE_GRAY,
               PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);

  uint8_t* buffer = ima->buffer;
  png_write_info(png_ptr, info_ptr);
  for (int i = 0; i < ima->height; ++i)
  {
    png_write_row(png_ptr, (png_const_bytep)(buffer));
    buffer += ima->stride;
  }

  png_write_end(png_ptr, info_ptr);
  png_destroy_write_struct(&png_ptr, NULL);
  fclose(fp);
}


image2d* load_image(const char *filename)
{
  FILE* fp = fopen(filename, "rb");
  if (!fp)
    return NULL;

  unsigned char header[8];
  fread(header, 1, 8, fp);

  if (png_sig_cmp(header, 0, 8))
    return NULL;

  png_structp png_ptr =
    png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    return NULL;

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    return NULL;
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);
  png_read_info(png_ptr, info_ptr);

  int width = png_get_image_width(png_ptr, info_ptr);
  int height = png_get_image_height(png_ptr, info_ptr);
  int color_type = png_get_color_type(png_ptr, info_ptr);
  int bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  if (bit_depth != 8 || color_type != PNG_COLOR_TYPE_GRAY)
    return NULL;

  //int number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);

  image2d* ima = create_image(width, height);
  uint8_t* buffer = ima->buffer;
  for (int i = 0; i < height; ++i)
  {
    png_read_row(png_ptr, (png_bytep)(buffer), NULL);
    buffer += ima->stride;
  }

  png_read_end(png_ptr, NULL);
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  fclose(fp);

  return ima;
}

image2d *create_image(int width, int height)
{
  image2d* ima = malloc(sizeof(image2d));
  ima->buffer = malloc(width * height);
  ima->width = width;
  ima->height = height;
  ima->stride = width;
  return ima;
}


void destroy_image(image2d* image)
{
  free(image->buffer);
  free(image);
}


image2d* clone_image(const image2d* f)
{
  image2d* out = create_image(f->width, f->height);
  memcpy(out->buffer, f->buffer, f->width * f->height);
  return out;
}

