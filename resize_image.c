#include <stdio.h>
#include <stdlib.h>

typedef struct image {
  int w;
  int h;
  int c;
  float *data;
} image;

image create_image(int w, int h, int c) {
  image new;
  new.h = h;
  new.w = w;
  new.c = c;
  new.data = (float *)calloc(w * h * c, sizeof(float));

  return new;
}

static float get_pixel(image m, int x, int y, int c) {
  assert(x < m.w);
  assert(y < m.h);
  assert(c < m.c);

  return m.data[m.c * (y * m.w) + m.c * x + c];
}

static void set_pixel(image m, int x, int y, int c, float val) {
  if (x < 0 || y < 0 || c < 0 || x >= m.w || y >= m.h || c >= m.c) return;
  assert(x < m.w && y < m.h && c < m.c);

  m.data[m.c * (y * m.w) + m.c * x + c] = val;
}

image resize_image(image im, int w, int h) {
  int dst_x = 0, dst_y = 0;
  float src_x = 0, src_y = 0;
  int x = 0, y = 0;
  float u = 0, v = 0;
  int c = 0;

  image img;
  img = create_image(w, h, im.c);

  for (dst_x = 0; dst_x < w; dst_x++) {
    for (dst_y = 0; dst_y < h; dst_y++) {
      src_x = dst_x * ((float)(im.w) / w);
      src_y = dst_y * ((float)(im.h) / h);

      x = (int)src_x;
      y = (int)src_y;

      u = src_x - x;
      v = src_y - y;

      if (u > 0.5 && x < im.w - 1) x = x + 1;
      if (v > 0.5 && y < im.h - 1) y = y + 1;

      for (c = 0; c < img.c; c++) {
        set_pixel(img, dst_x, dst_y, c, get_pixel(im, x, y, c));
      }
    }
  }

  return img;
}
