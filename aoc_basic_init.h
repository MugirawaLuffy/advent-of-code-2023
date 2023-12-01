
#pragma once
#include <stdbool.h>
#define MAX_TOKENS = 200

#if defined(__unix__) || defined(__APPLE__) /* __unix__ is usually defined by  \
                 compilers targeting Unix systems */
#define OS_UNIX
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#elif defined(_WIN32) || defined(WIN32)

#define OS_WINDOWS
#include <malloc.h>
#include <stdio.h>
#include <tchar.h>
#define DIV 1048576

#endif

#define AOC_NO_ERROR 0

#define AOC_CHECK(x)                                                           \
  do {                                                                         \
    int retval = (x);                                                          \
    if (retval != AOC_NO_ERROR) {                                              \
      fprintf(stderr, "Runtime error: %s returned %d at %s:%d", #x, retval,    \
              __FILE__, __LINE__);                                             \
      return;                                                                  \
    }                                                                          \
  } while (0)

#define AOC_CHECK_AND_DO(x, y)                                                 \
  do {                                                                         \
    int retval = (x);                                                          \
    if (retval != AOC_NO_ERROR) {                                              \
      fprintf(stderr, "Runtime error: %s returned %d at %s:%d", #x, retval,    \
              __FILE__, __LINE__);                                             \
      y;                                                                       \
    }                                                                          \
  } while (0)

// Unsigned int types.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// Signed int types.
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

// Floating point types
typedef float f32;
typedef double f64;

/** @brief planned for interfacing WASM and TS, might be redundant*/
typedef struct range {
  u64 offset;
  u64 size;
} range;

// compiler independent static assertions.
#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

// Ansi color codes
#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

typedef struct {
  i64 fileLength;
  char *buffer;
} AOC_InputFile;

typedef struct {
  i32 lineLength;
  char *buffer;
} AOC_SingleLine;

typedef struct {
  i32 number_of_lines;
  AOC_SingleLine *lines;
} AOC_LinesCollection;

i32 aoc_file_by_name(const char *file_name, AOC_InputFile *out_file);

int aoc_split_string(const char *input_string, const char *delimiter,
                     AOC_LinesCollection *output);
int aoc_split_file_by_lines(AOC_InputFile *input, AOC_LinesCollection *output);

void aoc_free_lines(AOC_LinesCollection *output);

bool aoc_char_is_digit(char c);

int aoc_parse_int_from_char(char c);

int aoc_parse_int_from_string(char *str);
