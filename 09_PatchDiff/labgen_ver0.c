#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LAB_SIZE 6

char* create_template() {
    int board_size = 2 * LAB_SIZE + 1;
    char* lab = malloc(board_size * board_size * sizeof(char));
    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            if ((i & 1) && (j & 1)) {
                lab[i * board_size + j] = '.';
            } else {
                lab[i * board_size + j] = '#';
            }
        }
    }
    return lab;
}

void print_lab(char* lab) {
    int board_size = 2 * LAB_SIZE + 1;
    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            putchar(lab[i * board_size + j]);
        }
        putchar('\n');
    }
}

struct Point {
    int x;
    int y;
};

int check_direction(bool** is_visit, struct Point room) {
    int num_dir = 0;
    if (!is_visit[room.x - 1][room.y]) {
        ++num_dir;
    }
    if (!is_visit[room.x][room.y - 1]) {
        ++num_dir;
    }
    if (!is_visit[room.x + 1][room.y]) {
        ++num_dir;
    }
    if (!is_visit[room.x][room.y + 1]) {
        ++num_dir;
    }
    return num_dir;
}

struct Point add_room(bool** is_visit, struct Point room, int index) {
    int num_dir = 0;
    if (!is_visit[room.x - 1][room.y]) {
        if (num_dir == index) {
            --room.x;
            return room;
        }
        ++num_dir;
    }
    if (!is_visit[room.x][room.y - 1]) {
        if (num_dir == index) {
            --room.y;
            return room;
        }
        ++num_dir;
    }
    if (!is_visit[room.x + 1][room.y]) {
        if (num_dir == index) {
            ++room.x;
            return room;
        }
        ++num_dir;
    }
    if (!is_visit[room.x][room.y + 1]) {
        if (num_dir == index) {
            ++room.y;
            return room;
        }
        ++num_dir;
    }
}

void generate_path(char* lab) {
    int board_size = 2 * LAB_SIZE + 1;
    int num_rooms = LAB_SIZE + 2;
    bool** is_visit = malloc(num_rooms * sizeof(bool*));
    for (int i = 0; i < num_rooms; ++i) {
        is_visit[i] = malloc(num_rooms * sizeof(bool));
        if (i == 0 || i == num_rooms - 1) {
            for (int j = 0; j < num_rooms; ++j) {
                is_visit[i][j] = true;
            }
        } else {
            for (int j = 0; j < num_rooms; ++j) {
                is_visit[i][j] = false;
            }
            is_visit[i][0] = true;
            is_visit[i][num_rooms - 1] = true;
        }
    }
    struct Point* queue = malloc(num_rooms * num_rooms * sizeof(struct Point));
    struct Point room;
    room.x = (rand() % LAB_SIZE) + 1;
    room.y = (rand() % LAB_SIZE) + 1;
    is_visit[room.x][room.y] = true;
    queue[0] = room;
    int size_queue = 1;
    
    while (size_queue > 0) {
        int index = rand() % size_queue;
        room = queue[index];
        int num_dir = check_direction(is_visit, room);
        if (num_dir == 0) {
            queue[index] = queue[size_queue - 1];
            --size_queue;
        } else {
            struct Point new_room = add_room(is_visit, room, rand() % num_dir);
            is_visit[new_room.x][new_room.y] = true;
            queue[size_queue] = new_room;
            ++size_queue;

            int offset_x = new_room.x - room.x;
            int offset_y = new_room.y - room.y;
            lab[(2 * room.x - 1 + offset_x) * board_size + (2 * room.y - 1 + offset_y)] = '.';
        }
    }

    for (int i = 0; i < num_rooms; ++i) {
        free(is_visit[i]);
    }
    free(is_visit);
    free(queue);
}

int main(int argc, char* argv[]) {
    char* lab = create_template();
    generate_path(lab);
    print_lab(lab);
    free(lab);
    return 0;
}
