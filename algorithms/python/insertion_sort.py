from typing import MutableSequence


def insertion_sort(l: MutableSequence) -> None:
  for i in range(1, len(l)):
    while i and l[i - 1] > l[i]:
      l[i], l[i - 1] = l[i - 1], l[i]
      i -= 1


a = [2, 1, 3, 9, 8, 7, 6, 5, 4]

print(a)
insertion_sort(a)
print(a)
