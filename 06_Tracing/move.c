#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

void remove_file(FILE* infile, FILE* outfile, const char* outfile_name, const char* error_msg, const char* error_filename) {
    fclose(infile);
    fclose(outfile);
    if (remove(outfile_name)) {
        fprintf(stderr, "Can't remove outfile %s during error\n", outfile_name);
        exit(7);
    }
    fprintf(stderr, "%s %s\n", error_msg, error_filename);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Error. Use 2 arguments:\n%s infile outfile\n", argv[0]);
        return 1;
    }
    char* infile_name = argv[1];
    char* outfile_name = argv[2];
    FILE* infile = fopen(infile_name, "r");
    if (!infile) {
        fprintf(stderr, "Error. Can't open file %s for reading\n", infile_name);
        return 2;
    }
    FILE* outfile = fopen(outfile_name, "w");
    if (!outfile) {
        fclose(infile);
        fprintf(stderr, "Error. Can't open file %s for writing\n", outfile_name);
        return 3;
    }
    char buf[BUFSIZE];
    while (!feof(infile)) {
        size_t count_read = fread(buf, sizeof(char), BUFSIZE, infile);
        if (ferror(infile)) {
            remove_file(infile, outfile, outfile_name, "Error. Can't read from file", infile_name);
            return 4;
        }
        size_t count_write = fwrite(buf, sizeof(char), count_read, outfile);
        if (ferror(outfile) || count_read != count_write) {
            remove_file(infile, outfile, outfile_name, "Error. Can't write to file", outfile_name);
            return 5;
        }
    }
    fclose(infile);
    fclose(outfile);
    if (remove(infile_name)) {
        remove(outfile_name);
        fprintf(stderr, "Can't remove infile %s after move\n", infile_name);
        return 6;
    }
    return 0;
}