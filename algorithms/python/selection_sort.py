from typing import MutableSequence


def swap(l: MutableSequence[int], i1: int, i2: int) -> None:
  l[i1], l[i2] = l[i2], l[i1]


def selection_sort_v1(l: MutableSequence[int]) -> None:
  for i in range(len(l) - 1):
    smallest = i
    for j in range(i + 1, len(l)):
      if l[j] < l[smallest]:
        smallest = j
    if smallest != i:
      swap(l, i, smallest)


a = [3, 1, 2, 5, 4]

print(a)
selection_sort_v1(a)
print(a)
