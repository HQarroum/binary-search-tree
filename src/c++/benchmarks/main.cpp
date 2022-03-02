#include <cfloat>
#include <cmath>
#include <random>
#include <binary_search_tree.hpp>

/**
 * The number of elements to insert into the tree.
 */
static const size_t iterations = 100000;

int main(void) {
  std::random_device device;
  std::default_random_engine engine(device());
  std::uniform_int_distribution<int> uniform_dist(1, iterations);

  auto tree = bst::tree_t<int>();

  for (int i = 0; i < iterations; ++i) {
    auto element = uniform_dist(engine);
    tree.insert(element);
    assert(tree.find(element).has_value());
  }

  return (0);
}