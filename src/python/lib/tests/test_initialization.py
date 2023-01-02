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
