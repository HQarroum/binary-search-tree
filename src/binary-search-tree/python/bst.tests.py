import unittest
from bst import BinarySearchTree

class BstInitialization(unittest.TestCase):

  def setUp(self):
    self.functor = lambda x, y: x - y
    self.bst = BinarySearchTree(comparator=self.functor)

  def runTest(self):
    self.assertEqual(self.bst.root, None)
    self.assertEqual(self.bst.size, 0)
    self.assertEqual(self.bst.comparator, self.functor)

class BstInsertion(unittest.TestCase):

  def setUp(self):
    self.bst = BinarySearchTree(comparator=lambda x, y: x - y)
    
    # Inserting elements sequentially.
    self.bst.insert(5)
    self.bst.insert(3)
    self.bst.insert(7)
    self.bst.insert(2)

    # Inserting elements in bulk.
    self.bst.insert([1, 4, 6, 8, 9, 10])

  def runTest(self):
    
    self.assertEqual(self.bst.root.data, 5)
    self.assertEqual(self.bst.root.left.data, 3)
    self.assertEqual(self.bst.root.left.left.data, 2)
    self.assertEqual(self.bst.root.left.right.data, 4)
    self.assertEqual(self.bst.root.right.data, 7)
    self.assertEqual(self.bst.root.right.right.data, 8)
    self.assertEqual(self.bst.root.right.right.right.data, 9)
    self.assertEqual(self.bst.root.right.right.right.right.data, 10)
    self.assertEqual(self.bst.size, 10)

class BstMinMaxSearch(unittest.TestCase):

  def setUp(self):
    self.bst = BinarySearchTree(comparator=lambda x, y: x - y)
    self.bst.insert([5, 3, 7, 2, 4, 6, 8, 9, 10])

  def runTest(self):
    self.assertEqual(self.bst.min().data, 2)
    self.assertEqual(self.bst.max().data, 10)

class BstSort(unittest.TestCase):

  def setUp(self):
    self.bst = BinarySearchTree(comparator=lambda x, y: x - y)
    self.dataset = [5, 3, 7, 2, 4, 6, 8, 9, 10]
    self.bst.insert(self.dataset)

  def runTest(self):
    self.assertEqual(self.bst.sort(), sorted(self.dataset))

class BstRemoval(unittest.TestCase):

  def setUp(self):
    self.bst = BinarySearchTree(comparator=lambda x, y: x - y)
    self.bst.insert([5, 3, 7, 2, 4, 6, 8, 9, 10])

  def runTest(self):
    self.bst.remove(10)
    self.assertEqual(self.bst.size, 9)

if __name__ == '__main__':
  unittest.main()
