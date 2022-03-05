#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <binary_search_tree.hpp>

/**
 * @brief Definition of a complex type
 * holding an integer.
 */
struct complex_t {
  int value_;

  /**
   * @brief Default constructor.
   */
  complex_t(int value) : value_(value) {}
  
  /**
   * @brief Provides a textual representation of the
   * type.
   * @param os the output stream.
   * @param c the type to output.
   * @return a reference to the output stream.
   */
  friend std::ostream& operator<<(std::ostream& os, const complex_t& c) {
    os << c.value_;
    return (os);
  }
};

/**
 * @brief Options for a binary search tree containing
 * strings.
 */
static auto string_options = bst::options_t<std::string>(
  [] (const std::string& a, const std::string& b) -> int {
    return (a.compare(b));
  },
  [] (const std::string& value) -> std::string {
    return (value);
  }
);

/**
 * @brief Options for a binary search tree containing
 * a complex type.
 */
static auto complex_options = bst::options_t<complex_t>(
  [] (const complex_t& a, const complex_t& b) -> int {
    return (a.value_ - b.value_);
  },
  [] (const complex_t& value) -> std::string {
    return (std::to_string(value.value_));
  }
);

/**
 * @brief Displays information about the given tree.
 */
template <typename T>
std::string format(const bst::tree_t<T>& tree) {
  std::stringstream ss;

  ss << "Size : " << tree.size() << std::endl
    << "Min : " << tree.min()->value() << std::endl
    << "Max : " << tree.max()->value() << std::endl
    << std::endl << tree;
  return (ss.str());
}

int main(void) {
  // Creating different trees with different types.
  auto complex_tree = bst::tree_t<complex_t>(complex_options);
  auto string_tree = bst::tree_t<std::string>(string_options);
  auto double_tree = bst::tree_t<double>();
  auto float_tree = bst::tree_t<float>();

  // Insert the data into the tree.
  string_tree.insert("abc", "aaa", "bbb", "ab");
  double_tree.insert(2.0, 4.0, 5.0, 3.0, 6.0);
  float_tree.insert(2.0f, 4.0f, 5.0f, 3.0f, 6.0f);
  complex_tree.insert(
    complex_t(50),
    complex_t(70),
    complex_t(60),
    complex_t(20)
  );

  // Displaying the content of each tree.
  std::cout << format(string_tree) << std::endl;
  std::cout << format(double_tree) << std::endl;
  std::cout << format(float_tree) << std::endl;
  std::cout << format(complex_tree) << std::endl;

  return (0);
}