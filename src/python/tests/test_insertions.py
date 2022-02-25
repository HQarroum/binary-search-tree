import unittest
from lib.bst import BinarySearchTree

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
