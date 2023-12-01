#include "aoc_basic_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

i32 aoc_file_by_name(const char *file_name, AOC_InputFile *out_file) {
  FILE *f = NULL;

#ifdef OS_WINDOWS
  fopen_s(&f, file_name, "rb;
#elif defined OS_UNIX
  f = fopen(file_name, "rb");
  printf("Unix subsystem recognized\n");
#else
  printf("No operating system recognized\n");
#endif

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
/*
int aoc_split_string(const char *input_string, const char *delimiter,
                     AOC_LinesCollection *output) {

  char **tokens = NULL;
  char *token;
  int count = 0;

  char *input_copy = strdup(input_string);
  if (input_copy == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return -1;
  }

  token = strtok(input_copy, "\n");
  while (token != NULL) {
    tokens = (char **)realloc(tokens, (count + 1) * sizeof(char *));
    if (tokens == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      return -2;
    }

    tokens[count] = strdup(token);
    if (tokens[count] == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      return -3;
    }

    count++;
    token = strtok(NULL, "\n");
  }

  free(input_copy);

  output->number_of_lines = count;
  output->lines = tokens;
  return 0;
}
*/
int aoc_split_file_by_lines(AOC_InputFile *input, AOC_LinesCollection *output) {
  aoc_split_string(input->buffer, "\n", output);

  return 0;
}

void aoc_free_lines(AOC_LinesCollection *output) {
  if (output->lines != NULL) {
    for (int i = 0; i < output->number_of_lines; ++i) {
      free(output->lines[i].buffer);
    }
    free(output->lines);
  }
}

int aoc_split_string(const char *input_string, const char *delimiter,
                     AOC_LinesCollection *output) {
  char *input_copy = strdup(input_string);
  if (input_copy == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return -1;
  }

  char *token = strtok(input_copy, delimiter);
  i32 count = 0;

  AOC_SingleLine *lines = NULL;

  while (token != NULL) {
    lines =
        (AOC_SingleLine *)realloc(lines, (count + 1) * sizeof(AOC_SingleLine));
    if (lines == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      return -2;
    }

    lines[count].lineLength = strlen(token);
    lines[count].buffer = strdup(token);
    if (lines[count].buffer == NULL) {
      fprintf(stderr, "Memory allocation failed.\n");
      return -3;
    }

    count++;
    token = strtok(NULL, delimiter);
  }

  free(input_copy);

  output->number_of_lines = count;
  output->lines = lines;

  return 0;
}

bool aoc_char_is_digit(char c) { return (c >= '0' && c <= '9'); }

int aoc_parse_int_from_char(char c) { return c - '0'; }

void aoc_str_append_char(char *s, char c) {
  int len = strlen(s);
  s[len] = c;
  s[len + 1] = '\0';
}

char *aoc_substring(char *str, int start_pos, int end_pos) {
  char *buffer = malloc(sizeof(char) * (end_pos - start_pos));
  for (int i = start_pos; i < end_pos; i++) {
    buffer[i - start_pos] = str[i];
  }

  return buffer;
}

bool aoc_str_starts_with(char *str, char *expected_start, i16 str_len,
                         i16 pattern_len) {
  if (str_len < pattern_len) {
    // printf(RED "Error: pattern bigger than string (%d, %d)\n" RESET,
    //        pattern_len, str_len);
    return false;
  }

  for (int i = 0; i < pattern_len; i++) {
    if (str[i] != expected_start[i])
      return false;
  }
  return true;
}
