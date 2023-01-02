import datetime
from random import seed
from random import randint
from bst import BinarySearchTree

# Initialize the random generator seed.
seed(1)

# The number of elements to insert.
iterations = 100000

# The array of random values.
array = [randint(0, iterations) for _ in range(iterations)]

if __name__ == '__main__':
  # Initialize the start time.
  begin = datetime.datetime.now()

  bst = BinarySearchTree(comparator=lambda x, y: x - y)

  # Inserting elements sequentially.
  for element in array:
    bst.insert(element)
    assert(bst.find(data=element) is not None)

  delta = datetime.datetime.now() - begin
  print(f'{delta.total_seconds() * 1000} ms')
