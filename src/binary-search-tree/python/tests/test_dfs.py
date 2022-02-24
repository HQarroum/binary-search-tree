import unittest
from lib.bst import BinarySearchTree

class BstDfsIterator(unittest.TestCase):

  def setUp(self):
    self.bst = BinarySearchTree(comparator=lambda x, y: x - y)
    self.bst.insert([5, 3, 7, 2, 4, 6, 8, 9, 10])

  def runTest(self):
    array = [n.data for n in self.bst.dfs_iterator()]
    self.assertEqual(array, [5, 3, 2, 4, 7, 6, 8, 9, 10])
