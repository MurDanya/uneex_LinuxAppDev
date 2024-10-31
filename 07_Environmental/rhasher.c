#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

#include <rhash.h>

#ifdef READLINE
#include <readline/readline.h>
#endif

int main() {
    rhash_library_init();

    unsigned char digest[64];
    char output[128];

    int rhash_algorithm;
    int rhash_flag;

    char* line = NULL;

#ifdef READLINE
    while (line = readline(prompt))
#else
    size_t len = 0;
    while (getline(&line, &len, stdin) != -1)
#endif
    {
        size_t len_line = strlen(line);
        if (len_line && line[len_line - 1] == '\n') {
            line[len_line - 1] = '\0';
        }

        char* algorithm = strtok(line, " ");
        char* message = strtok(NULL, " ");

        if (!algorithm || !message) {
            fprintf(stderr, "Error. Use 2 words: <hashing algorithm name> <filename/string>\n");
            continue;
        }

        rhash_flag = isupper(algorithm[0]) ? RHPR_HEX : RHPR_BASE64;

        for (size_t i = 0; i < strlen(algorithm); i++) {
            algorithm[i] = toupper(algorithm[i]);
        }

        if (!strcmp(algorithm, "MD5")) {
            rhash_algorithm = RHASH_MD5;
        } else if (!strcmp(algorithm, "SHA1")) {
            rhash_algorithm = RHASH_SHA1;
        } else if (!strcmp(algorithm, "TTH")) {
            rhash_algorithm = RHASH_TTH;
        } else {
            fprintf(stderr, "Error. Wrong hash algorithm: %s\n", algorithm);
            continue;
        }

        int result = 0;
        if (message[0] == '\"') {
            result = rhash_msg(rhash_algorithm, message + 1, strlen(message) - 1, digest);
        } else {
            result = rhash_file(rhash_algorithm, message, digest);
        }

        if (result < 0) {
            fprintf(stderr, "Error in computing rhash: %s: %s\n", message, strerror(errno));
            continue;
        }

        rhash_print_bytes(output, digest, rhash_get_digest_size(rhash_algorithm), rhash_flag);

        printf("%s\n", output);
    }

    free(line);
    return 0;
}