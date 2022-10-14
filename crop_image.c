#include <stdio.h>
#include <stdlib.h>

typedef struct image {
  int w;
  int h;
  int c;
  float *data;
} image;


image crop_image(image im, int dx, int dy, int w, int h) {
  image img_crop;

  img_crop.c = im.c;
  img_crop.w = w;
  img_crop.h = h;

  img_crop.data = (float *)calloc(w * h * img_crop.c, sizeof(float));

  int i = 0, j = 0;
  int start = 0, index = 0;

  for (i = dy; i < dy + h; i++) {
    start = (i * im.w + dx) * img_crop.c;
    for (j = start; j < start + w * img_crop.c; j++) {
      if (index > img_crop.c * img_crop.h * img_crop.w)
        printf("Error: Image size\n");
      img_crop.data[index] = im.data[j];
      index++;
    }
  }
  return img_crop;
}
