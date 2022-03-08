#include <cfloat>
#include <cassert>
#include <cmath>
#include <random>
#include <chrono>
#include <array>
#include <iostream>
#include <binary_search_tree.hpp>

/**
 * The number of elements to insert into the tree.
 */
static const size_t iterations = 100000;

int main(void) {
  std::random_device device;
  std::default_random_engine engine(device());
  std::uniform_int_distribution<int> uniform_dist(1, iterations);

  // The array containing random values.
  auto array = std::array<int, iterations>();

  // Fill the array with random values.
  for (size_t i = 0; i < iterations; ++i) {
    array[i] = uniform_dist(engine);
  }

  // Initializing the clock.
  auto begin = std::chrono::high_resolution_clock::now();

  // Creating the binary-search tree.
  auto tree = bst::tree_t<int>();

  // Inserting the elements into the tree.
  for (size_t i = 0; i < iterations; ++i) {
    auto value = array[i];
    tree.insert(value);
    assert(tree.find(value).has_value());
  }

  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::high_resolution_clock::now() - begin
  ).count() << "ms" << std::endl;

  return (0);
}