cc_test(
  name = "tests",
  srcs = glob(["*.cpp"]),
  copts = [
    "-Iinclude",
    "-std=c++17",
    "-Wno-deprecated"
  ],
  deps = [
    "@com_google_googletest//:gtest_main",
    "//include:binary_search_tree"
  ]
)
