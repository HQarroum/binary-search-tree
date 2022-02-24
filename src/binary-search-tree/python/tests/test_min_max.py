import unittest
from lib.bst import BinarySearchTree

class BstMinMaxSearch(unittest.TestCase):

  def setUp(self):
    self.bst = BinarySearchTree(comparator=lambda x, y: x - y)
    self.bst.insert([5, 3, 7, 2, 4, 6, 8, 9, 10])

  def runTest(self):
    self.assertEqual(self.bst.min().data, 2)
    self.assertEqual(self.bst.max().data, 10)
