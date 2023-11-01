#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * GLOBALS
 */
const char FULL = 'V';
const char EMPTY = '*';
const bool verbose =
    false;             // Enable this to see warnings, errors and more logs.
int rows = 12;         // n
int columns = 25;      // m
int triangle_base = 7; // l
bool screen_initialized = false;
/**
 * Variable screen is the most important variable here.
 * In this array of chars, we will store our entire screen.
 */
char *screen;

int ceil(const float num) {
  if (num == (float)(int)num)
    return (int)num;
  return (int)num + 1;
}

/**
 * Ask user the three params.
 */
void initialize() {
  if (verbose)
    printf("Please provide <rows> <columns> <triangle_base>\n");

  scanf("%d %d %d", &rows, &columns, &triangle_base);
}

/**
 * Print current `screen` value.
 */
void draw_screen() {
  if (verbose)
    printf("\n\n\nScreen:\n");
  printf("%s", screen);
}

bool valid_row(const int row) { return row < rows; }

bool valid_col(const int col) { return col <= columns; }

/**
 * Our `screen` variable is a string,
 * but we want to refer to it as a field with height and width.
 * this function will return the index of the string you need to access
 * if you want to read or write given coordinates.
 */
int screen_index(const int row, const int col) {
  if (!valid_row(row) && verbose)
    printf("%d is not a valid row\n", row);
  if (!valid_col(col) && verbose)
    printf("%d is not a valid column\n", col);

  return (columns + 1) * row + col;
}

/**
 * Deciding whether we can write in given coordinates.
 * Since our screen has a fixed height and length,
 * you cannot write any coordinate you wish to.
 *
 * This function is very important because there will be many
 * uncompleted triangles in our draws. This function will
 * prevent from drawing over a \n character or on the wrong line.
 */
bool can_write(const int row, const int col, const int ch) {
  bool can_write = true;

  if (!valid_row(row)) {
    if (verbose)
      printf("unable to write to row %d\n", row);
    can_write = false;
  }

  if (!valid_col(col)) {
    if (verbose)
      printf("unable to write to col %d\n", col);
    can_write = false;
  }

  if (screen_initialized && screen[screen_index(row, col)] == '\n') {
    if (verbose)
      printf("Cannot write where first there was a <newline>\n");

    can_write = false;
  }

  //  if (ch == '\n') printf("Writing newline to %d\n", col);

  return can_write;
}

/**
 * Write a char at specific coordinates.
 */
void write(const int row, const int col, const char ch) {
  if (!(can_write(row, col, ch)))
    return;

  screen[screen_index(row, col)] = ch;
}

/**
 * Write a horizontal line starting
 * from a specific point with given length.
 */
void write_line(const int row, const int col, const int length) {
  for (int i = 0; i < length; i++) {
    write(row, col + i, FULL);
  }
}

/**
 * How big has to be our string `screen`?
 */
int screen_size() { return screen_index(rows - 1, columns); }

int triangle_height() { return ceil(((float)triangle_base) / 2); }

int row_by_offset(const int offset) { return triangle_height() * offset; }

/**
 * Initialize our string `screen` with chars that rappresent empty cell
 * and new line characters.
 */
void initialize_screen() {
  screen = malloc(sizeof(char) * screen_size());
  screen_initialized = true;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < columns; col++)
      write(row, col, EMPTY);

    write(row, columns, '\n');
  }

  if (verbose)
    draw_screen();
}

/**
 * Drawing the first top-left triangle.
 * the function will draw all the triangles of that type given the offset.
 * The offset is just the line of triangles you want to write to.
 * The first time it will be called with offset = 0; then with offset = 2,
 * 4, 6...
 */
void draw_top_left(const int offset) {
  for (int i = 0; i < triangle_height(); i++) {
    write_line(row_by_offset(offset) + i, 0, triangle_height() - i);
  }
}

/**
 * This function will draw a common triangle given the size,
 * which is stored in `triangle_base` global variable.
 */
void draw_triangle(const int row_offset, const int top_left_col,
                   const bool reverse) {
  if (reverse) {
    for (int i = 0; i < triangle_height(); i++) {
      write_line(row_by_offset(row_offset) + i,
                 top_left_col + (triangle_height() - 1 - i), 1 + i * 2);
    }

    // Guard clause instead of hard-to-read if-else.
    return;
  }

  for (int i = 0; i < triangle_height(); i++) {
    write_line(row_by_offset(row_offset) + i, top_left_col + i,
               triangle_base - i * 2);
  }
}

/**
 * How many triangles can fit in the given screen?
 * Counting first and last one as full.
 */
int max_triangles_in_horizontal() {
  int result = 2;
  int space_left = columns - triangle_height() * 2;
  while (space_left > triangle_base) {
    result++;
    space_left -= triangle_base;
    space_left -= 1; // Space
  }

  return result;
}

int max_triangles_in_vertical() {
  int result = 1;
  int space_remaining = rows;
  while (space_remaining > triangle_height()) {
    result++;
    space_remaining -= triangle_height();
  }

  return result;
}

void print_current_config() {
  printf("rows = %d | columns = %d | triangle_base = %d\n", rows, columns,
         triangle_base);
}

/*
 * This is the heart of the engine that draws everything.
 * It will iterate the max number of vertical rows we can draw with the given
 * size, and will populate each row with triangles, reversed or not.
 */
