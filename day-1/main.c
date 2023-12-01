#include "../aoc_basic_init.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <sys/_types/_null.h>

int replace_literals_with_digits(AOC_SingleLine *line);
int replace_literals_with_digits1(AOC_SingleLine *line);

i32 main(void) {
  u16 year = 2023;
  printf(GREEN "Merry " RED "Christmas" WHITE " %d" YELLOW " !" RESET
               "\nDay1: Trebuchet!\n",
         year);

  i32 sum = 0;

  // safely read file and split it by line
  AOC_InputFile input_file;
  AOC_LinesCollection input_lines;

  // AOC_CHECK_AND_DO(aoc_file_by_name("../demo-input.txt", &input_file),
  //                 return -1);
  AOC_CHECK_AND_DO(aoc_file_by_name("../real_puzzle_input.txt", &input_file),
                   return -1);

  AOC_CHECK_AND_DO(aoc_split_file_by_lines(&input_file, &input_lines),
                   return -1);
  printf(GREEN "Red file and split it into %d lines.\n" RESET,
         input_lines.number_of_lines);

  // now, get numberset of each line
  for (i32 i = 0; i < input_lines.number_of_lines; i++) {
    AOC_SingleLine line = input_lines.lines[i];

    printf("Working on line %d: %s (%d chars)", i, line.buffer,
           line.lineLength);

    // In part two, also literals should be considered:
    replace_literals_with_digits(&line);
    printf(" -> %s", line.buffer);

    // Loop over each character
    i8 first = -1;
    i8 last = 0;
    for (i32 ci = 0; ci < line.lineLength; ci++) {
      char active_char = line.buffer[ci];

      // last gets always reassigned, so that it always holds the latest
      // i.e. last value
      last = aoc_parse_int_from_char(active_char);

      // first only gets reassigned when the first letter is encountered
      if (first == -1) {
        first = aoc_parse_int_from_char(active_char);
      }
    }
    i16 num = 10 * first + last;
    printf(YELLOW ": Got %d\n" RESET, num);
    sum += num;
  }

  printf(GREEN "Final sum was: %d\n" RESET, sum);

  // clean up
  printf("Finished execution, cleaning up!" RESET);
  aoc_free_lines(&input_lines);
}

int replace_literals_with_digits(AOC_SingleLine *line) {
  char *result = malloc(1);
  i8 len = 0;

  i32 ci = 0; // Use a separate index for iteration
  while (ci < line->lineLength) {
    char current = line->buffer[ci];
    if (aoc_char_is_digit(current)) {
      aoc_str_append_char(result, current);
      len++;
      ci++;
      continue;
    }

    // if is char, try to append a following word
    char *rest_of_line = aoc_substring(line->buffer, ci, line->lineLength);
    i8 str_len = line->lineLength - ci;

    if (aoc_str_starts_with(rest_of_line, "zero", str_len, 4)) {
      aoc_str_append_char(result, '0');
      len++;
    } else if (aoc_str_starts_with(rest_of_line, "one", str_len, 3)) {
      aoc_str_append_char(result, '1');
      len++;
    } else if (aoc_str_starts_with(rest_of_line, "two", str_len, 3)) {
      aoc_str_append_char(result, '2');
      len++;
    } else if (aoc_str_starts_with(rest_of_line, "three", str_len, 4)) {
      aoc_str_append_char(result, '3');
      len++;
    } else if (aoc_str_starts_with(rest_of_line, "four", str_len, 4)) {
      aoc_str_append_char(result, '4');
      len++;
    } else if (aoc_str_starts_with(rest_of_line, "five", str_len, 4)) {
      aoc_str_append_char(result, '5');
      len++;
    } else if (aoc_str_starts_with(rest_of_line, "six", str_len, 3)) {
      aoc_str_append_char(result, '6');
      len++;
    } else if (aoc_str_starts_with(rest_of_line, "seven", str_len, 5)) {
      aoc_str_append_char(result, '7');
      len++;
    } else if (aoc_str_starts_with(rest_of_line, "eight", str_len, 5)) {
      aoc_str_append_char(result, '8');
      len++;
    } else if (aoc_str_starts_with(rest_of_line, "nine", str_len, 4)) {
      aoc_str_append_char(result, '9');
      len++;
    }
    ci++;
  }

  line->lineLength = len;
  line->buffer = result;

  return 0;
}
