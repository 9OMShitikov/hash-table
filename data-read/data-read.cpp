#include "data-read.h"
size_t read_data (char **buff, const char* input_name){
    MY_ASSERT(buff);
    MY_ASSERT(input_name);

    FILE *input_file = fopen(input_name, "r");
    MY_ASSERT(input_file);

    MY_ASSERT(fseek(input_file, 0L, SEEK_END) == 0);
    long size = ftell(input_file);
    MY_ASSERT(size >= 0);
    MY_ASSERT(fseek(input_file, 0L, SEEK_SET) == 0);

    *buff = (char *) calloc(size, sizeof(char));
    if (fread(*buff, sizeof(char), size, input_file) != size) {
        MY_ASSERT(feof(input_file));
    }
    MY_ASSERT(fclose(input_file) == 0);

    return size;
}

size_t parse_data(char ***strings, char **buff, size_t buff_size) {
    MY_ASSERT(buff);
    MY_ASSERT(strings);

    int lines_count = 0;
    for (int i = 0; i < buff_size; ++i) {
        if ((*buff)[i] == '\0') {
            ++lines_count;
        }
    }

    (*strings) = (char **) calloc (lines_count, sizeof(char*));

    int j = 0;
    for (int i = 0; i < buff_size; ++i) {
        (*strings)[j] = *buff + i;
        ++j;
        i += strlen(*buff + i);
    }

    return lines_count;
}
