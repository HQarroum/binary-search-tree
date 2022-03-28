import com.algorithms.trees.bst.BinarySearchTree

fun main() {
  // An array of values.
  val array = arrayOf(50, 70, 60, 20, 90, 10, 40, 100)

  // Creating the binary-search tree.
  val tree = BinarySearchTree<Int> { a: Int, b: Int -> a - b }

  // Inserting values.
  for (i in array) {
    tree.insert(i)
  }

  // Printing the tree.
  println(tree.toString())
  
  // Removing values.
  for (i in array.reversed()) {
    tree.remove(i)
  }

  // Printing the tree.
  println(tree.toString())

  // Inserting values.
  for (i in array) {
    tree.insert(i)
  }

  // Printing the tree.
  println(tree.toString())

  // Clearing the tree.
  tree.clear()

  // Printing the tree.
  println(tree.toString())
}
