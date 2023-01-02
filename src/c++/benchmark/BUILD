cc_binary(
  name = "benchmark",
  srcs = ["main.cpp"],
  copts = [
    "-Iinclude",
    "-std=c++17",
    "-W",
    "-Wall",
    "-Werror",
    "-O3",
    "-Wno-deprecated"
  ],
  deps = [
    "//include:binary_search_tree"
  ]
)
