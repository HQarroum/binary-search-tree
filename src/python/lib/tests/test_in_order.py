import unittest
from bst import BinarySearchTree

class BstInOrderIterator(unittest.TestCase):

  def setUp(self):
    self.dataset = [5, 3, 7, 2, 4, 6, 8, 9, 10]
    self.bst = BinarySearchTree(comparator=lambda x, y: x - y)
    self.bst.insert(self.dataset)

  def runTest(self):
    array = [n.data for n in self.bst.in_order_iterator()]
    self.assertEqual(array, [2, 3, 4, 5, 6, 7, 8, 9, 10])
    self.assertEqual(array, sorted(self.dataset))
