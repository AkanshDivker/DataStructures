# DataStructures
A simple set of a few data structures that are efficient and easy to use, written in C++ .

## Getting Started
To use any of the data structures, simply import the header files into your project and include them in your source files where being used.

### Binary Tree
In order to initialize a Binary Tree, create a new BinaryTree object. For C++, I recommend using std::unique_pointer instead of creating a raw pointer.
```
// Recommended
std::unique_ptr<BinaryTree> binaryTree(new BinaryTree());

// Raw Pointer
BinaryTree *binaryTree = new BinaryTree();
```
### Red Black Tree
Initializing a Red Black Tree is a similar process. Create a new RedBlackTree object.
```
// Recommended
std::unique_ptr<RedBlackTree> rbt(new RedBlackTree());

// Raw Pointer
RedBlackTree *rbt = new RedBlackTree();
```

