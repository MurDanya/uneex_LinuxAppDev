#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <regex.h>

#define BUF_SIZE 1024
#define BAGS_SIZE 10

struct buffer {
    char *data;
    size_t capacity;
    size_t len;
};

void append(struct buffer* buf, char *str, size_t str_len)
{
    for (int i = 0; i < str_len; ++i) {
        if (buf->len + 1 >= buf->capacity) {
            buf->capacity *= 2;
            buf->data = realloc(buf->data, buf->capacity);
        }
        buf->data[buf->len] = str[i];
        ++buf->len;
        buf->data[buf->len] = '\0';
    }
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "Error. Use 3 arguments:\n%s regexp substitution string\n", argv[0]);
        return 1;
    }
    char *regexp = argv[1];
    char *substitution = argv[2];
    char *string = argv[3];

    regex_t regex;
    int error = regcomp(&regex, regexp, REG_EXTENDED);
    if (error) {
        char buf[BUF_SIZE];
        regerror(error, &regex, buf, BUF_SIZE);
        fprintf(stderr, "regcomp error: %s\n", buf);
        return 1;
    }

    regmatch_t bags[BAGS_SIZE];
    if (regexec(&regex, string, BAGS_SIZE, bags, 0)) {
        printf("%s\n", string);
    } else {
        struct buffer buf;
        buf.data = malloc(1 * sizeof(buf));
        buf.capacity = 1;
        buf.len = 0;
        size_t len_substi = strlen(substitution);
        for (int i = 0; i < len_substi; ++i) {
            if (substitution[i] == '\\') {
                ++i;
                if (i >= len_substi) {
                    fprintf(stderr, "Error. Slash \"\\\" without pair in substitution.\n");
                    free(buf.data);
                    return 1;
                } else {
                    if (isdigit(substitution[i])) {
                        int bag_index = substitution[i] - '0';
                        if (bags[bag_index].rm_so == -1) {
                            fprintf(stderr, "Error. Non-existent bag number %d\n", bag_index);
                            free(buf.data);
                            return 1;
                        }
                        int start = bags[bag_index].rm_so;
                        int end = bags[bag_index].rm_eo;
                        append(&buf, string + start, end - start);
                    } else {
                        append(&buf, substitution + i, 1);
                    }
                }
            } else {
                append(&buf, substitution + i, 1);
            }
        }
        int start = bags[0].rm_so;
        int end = bags[0].rm_eo;
        printf("%.*s%s%s\n", start, string, buf.data, string + end);
        free(buf.data);
    }
    regfree(&regex);
    return 0;
}