
#include "input.h"

/*
* it turns out the C library has (relatively) recently
* added a function called getline() that if called with 
* a null pointer, will do as the methods below are intended
* to. nonetheless, i provide my own approach below.
*/
// grab the next space-separated word from standard input
const char * input_next() {
    size_t size = MESSAGE_MAX_SIZE;
    /* use of sizeof(*ret) removes the need
    * to edit the multiplication later
    * should the type of ret change */
    char * ret = malloc(sizeof(*ret) * size);
    int c, i = 0;
    while ((c = getchar()) != ' ') {
        if (i == size) {
            size *= 2;
            ret = realloc(ret, sizeof(*ret) * size);
        }
        if (c == '\n' || c == EOF) { // we've hit an end 
                                    break;
                                   }
        ret[i++] = c;
    }
    ret[i] = '\0';
    return ret;
}
// grab the next newline-separated line from standard input
const char * input_nextln() {
    int size = MESSAGE_MAX_SIZE; 
    char * ret = malloc(sizeof(*ret) * size);
    int c, i = 0;
    while ((c = getchar()) != EOF) {
        if (i == size) {
            ret = realloc(ret, sizeof(*ret) * size);
        }
        if (c == '\n') {
            break;
        }
        ret[i++] = c;
    }
    ret[i] = '\0';
    return ret;
}
