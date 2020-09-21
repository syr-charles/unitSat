#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "problem.h"

/*
 *  Choose separator mode, one blank allows better performance, several blanks better flexibility.
 *  Choosing one blank on ill-formatted file will result in undefined behavior.
 *  If both are active, several will take precedence.
 */

#define ONE_BLANK 0
#define SEVERAL_BLANKS 1

#if !(ONE_BLANK || SEVERAL_BLANKS)
# error please choose separator mode
#endif

__attribute__((always_inline)) inline void
skip_comments_line (char **data) {

    while (**data == 'c') {
        while (**data != '\n')
            *data += 1;
        *data += 1;
    }
}

int
get_line_length(char **data) {

    /*
     *  Lines must be properly formatted otherwise result will be inaccurate, ie.
     *  [int][single_space][int][single_space][int]... [0][newline]
     */

    int num = 0;
    while (**data != '0') {

        /* Will skip either minus sign or first digit. */
        *data += 1;

        /* Will skip remaining digits if any. */
        while (isdigit(**data)) *data += 1;

#if SEVERAL_BLANKS
        while (isblank(**data))
#endif

            *data += 1;
        num += 1;
    }

    *data += 2;
    return num;
}

int **
parse_cnf (char *data) {

    skip_comments_line(&data);

    /* Expect 'p cnf K P' line where K is the max integer value and P the number of lines. */
    if (*data != 'p')
        return NULL;

    /* Position data on column number. */
    while (!isdigit(*data)) data += 1;
    while (isdigit(*data)) data += 1;
    while (!isdigit(*data)) data += 1;

    int column_number = strtol(data, &data, 10);
    data += 1;
    int **array = malloc(sizeof(int *) * (column_number + 1));
    if (__builtin_expect(!array, 0))
        return NULL;

    /* Parsing. */
    for (int k = 0; k < column_number;) {
        skip_comments_line(&data);

        /* We need to iterate twice over the line, keep data at the beginning of next line and work on copy. */
        char *line = data;
        array[k] = malloc(sizeof(int) * (get_line_length(&data) + 1));
        if (__builtin_expect(!array[k], 0))
            return NULL;

        /* Map values. */
        for (int p = 0; *line != '\n'; p += 1) {
            int val = (int)strtol(line, &line, 10);
            if ((array[k][p] = val) == 0)
                break;
            line += 1;
        }

        /* Zero terminate the array. */
        if (++k == column_number) {
            array[k] = 0;
            break;
        }
    }

    return array;
}

int **
read_cnf (char const *filename) {

    int **array;

    /* Process file. */
    if (filename) {
        int const fd = open(filename, O_RDONLY);
        if (fd == -1)
            return NULL;

        struct stat s;
        if (stat(filename, &s) == -1)
            return NULL;

        void *m = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (m == MAP_FAILED)
            return NULL;

        array = parse_cnf((char *)m);
        munmap(m, s.st_size);

    /* Read from standard input. */
    } else {
        char buff[BUFSIZ];
        char *data = NULL;
        size_t pos = 0;

        for (size_t bytes = 0; (bytes = read(STDIN_FILENO, buff, BUFSIZ)); ) {
            if (bytes == (size_t)-1)
                return NULL;
            data = realloc(data, pos + bytes);
            strncpy(&data[pos], buff, bytes);
            pos += bytes;
        }

        size_t len = strlen(buff);
        data = realloc(data, pos + len);
        strncpy(&data[pos], buff, len);

        array = parse_cnf(data);
    }

    return array;
}

int	**ft_solve(int **problem);

int
main (int argc, char const *argv[]) {

	int	**sol;
	int	var;
    int **ret = read_cnf(argc == 1 ? NULL : argv[1]);
    if (ret == NULL) {
        printf("Invalid\n");
        return EXIT_FAILURE;
    }

#if 0
        /* Display for testing. */
        for (int k = 0; ret[k]; k += 1) {
            for (int p = 0; ret[k][p]; p += 1)
                printf("[%d]", ret[k][p]);
            printf("\n");
        }
#endif
	var = ft_variables(ret);
	sol = ft_solve(ret);
	printf("List of all possible solutions :\n");
	for (int k = 0; sol[k]; k += 1) {
		for (int p = 1; p <= var; p += 1)
			printf("[%d]", sol[k][p] * p);
		printf("\n");
	}
    return EXIT_SUCCESS;
}
