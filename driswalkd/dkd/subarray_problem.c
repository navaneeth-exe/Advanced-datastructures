#include <stdio.h>
#include <stdlib.h>

#define OFFSET 10000
#define MAX_SUM 20001

int count_zero_sum_subarrays(int* nums, int size) {
    int current_sum = 0;
    int total_count = 0;
    int* freq = (int*)calloc(MAX_SUM, sizeof(int));

    freq[0 + OFFSET] = 1;

    for (int i = 0; i < size; i++) {
        current_sum += nums[i];
        
        if (current_sum + OFFSET >= 0 && current_sum + OFFSET < MAX_SUM) {
            total_count += freq[current_sum + OFFSET];
            freq[current_sum + OFFSET]++;
        }
    }

    free(freq);
    return total_count;
}

int main() {
    int arr[] = {1, -1, 1, -1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", count_zero_sum_subarrays(arr, n));

    return 0;
}
