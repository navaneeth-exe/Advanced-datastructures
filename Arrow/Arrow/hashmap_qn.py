def count_zero_sum_subarrays(arr):
    prefix_sum = 0
    count = 0

    freq = {0: 1}  # Important: handles sum from index 0

    for num in arr:
        prefix_sum += num

        if prefix_sum in freq:
            count += freq[prefix_sum]

        freq[prefix_sum] = freq.get(prefix_sum, 0) + 1

    return count


# Example
arr = [1, -1, 2, -2, 3]
print("Count:", count_zero_sum_subarrays(arr))
