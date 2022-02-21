import random
from bst import BinarySearchTree

def generate(n):
  return random.sample([i for i in range(1, n)], n - 1)

if __name__ == '__main__':
  bst = BinarySearchTree(comparator=lambda x, y: x - y)

  bst.insert(generate(20))

  print(str(bst))

  for node in bst.dfs_iterator():
    print(node.data)
  #print(list(map(lambda n: n.data, bst.depth_first())))
  