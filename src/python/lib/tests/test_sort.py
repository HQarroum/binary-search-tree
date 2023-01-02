import unittest
from bst import BinarySearchTree

class BstSort(unittest.TestCase):

  def setUp(self):
    self.bst = BinarySearchTree(comparator=lambda x, y: x - y)
    self.dataset = [5, 3, 7, 2, 4, 6, 8, 9, 10]
    self.bst.insert(self.dataset)

  def runTest(self):
    self.assertEqual(self.bst.sort(), sorted(self.dataset))
