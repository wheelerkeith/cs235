/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype
#include "bnode.h"
#include "vector.h"
#include "pair.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct HuffmanTree
{
public:
	HuffmanTree() : tree(NULL) {};
	HuffmanTree(BinaryNode<Pair<const int, string>>* node) : tree(node) {};
	HuffmanTree(Pair<int, string> data)
	{
		BinaryNode<Pair<int, string> >* node = new BinaryNode<Pair<int, string> >;
		node->data = data;
	}

	BinaryNode<Pair<int, string> >* tree;
};

void printCode(HuffmanTree top, string str)
{
	if (!top.tree)
		return;

	if (top.tree->data.second != "\0")
	{
		cout << top.tree->data.second << " = "
			<< str << endl;
	}

	printCode(top.tree->pLeft, str + "0");
	printCode(top.tree->pRight, str + "1");
}

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(string filename)
{
	Vector<Pair<int, string> > data;
	string c;
	int w;

	ifstream fin(filename.c_str());
	while (fin)
	{
		fin >> c >> w;
		Pair<int, string> pair(w, c);
		data.push_back(pair);
	}

	Vector<HuffmanTree> nodes;

	for (int i = 0; i < data.size(); i++)
	{
		HuffmanTree tree(data[i]);
		nodes.push_back(tree);
	}

	// create dummy value that will be bigger than all frequencies in smallest vector
	Pair<int, string> one(1, string());
	HuffmanTree smallest[2];
	// used to keep track of left-most position
	int leftmost;
	int rightmost;

	while (nodes.size() != 1)
	{
		smallest[0].tree->data = one;
		smallest[1].tree->data = one;
		leftmost = -1;
		rightmost = -1;

		// find two smallest nodes
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].tree->data < smallest[0].tree->data)
			{
				HuffmanTree temp = smallest[0];
				smallest[0] = nodes[i];
				smallest[1] = temp;
			}
			else if (nodes[i].tree->data < smallest[1].tree->data)
			{
				smallest[1] = nodes[i];
			}
		}

		// find leftmost tree
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].tree->data == smallest[0].tree->data ||
				nodes[i].tree->data == smallest[1].tree->data)
			{
				leftmost = i;
				break;
			}
		}

		// find rightmost tree
		for (int i = nodes.size() - 1; i >= 0; i--)
		{
			if (nodes[i].tree->data == smallest[0].tree->data ||
				nodes[i].tree->data == smallest[1].tree->data)
			{
				rightmost = i;
				break;
			}
		}

		// new weight of the two combined.
		int nWeight = smallest[0].tree->data.first + smallest[1].tree->data.first;
		Pair<int, string> p1(nWeight, string());
		HuffmanTree add(p1);
		add.tree->addLeft(smallest[0].tree);
		add.tree->addRight(smallest[1].tree);

		Vector<HuffmanTree> temp;
		for (int i = 0; i < nodes.size(); i++)
		{
			if (i != rightmost)
				temp.push_back(nodes[i]);
		}

		nodes.clear();
		nodes = temp;
		nodes[leftmost] = add;
	}

	printCode(nodes[0], "");
}
