#include "../aoc_basic_init.h"
#include <math.h>
#include <stdio.h>
#include <sys/_types/_null.h>

i32 main(void) {
  u16 year = 2023;
  printf(GREEN "Merry " RED "Christmas" WHITE " %d" YELLOW " !" RESET
               "\nDay1: Trebuchet!\n",
         year);

  i32 sum = 0;

  // safely read file and split it by line
  AOC_InputFile input_file;
  AOC_LinesCollection input_lines;
  AOC_CHECK_AND_DO(aoc_file_by_name("../real_puzzle_input.txt", &input_file),
                   return -1);
  AOC_CHECK_AND_DO(aoc_split_file_by_lines(&input_file, &input_lines),
                   return -1);
  printf(GREEN "Red file and split it into %d lines.\n" RESET,
         input_lines.number_of_lines);

  // now, get numberset of each line
  for (i32 i = 0; i < input_lines.number_of_lines; i++) {
    AOC_SingleLine line = input_lines.lines[i];

    printf("Working on line %d: %s (%d chars): ", i, line.buffer,
           line.lineLength);

    // Loop over each character
    i8 first = -1;
    i8 last = 0;
    for (i32 ci = 0; ci < line.lineLength; ci++) {
      char active_char = line.buffer[ci];

      // is active character a digit?
      if (aoc_char_is_digit(active_char)) {
        // last gets always reassigned, so that it always holds the latest
        // i.e. last value
        last = aoc_parse_int_from_char(active_char);

        // first only gets reassigned when the first letter is encountered
        if (first == -1) {
          first = aoc_parse_int_from_char(active_char);
        }
      }
    }
    i16 num = 10 * first + last;
    printf(YELLOW "Got %d\n" RESET, num);
    sum += num;
  }

  printf(GREEN "Final sum was: %d\n" RESET, sum);

  // clean up
  printf("Finished execution, cleaning up!" RESET);
  aoc_free_lines(&input_lines);
}
