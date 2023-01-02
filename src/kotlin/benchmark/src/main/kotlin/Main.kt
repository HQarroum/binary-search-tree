import com.algorithms.trees.bst.BinarySearchTree;
import java.util.*
import kotlin.system.measureTimeMillis

/**
 * The number of elements to insert.
 */
const val ITERATIONS = 100000

fun main(args: Array<String>) {
    // An array with random numbers.
    val array  = (1..ITERATIONS).map { Random().nextInt() }

    // Measuring the time it takes to insert and find nodes.
    val time = measureTimeMillis {
        // Creating the binary-search tree.
        val tree = BinarySearchTree<Int> { a: Int, b: Int -> a - b }

        // Inserting values.
        for (i in array) {
            tree.insert(i)
            assert(tree.find(i) != null)
        }
    }

    // Displaying the result.
    println("$time ms")
}