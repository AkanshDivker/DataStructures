/**
	Simple Data Structures
	RedBlackTree.h

	@author Akansh Divker
	@version 1.0
*/

#pragma once

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <string>

enum Color
{
	BLACK,
	RED
};

class Node
{
private:
	int key;
	std::string data;
	Node *left;
	Node *right;
	Node *parent;
	Color color;

public:

	Node(const std::string& dataVal, int keyVal) : left(nullptr), right(nullptr), parent(nullptr), color(BLACK), data(dataVal), key(keyVal) {}

	int GetKey()
	{
		return key;
	}

	std::string GetData()
	{
		return data;
	}

	Node* GetLeft()
	{
		return left;
	}

	Node* GetRight()
	{
		return right;
	}

	Node* GetParent()
	{
		return parent;
	}

	Color GetColor()
	{
		return color;
	}

	void SetKey(int value)
	{
		key = value;
	}

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

	void SetParent(Node *parentPtr)
	{
		parent = parentPtr;
	}

	void SetColor(Color value)
	{
		color = value;
	}
};

class RedBlackTree
{
private:

	Node * nil;
	Node *root;

public:

	/**
		Constructor for RedBlackTree structure. Initializes nil and root.
	*/
	RedBlackTree()
	{
		nil = new Node("", -1);

		nil->SetLeft(nil);
		nil->SetRight(nil);

		root = nil;
	}

	Node *GetRoot()
	{
		return root;
	}

	void RotateLeft(Node *x)
	{
		//Set y
		Node *y = x->GetRight();

		// Turn y's left subtree into x's right subtree
		x->SetRight(y->GetLeft());

		if (x->GetRight() != this->nil)
			x->GetRight()->SetParent(x);

		// Link x's parent to y
		y->SetParent(x->GetParent());

		if (x->GetParent() == this->nil)
			this->root = y;
		else if (x == x->GetParent()->GetLeft())
			x->GetParent()->SetLeft(y);
		else
			x->GetParent()->SetRight(y);

		// Put x on y's left
		y->SetLeft(x);
		x->SetParent(y);
	}

	void RotateRight(Node *x)
	{
		// Set y
		Node *y = x->GetLeft();

		// Turn y's right subtree into x's left subtree
		x->SetLeft(y->GetRight());

		if (x->GetLeft() != this->nil)
			x->GetLeft()->SetParent(x);

		// Link x's parent to y
		y->SetParent(x->GetParent());

		if (x->GetParent() == this->nil)
			this->root = y;
		else if (x == x->GetParent()->GetRight())
			x->GetParent()->SetRight(y);
		else
			x->GetParent()->SetRight(y);

		// Put x on y's right
		y->SetRight(x);
		x->SetParent(y);
	}

	void Insert(Node *z)
	{
		Node *y = this->nil;
		Node *x = this->root;

		while (x != this->nil)
		{
			y = x;

			if (z->GetKey() < x->GetKey())
				x = x->GetLeft();
			else
				x = x->GetRight();
		}

		z->SetParent(y);

		if (y == this->nil)
			this->root = z;
		else if (z->GetKey() < y->GetKey())
			y->SetLeft(z);
		else
			y->SetRight(z);

		z->SetLeft(this->nil);
		z->SetRight(this->nil);
		z->SetColor(RED);

		InsertFixup(z);
	}

	void InsertFixup(Node *z)
	{
		Node *y = nil;

		while (z->GetParent()->GetColor() == RED)
		{
			if (z->GetParent() == z->GetParent()->GetParent()->GetLeft())
			{
				y = z->GetParent()->GetParent()->GetRight();

				if (y->GetColor() == RED)
				{
					// CASE 1 - RED UNCLE
					z->GetParent()->SetColor(BLACK);
					y->SetColor(BLACK);
					z->GetParent()->GetParent()->SetColor(RED);
					z = z->GetParent()->GetParent();
				}
				else if (z == z->GetParent()->GetRight())
				{
					// CASE 2 - BLACK UNCLE

					z = z->GetParent();
					RotateLeft(z);

					// CASE 3 - BLACK UNCLE, LEFT CHILD
					z->GetParent()->SetColor(BLACK);
					z->GetParent()->GetParent()->SetColor(RED);
					RotateRight(z->GetParent()->GetParent());
				}
			}
			else
			{
				y = z->GetParent()->GetParent()->GetLeft();

				if (y->GetColor() == RED)
				{
					// CASE 1 - RED UNCLE
					z->GetParent()->SetColor(BLACK);
					y->SetColor(BLACK);
					z->GetParent()->GetParent()->SetColor(RED);
					z = z->GetParent()->GetParent();
				}
				else if (z == z->GetParent()->GetLeft())
				{
					// CASE 2 - BLACK UNCLE
					z = z->GetParent();
					RotateRight(z);

					// CASE 3 - BLACK UNCLE, LEFT CHILD
					z->GetParent()->SetColor(BLACK);
					z->GetParent()->GetParent()->SetColor(RED);
					RotateLeft(z->GetParent()->GetParent());
				}
			}
		}

		this->root->SetColor(BLACK);
	}

	Node *Minimum(Node *x)
	{
		Node *temp = x;

		while (temp->GetLeft() != nil)
			temp = temp->GetLeft();

		return temp;
	}

	Node *Maximum(Node *x)
	{
		Node *temp = x;

		while (temp->GetRight() != nil)
			temp = temp->GetRight();

		return temp;
	}

