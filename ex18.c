#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17. */
void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

// a typedef creates a fake type, in this case for a function pointer
typedef int(*compare_cb)(int a, int b);

/**
 * A classic bubble sort function that compares elements.
 * param numbers is a pointer to an array of integers
 * param count is the size of numbers array
 * param cmp is a function pointer to a function whose signature matches typedef compare_cb
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if (!target) {
        die("Memory error.");
    }

    memcpy(target, numbers, count * sizeof(int));

    for (i = 0; i < count; i++) {

        for (j = 0; j < (count - 1); j++) {
            // call whatever function function pointer cmp points to
            // use local variable target for arguments.
            if (cmp(target[j], target[j+1]) > 0) {
                temp = target[j+1];
                target[j+1] = target[j];
                target[j] = temp;
            }
        }
    }
    return target;
}

/** sorted_order function signature is compatible with function pointer typedef compare_cb
 */
int sorted_order(int a, int b)
{
    return a - b;
}

/** reverse_order function signature is compatible with function pointer typedef compare_cb
 */
int reverse_order(int a, int b)
{
    return b - a;
}

/** strange_order function signature is compatible with function pointer typedef compare_cb
 */
int strange_order(int a, int b)
{
    if (a == 0 || b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

/**
 * Test bubble_sort by sorting elements and printing results.
 */
void test_sorting(int *numbers, int count, compare_cb cmp)
{
    int i = 0;
    int *sorted = bubble_sort(numbers, count, cmp);
    if (!sorted) {
        die("Failed to sort as requested.");
    }

    for (i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");
    free(sorted);

    // print function pointed to by cmp as a string
    unsigned char *data = (unsigned char *)cmp;
    for (i = 0; i < 25; i++) {
        printf("%02x:", data[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        die("USAGE: ex18 4 3 1 5 6");
    }

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));

    if (!numbers)
    {
        die("Memory error.");
    }

    for (i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    // call test_sorting(), passing name of a function whose signature matches typedef compare_cb.
    // C compiler finds the address of the function.
    test_sorting(numbers, count, sorted_order);
    test_sorting(numbers, count, reverse_order);
    test_sorting(numbers, count, strange_order);

    free(numbers);

    return 0;
}