void draw_everything() {
  // Initializing screen with empty characters and new lines.
  initialize_screen();

  if (verbose)
    print_current_config();

  for (int j = 0; j < max_triangles_in_vertical(); j++) {
    if (j % 2 == 0) {
      /*
       * Even rows: the non-reverse rows. (0, 2, 4, 6, ...)
       * Before start, draw the top-left triangle.
       * Then we draw how many possible triangles.
       */

      draw_top_left(j);

      for (int i = 0; i < max_triangles_in_horizontal(); i++) {
        const int first_triangle_offset = triangle_height() + 1;
        draw_triangle(j, first_triangle_offset + (triangle_base + 1) * i,
                      false);
      }
    } else {
      for (int i = 0; i < max_triangles_in_horizontal(); i++) {
        draw_triangle(j, 1 + (triangle_base + 1) * i, true);
      }
    }
  }

  draw_screen();

  // This is for testing purposes.
  screen_initialized = false;
}

/*
 * TESTS: skip this part if you care only about the final working version.
 * This part of the code was used in development to test that
 * each piece works fine alone.
 */

/*
void test_max_triangles_in_horizontal() {
 // Saving for later original values
 int old_columns = columns;
 int old_rows = rows;
 int old_base = triangle_base;

 int expected;

 // Case 1: 12 25 7
 rows = 12;
 columns = 25;
 triangle_base = 7;
 expected = 4;
 if (max_triangles_in_horizontal() != expected)
   printf("max_triangles_in_horizontal: %d | rows: %d | columns: %d | "
          "triangle_base: %d\n",
          max_triangles_in_horizontal(), rows, columns, triangle_base);

 // Case 2: 6 13 5
 rows = 6;
 columns = 13;
 triangle_base = 5;
 expected = 3;
 if (max_triangles_in_horizontal() != expected)
   printf("max_triangles_in_horizontal: %d | rows: %d | columns: %d | "
          "triangle_base: %d\n",
          max_triangles_in_horizontal(), rows, columns, triangle_base);

 // Case 2: 5 31 9
 rows = 5;
 columns = 31;
 triangle_base = 9;
 expected = 4;
 if (max_triangles_in_horizontal() != expected)
   printf("max_triangles_in_horizontal: %d | rows: %d | columns: %d | "
          "triangle_base: %d\n",
          max_triangles_in_horizontal(), rows, columns, triangle_base);

 // Restoring original values after tests
 triangle_base = old_base;
 rows = old_rows;
 columns = old_columns;
}

void test_max_triangles_in_vertical() {
 // Saving for later original values
 int old_columns = columns;
 int old_rows = rows;
 int old_base = triangle_base;

 int expected;

 // Case 1: 12 25 7
 rows = 12;
 columns = 25;
 triangle_base = 7;
 expected = 3;
 if (max_triangles_in_vertical() != expected)
   printf("max_triangles_in_vertical: %d | rows: %d | columns: %d | "
          "triangle_base: %d\n",
          max_triangles_in_vertical(), rows, columns, triangle_base);

 // Case 2: 6 13 5
 rows = 6;
 columns = 13;
 triangle_base = 5;
 expected = 2;
 if (max_triangles_in_vertical() != expected)
   printf("max_triangles_in_vertical: %d | rows: %d | columns: %d | "
          "triangle_base: %d\n",
          max_triangles_in_vertical(), rows, columns, triangle_base);

 // Case 3: 5 31 9
 rows = 5;
 columns = 31;
 triangle_base = 9;
 expected = 1;
 if (max_triangles_in_vertical() != expected)
   printf("max_triangles_in_vertical: %d | rows: %d | columns: %d | "
          "triangle_base: %d\n",
          max_triangles_in_vertical(), rows, columns, triangle_base);
}

void test_known_configurations() {
 // Case 12 25 7
 rows = 12;
 columns = 25;
 triangle_base = 7;
 print_current_config();
 draw_everything();

 printf("\n\n");
 // Case 6 13 5
 rows = 6;
 columns = 13;
 triangle_base = 5;
 print_current_config();
 draw_everything();

 printf("\n\n");
 // Case 5 31 9
 rows = 5;
 columns = 31;
 triangle_base = 9;
 print_current_config();
 draw_everything();

 printf("\n\n");
 // Case 60 67 19
 rows = 60;
 columns = 67;
 triangle_base = 19;
 print_current_config();
 draw_everything();

 printf("\n\n");
 // Case 32 46 7
 rows = 32;
 columns = 46;
 triangle_base = 7;
 print_current_config();
 draw_everything();

 printf("\n\n");
 // Case 25 37 9
 rows = 25;
 columns = 37;
 triangle_base = 9;
 print_current_config();
 draw_everything();
}

void test_screen_index() {
 printf("screen_index(0, 0): %d\n", screen_index(0, 0));
 printf("screen_index(1, 0): %d\n", screen_index(1, 0));
 printf("screen_index(1, 1): %d\n", screen_index(1, 1));
 printf("screen_index(1, 5): %d\n", screen_index(1, 5));
 printf("screen_index(2, 7): %d\n", screen_index(2, 7));
}
//*/

int main(void) {
  initialize();
  draw_everything();

  //  test_screen_index();
  //  test_max_triangles_in_vertical();
  //  test_max_triangles_in_horizontal();
  //  test_known_configurations();

  return 0;
}