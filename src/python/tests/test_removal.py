import unittest
from lib.bst import BinarySearchTree

class BstRemoval(unittest.TestCase):

  def setUp(self):
    self.bst = BinarySearchTree(comparator=lambda x, y: x - y)
    self.bst.insert([5, 3, 7, 2, 4, 6, 8, 9, 10])

  def runTest(self):
    self.bst.remove(2)
    self.assertEqual(self.bst.size, 9)
    self.assertEqual(self.bst.find(2), None)
    self.assertEqual(self.bst.min().data, 3)
    self.assertEqual(self.bst.max().data, 10)
    self.bst.remove(5)
    self.assertEqual(self.bst.size, 8)
    self.assertEqual(self.bst.find(5), None)
    self.assertEqual(self.bst.min().data, 3)
    self.assertEqual(self.bst.max().data, 10)
