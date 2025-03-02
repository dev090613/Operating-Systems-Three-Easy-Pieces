#include <stdio.h>
#include <stdlib.h> // malloc

int main()
{
    int *arr = NULL;
    
    arr = (int *)malloc(10 * sizeof(int));
    if (arr == NULL) {
        perror("malloc failed.");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        arr[i] = i;
    }

    printf("This is array: \n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }

    // free(arr);

    return 0;
}

