cc_test(
  name = "launch_tests",
  srcs = glob(["*.cpp"]),
  copts = [
    "-Iinclude",
    "-std=c++17"
  ],
  deps = [
    "@com_google_googletest//:gtest_main",
    "//include:binary_search_tree"
  ]
)
