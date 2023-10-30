#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * GLOBALS
 */
const char FULL = 'V';
const char EMPTY = ' ';
const bool verbose = false;
int rows = 12;         // n
int columns = 25;      // m
int triangle_base = 7; // l
char *screen;

int ceil(const float num) {
  if (num == (float)(int)num)
    return (int)num;
  return (int)num + 1;
}

void initialize() {
  if (verbose)
    printf("Please provide <rows> <columns> <triangle_base>\n");

  scanf("%d %d %d", &rows, &columns, &triangle_base);
}

void print_screen() {
  if (verbose)
    printf("\n\n\nScreen:\n");
  printf("%s", screen);
}

int screen_index(const int row, const int col) {
  if (row >= rows)
    printf("%d is not a valid row\n", row);
  if (col > columns)
    printf("%d is not a valid column\n", col);

  return (columns + 1) * row + col;
}

void write(const int row, const int col, const char ch) {
  screen[screen_index(row, col)] = ch;
}

void write_line(const int row, const int col, const int length) {
  for (int i = 0; i < length; i++) {
    write(row, col + i, FULL);
  }
}

int screen_size() {
  // TODO: can +1 be removed ?
  return screen_index(rows - 1, columns) + 1;
}

int triangle_height() { return ceil(((float)triangle_base) / 2); }

int row_by_offset(const int offset) { return triangle_height() * offset; }

void initialize_screen() {
  screen = malloc(sizeof(char) * screen_size());
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < columns; col++)
      write(row, col, EMPTY);

    write(row, columns, '\n');
  }

  // print_screen();
}

void test_screen_index() {
  printf("screen_index(0, 0): %d\n", screen_index(0, 0));
  printf("screen_index(1, 0): %d\n", screen_index(1, 0));
  printf("screen_index(1, 1): %d\n", screen_index(1, 1));
  printf("screen_index(1, 5): %d\n", screen_index(1, 5));
  printf("screen_index(2, 7): %d\n", screen_index(2, 7));
}

void draw_top_left(const int offset) {
  for (int i = 0; i < triangle_height(); i++) {
    write_line(row_by_offset(offset) + i, 0, triangle_height() - i);
  }
}

void draw_top_right(const int offset) {
  for (int i = 0; i < triangle_height(); i++) {
    write_line(row_by_offset(offset) + i, (columns - triangle_height()) + i,
               triangle_height() - i);
  }
}

void draw_triangle(const int row_offset, const int top_left_col,
                   const bool reverse) {
  if (!(reverse)) {
    for (int i = 0; i < triangle_height(); i++) {
      write_line(row_by_offset(row_offset) + i, top_left_col + i,
                 triangle_base - i * 2);
    }

    return;
  }

  for (int i = 0; i < triangle_height(); i++) {
    write_line(row_by_offset(row_offset) + i,
               top_left_col + (triangle_height() - 1 - i), 1 + i * 2);
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

void draw_everything() {
  initialize_screen();

  if (verbose) print_current_config();

  for (int j = 0; j < max_triangles_in_vertical(); j++) {
    if (j % 2 == 0) {
      draw_top_left(j);

      for (int i = 0; i < max_triangles_in_horizontal() - 2; i++) {
        const int first_triangle_offset = triangle_height() + 1;
        draw_triangle(j, first_triangle_offset + (triangle_base + 1) * i,
                      false);
      }

      draw_top_right(j);
    } else {
      for (int i = 0; i < max_triangles_in_horizontal() - 1; i++) {
        draw_triangle(j, 1 + (triangle_base + 1) * i, true);
      }
    }
  }

  print_screen();
}

// /*
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
//*/

int main(void) {
//  initialize();
//  draw_everything();

//  test_screen_index();
//  test_max_triangles_in_vertical();
//  test_max_triangles_in_horizontal();
  test_known_configurations();

  return 0;
}