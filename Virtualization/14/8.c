#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} Vector;

void vector_init(Vector *vec) {
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

void vector_push(Vector *vec, int value) {
    if (vec->size >= vec->capacity) {
        int new_capacity = vec->capacity == 0 ? 1 : vec->capacity * 2;
        
        int* new_data = (int *)realloc(vec->data,
                new_capacity * sizeof(int));
        if (!new_data){
            perror("realloc failed.");
            exit(1);
        }
        vec->data = new_data;
        vec->capacity = new_capacity;
    }
    vec->data[vec->size++] = value;
}

int vector_get(Vector *vec, int index) {
    if (index < 0 || index >= vec->size) {
        printf("index error");
        exit(1);
    }

    return vec->data[index];
}

void vector_print(Vector *vec)
{
    printf("Vector(size: %d, capacity: %d): ",
            vec->size, vec->capacity);

    printf("[");
    for (int i = 0; i < vec->size; i++) {
        printf("%d", vec->data[i]);
        if (i < vec->size - 1)
            printf(", ");
    }
    printf("]");

    printf("\n");
}

void vector_free(Vector *vec)
{
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;

}

int main()
{
    Vector vec;
    vector_init(&vec);

    for (int i = 0; i < 10; i++) {
        vector_push(&vec, i * 10);
        vector_print(&vec);
    }

    vector_free(&vec);

    return 0;
}
