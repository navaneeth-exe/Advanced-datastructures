def count_zero_sum_subarrays(arr):
 prefix_sum = 0
 total = 0
 seen = {}
 for num in arr:
  prefix_sum += num
  if prefix_sum == 0:
   total += 1
  if prefix_sum in seen:
   total += seen[prefix_sum]
  seen[prefix_sum] = seen.get(prefix_sum, 0) + 1
 return total
arr = list(map(int, input("Enter numbers separated by space: ").split()))
result = count_zero_sum_subarrays(arr)
print("Array:", arr)
print("Total zero-sum subarrays:", result)
