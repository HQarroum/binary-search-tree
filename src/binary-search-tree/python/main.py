import random
from bst import BinarySearchTree

def generate(n):
  return random.sample([i for i in range(1, n)], n - 1)

def foo(**kwargs):
  return kwargs.get('data', 1)

if __name__ == '__main__':
  bst = BinarySearchTree(comparator=lambda x, y: x - y)

  bst.insert(generate(20))

  print(str(bst))
  print(bst.kth_largest(k=1).data)
