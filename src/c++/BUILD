cc_library(
  name = "binary_search_tree",
  hdrs = ["include/binary_search_tree.hpp"],
  includes = ["include"],
  visibility = [
    "//visibility:public",
  ]
)

cc_binary(
  name = "insert_and_search",
  srcs = ["examples/insert_and_search/main.cpp"],
  deps = [
    ":binary_search_tree"
  ]
)
