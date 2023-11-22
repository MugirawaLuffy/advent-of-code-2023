#include "../inittypes.h"
#include <stdio.h>

int main(void) {
  u16 year = 2023;
  printf(GREEN "Merry " RED "Christmas" WHITE " %d" YELLOW " !" RESET, year);
}
