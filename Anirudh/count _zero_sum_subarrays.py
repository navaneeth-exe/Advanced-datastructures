def count_zero_sum_subarrays(arr):
    prefix_sum = 0
    count = 0
    freq = {0: 1}  # prefix sum 0 occurs once initially

    for num in arr:
        prefix_sum += num

        if prefix_sum in freq:
            count += freq[prefix_sum]

        freq[prefix_sum] = freq.get(prefix_sum, 0) + 1

    return count


# Example 1 (all positive)
arr1 = [1, 2, 3, 4]
print(count_zero_sum_subarrays(arr1))  # 0

# Example 2 (contains zero)
arr2 = [0, 1, 2, 0]
print(count_zero_sum_subarrays(arr2))  # 2

# Example 3 (with negatives)
arr3 = [1, -1, 2, -2, 3]
print(count_zero_sum_subarrays(arr3))  # 3
