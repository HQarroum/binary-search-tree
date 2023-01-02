<br /><br /><br /><br />
<p align="center">
  <img width="240" src="assets/icon.png" />
</p>
<br /><br />

# binary-search-tree
> A set of idiomatic implementations of a binary-search tree in multiple languages.

Current version: **1.0.0**

## 📋 Table of content

- [Implementations](#-implementations)
- [Description](#-description)
- [Benchmarks](#-benchmarks)
- [See also](#-see-also)

## ✏️ Implementations

This repository contains implementations in the following languages.

> Click to access a particular implementation.

<br />
<table align="center">
  <thead>
    <tr>
      <th>Python</th>
      <th>Typescript</th>
      <th>C</th>
      <th>C++</th>
      <th>Kotlin</th>
    </tr>
  </thead>
  <tr>
    <td><a href="src/python"><img width="80" src="assets/python.png" ></a></td>
    <td><a href="src/typescript"><img width="80" src="assets/typescript.png" /></a></td>
    <td><a href="src/c"><img width="80" src="assets/c.png" ></a></td>
    <td><a href="src/c++"><img width="80" src="assets/c++.png" ></a></td>
    <td><a href="src/kotlin"><img width="80" src="assets/kotlin.png" ></a></td>
  </tr>
</table>
<br />

> Please refer to each implementation on how to use it, test it and benchmark it.

## 🔰 Description

This repository contains idiomatic implementations of a [Binary Search Tree](https://en.wikipedia.org/wiki/Binary_search_tree) in multiple programming languages. The purpose of this repository is purely educational and allows to introduce a binary search tree recursive data structure, as well as its many implementation details across multiple languages.

A binary search tree is a tree data structure that can store arbitrarily typed data by enforcing the following properties :

- The left subtree of a node contains only nodes with keys lesser than the node’s key.
- The right subtree of a node contains only nodes with keys greater than the node’s key.
- The left and right subtree each must also be a binary search tree.
- It doesn't have any duplicate nodes.

A binary search tree supports operations like `search`, `insertion`, `deletion`, `min-max search`, in `O(h)` time where `h` is the height of the tree. Below is an example of the structural organization of elements in a binary search tree.

<br /><br />
<p align="center">
  <img width="700" src="assets/bst.jpeg" />
</p>
<br /><br />

## 📈 Benchmarks

The following benchmark results have been executed on a *Macbook M1 Pro* running 100.000 insertions and searches on a binary search tree.

<br /><br />
<p align="center">
  <img width="700" src="assets/benchmark.png" />
</p>
<br /><br />

## 👀 See also

- The [Binary Search Tree](https://en.wikipedia.org/wiki/Binary_search_tree) Wiki page.
- [Convert](https://www.geeksforgeeks.org/convert-normal-bst-balanced-bst/) a Binary Search Tree into a balanced tree.
