/**
	Simple Data Structures
	BinaryTree.h

	@author Akansh Divker
	@version 1.0
*/

#pragma once

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <string>

class Node
{
private:

	std::string data;
	Node *left;
	Node *right;

public:

	Node(const std::string& value) : left(nullptr), right(nullptr), data(value) {}

	void SetData(const std::string& value)
	{
		data = value;
	}

	void SetLeft(Node *leftPtr)
	{
		left = leftPtr;
	}

	void SetRight(Node *rightPtr)
	{
		right = rightPtr;
	}

	const std::string& GetData()
	{
		return data;
	}

	Node *GetLeft()
	{
		return left;
	}

	Node *GetRight()
	{
		return right;
	}
};

class BinaryTree
{
private:

	Node * root;

public:

	BinaryTree()
	{
		root = nullptr;
	}

	Node *GetRoot()
	{
		return root;
	}

	void SetRoot(Node *r)
	{
		root = r;
	}

	void Insert(Node *tree, Node *n)
	{
		if (root == nullptr)
		{
			root = n;
		}
		else if (n->GetData() < tree->GetData())
		{
			if (tree->GetLeft() == nullptr)
				tree->SetLeft(n);
			else
				Insert(tree->GetLeft(), n);
		}
		else
		{
			if (tree->GetRight() == nullptr)
				tree->SetRight(n);
			else
				Insert(tree->GetRight(), n);
		}
	}

	bool Search(Node* tree, std::string data)
	{
		while (tree != nullptr)
		{
			if (data > tree->GetData())
				tree = tree->GetRight();

			else if (data < tree->GetData())
				tree = tree->GetLeft();
			else
				return true;
		}

		return false;
	}

	Node *DeleteNode(Node *tree, std::string data)
	{
		if (tree == nullptr)
		{
			return tree;
		}

		if (data < tree->GetData())
		{
			tree->SetLeft(DeleteNode(tree->GetLeft(), data));
		}
		else if (data > tree->GetData())
		{
			tree->SetRight(DeleteNode(tree->GetRight(), data));
		}
		else
		{
			if (tree->GetLeft() == nullptr && tree->GetRight() == nullptr)
			{
				delete tree;
				tree = nullptr;
			}
			else if (tree->GetLeft() == nullptr)
			{
				Node *temp = tree;
				tree = tree->GetRight();
				delete temp;
			}
			else if (tree->GetRight() == nullptr)
			{
				Node *temp = tree;
				tree = tree->GetLeft();
				delete temp;
			}
			else
			{
				auto minNode = [&](Node *x) -> Node* { auto n = x; while (n->GetLeft() != nullptr) n = n->GetLeft(); return n; };

				Node *temp = minNode(tree->GetRight());

				tree->SetData(temp->GetData());

				tree->SetRight(DeleteNode(tree->GetRight(), temp->GetData()));
			}
		}

		return tree;
	}

	void Inorder(Node *tree)
	{
		if (tree == nullptr)
		{
			return;
		}
		else
		{
			Inorder(tree->GetLeft());
			std::cout << tree->GetData() << "\n";
			Inorder(tree->GetRight());
		}
	}
};

#endif