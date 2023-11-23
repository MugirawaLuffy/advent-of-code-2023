#include "../aoc_basic_init.h"
#include <stdio.h>

i32 main(void) {
  i32 status = 0;
  u16 year = 2023;
  printf(GREEN "Merry " RED "Christmas" WHITE " %d" YELLOW " !\n" RESET, year);

  AOC_InputFile input;
  status = aoc_file_by_name("../test.txt", &input);

  if (status < 0) {
    printf(RED "Failed to read input file: code %d\n" RESET, status);
    return -1;
  }

  printf(GREEN "Successfully red text:\n" RESET "%.*s\n", (int)input.fileLength,
         input.buffer);
}
