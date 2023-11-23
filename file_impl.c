#include "aoc_basic_init.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

i32 aoc_file_by_name(const char *file_name, AOC_InputFile *out_file) {

  FILE *f = NULL;
  fopen_s(&f, file_name, "rb");

  if (f == NULL) {
    return -1;
  }

  fseek(f, 0, SEEK_END);
  out_file->fileLength = ftell(f);
  fseek(f, 0, SEEK_SET);
  out_file->buffer = malloc(out_file->fileLength);

  if (!out_file->buffer) {
    return -2;
  }

  fread(out_file->buffer, 1, out_file->fileLength, f);
  fclose(f);

  return out_file->buffer ? AOC_NO_ERROR : -3;
}
