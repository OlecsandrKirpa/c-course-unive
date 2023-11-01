#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * GLOBALS
 */
const char FULL = 'V';
const char EMPTY = '*';
const bool verbose = false;
int rows = 12;         // n
int columns = 25;      // m
int triangle_base = 7; // l
char *screen;
bool screen_inintialized = false;

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

bool valid_row(const int row) { return row < rows; }

bool valid_col(const int col) { return col <= columns; }

int screen_index(const int row, const int col) {
  if (!valid_row(row) && verbose)
    printf("%d is not a valid row\n", row);
  if (!valid_col(col) && verbose)
    printf("%d is not a valid column\n", col);

  return (columns + 1) * row + col;
}

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

  if (screen_inintialized && screen[screen_index(row, col)] == '\n'){
    if (verbose) printf("Cannot write where first there was a <newline>\n");

    can_write = false;
  }

//  if (ch == '\n') printf("Writing newline to %d\n", col);

  return can_write;
}

void write(const int row, const int col, const char ch) {
  if (!(can_write(row, col, ch))) return;

  screen[screen_index(row, col)] = ch;
}

void write_line(const int row, const int col, const int length) {
  for (int i = 0; i < length; i++) {
    write(row, col + i, FULL);
  }
}

int screen_size() {
  return screen_index(rows - 1, columns);
}

int triangle_height() { return ceil(((float)triangle_base) / 2); }

int row_by_offset(const int offset) { return triangle_height() * offset; }

void initialize_screen() {
  screen = malloc(sizeof(char) * screen_size());
  screen_inintialized = true;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < columns; col++)
      write(row, col, EMPTY);

    write(row, columns, '\n');
  }
}

void draw_top_left(const int offset) {
  for (int i = 0; i < triangle_height(); i++) {
    write_line(row_by_offset(offset) + i, 0, triangle_height() - i);
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

  print_screen();

  screen_inintialized = false;
}

int main(void) {
    initialize();
    draw_everything();

  return 0;
}