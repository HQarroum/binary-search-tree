cc_binary(
  name = "insertion",
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
  ],
  visibility = ["//visibility:public"]
)