	/**
		Finds the predecessor and successor of a given key value for the tree.
	*/
	void GetPredSuc(Node* root, Node*& pre, Node*& suc, int key)
	{
		// Base case
		if (root == this->nil)  return;

		// If key is present at root
		if (root->GetKey() == key)
		{
			// The maximum value in left subtree is predecessor
			if (root->GetLeft() != this->nil)
			{
				Node* tmp = root->GetLeft();
				while (tmp->GetRight())
					tmp = tmp->GetLeft();
				pre = tmp;
			}

			// The minimum value in right subtree is successor
			if (root->GetRight() != this->nil)
			{
				Node* tmp = root->GetRight();
				while (tmp->GetLeft())
					tmp = tmp->GetLeft();
				suc = tmp;
			}
			return;
		}

		// If key is smaller than root's key, go to left subtree
		if (root->GetKey() > key)
		{
			suc = root;
			GetPredSuc(root->GetLeft(), pre, suc, key);
		}
		else // Go to right subtree
		{
			pre = root;
			GetPredSuc(root->GetLeft(), pre, suc, key);
		}
	}

	void Transplant(Node *u, Node *v)
	{
		if (u->GetParent() == nil)
			this->root = v;
		else if (u == u->GetParent()->GetLeft())
			u->GetParent()->SetLeft(v);
		else
			u->GetParent()->SetRight(v);

		if (v != nil)
			v->SetParent(u->GetParent());
	}

	Node *Search(std::string data)
	{
		Node *temp = this->root;

		while (temp != this->nil)
		{
			if (data > temp->GetData())
				temp = temp->GetRight();
			else if (data < temp->GetData())
				temp = temp->GetLeft();
			else
				return temp;
		}

		return nullptr;
	}

	Node *Search(int key)
	{
		Node *temp = this->root;

		while (temp != this->nil)
		{
			if (key > temp->GetKey())
				temp = temp->GetRight();
			else if (key < temp->GetKey())
				temp = temp->GetLeft();
			else
				return temp;
		}

		return nullptr;
	}

	void RBDelete(Node *z)
	{
		Node *x = nil;
		Node *y = z;
		Color y_origColor = y->GetColor();

		if (z->GetLeft() == this->nil)
		{
			x = z->GetRight();
			Transplant(z, z->GetRight());
		}
		else if (z->GetRight() == this->nil)
		{
			x = z->GetLeft();
			Transplant(z, z->GetLeft());
		}
		else
		{
			y = Minimum(z->GetRight());
			y_origColor = y->GetColor();
			x = y->GetRight();

			if (y->GetParent() == z)
			{
				x->SetParent(y);
			}
			else
			{
				Transplant(y, y->GetRight());
				y->SetRight(z->GetRight());
				y->GetRight()->SetParent(y);
			}

			Transplant(z, y);

			y->SetLeft(z->GetLeft());
			y->GetLeft()->SetParent(y);
			y->SetColor(z->GetColor());
		}

		delete z;

		if (y_origColor == BLACK)
			DeleteFixup(x);
		else
			delete x;
	}

	void DeleteFixup(Node *x)
	{
		Node *w = this->nil;

		while (x != this->root && x->GetColor() == BLACK)
		{
			if (x == x->GetParent()->GetLeft())
			{
				w = x->GetParent()->GetRight();

				if (w->GetColor() == RED)
				{
					w->SetColor(BLACK);
					x->GetParent()->SetColor(RED);

					RotateLeft(x->GetParent());

					w = x->GetParent()->GetRight();
				}

				if (w->GetLeft()->GetColor() == BLACK && w->GetRight()->GetColor() == BLACK)
				{
					w->SetColor(RED);
					x = x->GetParent();
				}
				else if (w->GetRight()->GetColor() == BLACK)
				{
					w->GetLeft()->SetColor(BLACK);
					w->SetColor(RED);

					RotateRight(w);

					w = x->GetParent()->GetRight();

					w->SetColor(x->GetParent()->GetColor());
					x->GetParent()->SetColor(BLACK);
					w->GetRight()->SetColor(BLACK);

					RotateLeft(x->GetParent());

					x = this->root;
				}
			}
			else
			{
				w = x->GetParent()->GetLeft();

				if (w->GetColor() == RED)
				{
					w->SetColor(BLACK);
					x->GetParent()->SetColor(RED);

					RotateRight(x->GetParent());

					w = x->GetParent()->GetLeft();
				}

				if (w->GetRight()->GetColor() == BLACK && w->GetLeft()->GetColor() == BLACK)
				{
					w->SetColor(RED);
					x = x->GetParent();
				}
				else if (w->GetRight()->GetColor() == BLACK)
				{
					w->GetRight()->SetColor(BLACK);
					w->SetColor(RED);

					RotateLeft(w);

					w = x->GetParent()->GetLeft();

					w->SetColor(x->GetParent()->GetColor());
					x->GetParent()->SetColor(BLACK);
					w->GetLeft()->SetColor(BLACK);

					RotateRight(x->GetParent());

					x = this->root;
				}
			}
		}

		x->SetColor(BLACK);

		delete w;
		delete x;
	}

	void Inorder(Node *tree)
	{
		if (tree == this->nil)
			return;

		Inorder(tree->GetLeft());
		std::cout << tree->GetData() + "\n";
		Inorder(tree->GetRight());
	}
};

#endif 