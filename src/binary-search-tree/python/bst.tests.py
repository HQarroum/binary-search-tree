import unittest
from bst import BinarySearchTree

class BstRemoval(unittest.TestCase):

  def setUp(self):
    self.bst = BinarySearchTree(comparator=lambda x, y: x - y)
    self.bst.insert([5, 3, 7, 2, 4, 6, 8, 9, 10])

  def runTest(self):
    self.bst.remove(10)
    self.assertEqual(self.bst.size, 9)

if __name__ == '__main__':
  unittest.main()
