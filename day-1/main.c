#include "../aoc_basic_init.h"
#include <stdio.h>
#include <stdlib.h>

i32 main(void) {
  u16 year = 2023;
  printf(GREEN "Merry " RED "Christmas" WHITE " %d" YELLOW " !\n" RESET, year);

  // READ FILE AND DO ERROR CHECKING
  AOC_InputFile input;
  AOC_CHECK_AND_DO(aoc_file_by_name("../test.txt", &input), return -1);

  // PRINT FILE TO CONSOLE
  printf(GREEN "Successfully red text:\n" RESET "%.*s\n", (int)input.fileLength,
         input.buffer);
}
