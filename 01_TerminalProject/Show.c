#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>

#define DX 3
#define BUFSIZE 1000
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

void draw_lines(WINDOW *win, int win_lines, int win_cols, char** lines, int index_line, int index_char) {
    werase(win);
    wmove(win, 1, 0);
    win_cols = MAX(win_cols - 6, 0);
    while (win_lines > 0 && lines[index_line] != NULL) {
        int len_line = (int)strlen(lines[index_line]) - 1;
        if (index_char < len_line) {
            char* cur_line = &lines[index_line][index_char];
            wprintw(win, " %4d: %.*s\n", index_line + 1, MIN(win_cols, len_line - index_char), cur_line);
        } else {
            wprintw(win, " %4d:\n", index_line + 1);
        }
        --win_lines;
        ++index_line;
    }
    box(win, 0, 0);
    wrefresh(win);
}

void draw_window(const char* filename, int num_lines, int max_line, char** lines) {
    WINDOW *win;
    int c = 0;
    int cur_begin_line = 0;
    int cur_begin_char = 0;
    
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    printw("File title: %s\nlines: %d\n", filename, num_lines);
    refresh();
    
    int win_lines = LINES - 2*DX - 2;
    int win_cols = COLS - 2*DX - 2;
    win = newwin(win_lines + 2, win_cols + 2, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    draw_lines(win, win_lines, win_cols, lines, cur_begin_line, cur_begin_char);
    while ((c = wgetch(win)) != 27) {
        if (c == 258 && cur_begin_line < num_lines) { // KEY_DOWN
            ++cur_begin_line;
        }
        if (c == 259 && cur_begin_line > 0) { // KEY_UP
            --cur_begin_line;
        }
        if (c == 260 && cur_begin_char > 0) { // KEY_LEFT
            --cur_begin_char;
        }
        if (c == 261 && cur_begin_char < max_line) { // KEY_RIGHT
            ++cur_begin_char;
        }
        if (c == 338 && cur_begin_line < num_lines) { // KEY_NPAGE
            cur_begin_line = MIN(cur_begin_line + win_lines, num_lines);
        }
        if (c == 339 && cur_begin_line > 0) { // KEY_PPAGE
            cur_begin_line = MAX(cur_begin_line - win_lines, 0);
        }

        draw_lines(win, win_lines, win_cols, lines, cur_begin_line, cur_begin_char);
    }
    endwin();
}

char** read_lines(FILE* file) {
    char **lines = NULL;
    size_t size_line = 0;
    size_t chars_read;
    size_t size_buf = BUFSIZE;
    char* buf = (char*) malloc((BUFSIZE - 1) * sizeof(char));
    while ((chars_read = getline(&buf, &size_buf, file)) != -1) {
        if (chars_read > 0 && buf[chars_read - 1] == '\n') {
            buf[chars_read - 1] = '\0';
        }
        ++size_line;
        lines = (char**) realloc(lines, size_line * sizeof(char *));
        lines[size_line - 1] = malloc((chars_read + 1) * sizeof(char));
        strcpy(lines[size_line - 1], buf);
    }
    ++size_line;
    lines = (char**) realloc(lines, size_line * sizeof(char *));
    lines[size_line - 1] = NULL;
    fclose(file);
    free(buf);
    return lines;
}

void free_lines(char **lines) {
    int index_line = 0;
    while (lines[index_line] != NULL) {
        free(lines[index_line]);
        ++index_line;
    }
    free(lines);
}

int main(int argc, char* argv[]) {
    // Check args and open file
    if (argc < 2) {
        fprintf(stderr, "No file name!\n");
        return 1;
    }
    char *filename = argv[1];
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "File cannot open!\n");
        return false;
    }

    // Read from file
    char **lines = read_lines(file);
    int num_lines = 0;
    int max_line = 0;
    while (lines[num_lines] != NULL) {
        max_line = MAX(max_line, strlen(lines[num_lines]) - 1);
        ++num_lines;
    }

    // Output window
    draw_window(filename, num_lines, max_line, lines);

    // free memory from lines
    free_lines(lines);

    return 0;
} 
