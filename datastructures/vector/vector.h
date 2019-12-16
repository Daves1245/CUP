#ifndef VECTOR_H
#define VECTOR_H

/* Constants */
#define VECTOR_INIT_CAPACITY 4

// The vector structure
typedef struct vector {
  void **items;
  int capacity;
  int size;
} vector;

/* Creation/Deletion - Memory management */
vector * vector_new();
void vector_delete(vector *);

/* Non-modifiers */ 
int vector_size(vector *); // grab size of vector 
void * vector_get(vector *, int); // grab element at index
int vector_empty(vector *);

/* Internal usage */
void vector_resize(vector *, int); // dynamically reallocate memory 

/* Modification - Data management */
void vector_add(vector *, void *);
void vector_set(vector *, int, void *);
void *vector_get(vector *, int);
void vector_rm(vector *, int);

#endif
