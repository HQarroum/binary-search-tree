cc_binary(
  name = "using_other_types",
  srcs = ["main.cpp"],
  copts = [
    "-Iinclude",
    "-std=c++17",
    "-Wno-deprecated"
  ],
  deps = [
    "//include:binary_search_tree"
  ],
  visibility = ["//visibility:public"]
)
