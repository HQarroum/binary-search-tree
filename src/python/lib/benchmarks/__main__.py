from random import seed
from random import randint
from bst import BinarySearchTree

# Initialize the random generator seed.
seed(1)

# The number of elements to insert.
iterations = 100000

if __name__ == '__main__':
  bst = BinarySearchTree(comparator=lambda x, y: x - y)

  # Inserting elements sequentially.
  for _ in range(iterations):
    number = randint(1, iterations)
    bst.insert(number)
    bst.find(data=number)
