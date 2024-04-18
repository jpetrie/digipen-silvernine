/*!
	@file		CQuadTree.h
	@author	Scott Smith
	@date		November 18, 2003

	@brief	Interface file for a quadtree data structure
______________________________________________________________________________*/

#include "CQuadTree.h"
#include "CGraphicsObject.h"

/*
	QNode::QNode()
	@param	xmin	minimum x value
	@param	xmax	maximum x value
	@param	ymin	minimum y value
	@param	ymax	maximum y value
	
	@brief	construct a quadtree node.
______________________________________________________________________________*/
QNode::QNode(int xmin_, int xmax_, int ymin_, int ymax_)
		:xmin(xmin_), xmax(xmax_), ymin(ymin_), ymax(ymax_),
		top_left(0), top_right(0), bottom_left(0), bottom_right(0)
{
	testx = xmin + (xmax - xmin)/2;
	testy = ymin + (ymax - ymin)/2;
}
/*
	CQuadTree::CQuadTree()
	@param	xmin			minimum x value
	@param	xmax			maximum x value
	@param	ymin			minimum y value
	@param	ymax			maximum y value
	@param	max_depth	The maximum desired depth of the quadtree.
	
	@brief	construct a quadtree. 
______________________________________________________________________________*/
CQuadTree::CQuadTree(int xmin, int xmax, int ymin, int ymax, int max_depth)
:Tree(0), resolution(max_depth)
{
	Tree = new QNode(xmin, xmax, ymin, ymax);
	Tree->depth = 1;
}
/*
	CQuadTree::~CQuadTree()
	@brief	Free the tree nodes.
______________________________________________________________________________*/
CQuadTree::~CQuadTree()
{
	FreeTree(Tree);	
}
/*
	CQuadTree::BuildTree()
	@brief	Build the tree using a recursive helper function.
______________________________________________________________________________*/
void CQuadTree::BuildTree(void)
{
	//if(Tree)
	//  FreeTree(Tree);
	BuildQuadTree(Tree);
}
/*
	CQuadTree::BuildQuadTree()
	@param	tree	A pointer to a tree/subtree

	@brief	Recursively builds a quadtree until a max depth is reached.
______________________________________________________________________________*/
void CQuadTree::BuildQuadTree(QNode *tree)
{
	// if we have reached the desired depth
	if(tree->depth == resolution)
		return;

  // build the top_left node
	tree->top_left = NewQuadTreeNode(tree->xmin, tree->testx, tree->ymax, tree->testy, tree->depth + 1);
	BuildQuadTree(tree->top_left);
	// build top right node
	tree->top_right = NewQuadTreeNode(tree->testx, tree->xmax, tree->ymax, tree->testy, tree->depth + 1);
	BuildQuadTree(tree->top_right);
	// build bottom left node
	tree->bottom_left = NewQuadTreeNode(tree->xmin, tree->testx, tree->testy, tree->ymin, tree->depth + 1);
	BuildQuadTree(tree->bottom_left);
	// build bottom right node
	tree->bottom_right = NewQuadTreeNode(tree->testx, tree->xmax, tree->testy, tree->ymin, tree->depth + 1);
	BuildQuadTree(tree->bottom_right);
}
/*
	CQuadTree::FreeTree()
	@param	tree	A pointer to a tree/subtree

	@brief	Recursively frees the nodes of a quadtree.
______________________________________________________________________________*/
void CQuadTree::FreeTree(QNode *tree)
{
	if(!tree)
		return;
	FreeTree(tree->top_left);
	FreeTree(tree->top_right);
	FreeTree(tree->bottom_left);
	FreeTree(tree->bottom_right);
	delete tree;
}
/*
	CQuadTree::TestPoint()
	@param	x The x location to test
	@param	y	The y location to test
	@return The node of the quadtree which most closely bounds the point 
					according to a specified depth.

	@brief	Finds the region of the map in which a point is contained.
______________________________________________________________________________*/
QNode *CQuadTree::TestPoint(int x, int y)
{
	QNode *t = Tree;

	while(t->depth != resolution)
	{
		if(x < t->testx && y < t->testy)
			t = t->bottom_left;
		else if(x < t->testx && y >= t->testy)
			t = t->top_left;
		else if(x >= t->testx && y < t->testy)
			t = t->bottom_right;
		else if(x >= t->testx && y >= t->testy)
			t = t->top_right;
	}
	return t;
}
/*
______________________________________________________________________________*/
QNode *CQuadTree::NewQuadTreeNode(int xl, int xr, int yt, int yb, int d)
{
	QNode *t = new QNode(xl, xr, yb, yt);
	t->depth = d;
	NodeWidth = xr - xl;
	NodeHeight = yt - yb;
	return t;
}

void CQuadTree::AddObject(QNode *tree, void *o)	// static images
{
	tree->Objects.push_back(o);
}

void CQuadTree::SortTree( bool(*sort)(void*, void*) )
{
	InternalSort(Tree, sort);
}
void CQuadTree::InternalSort( QNode *tree, bool(*sort)(void*, void*) )
{
	if(tree->bottom_left == 0 && tree->bottom_right == 0 &&
		tree->top_left == 0 && tree->top_right == 0)
	{
		std::sort(tree->Objects.begin(), tree->Objects.end(), sort);
		return;
	};

	if(tree->bottom_left)
		InternalSort(tree->bottom_left, sort);
	if(tree->bottom_right)
		InternalSort(tree->bottom_right, sort);
	if(tree->top_left)
		InternalSort(tree->top_left, sort);
	if(tree->top_right)
		InternalSort(tree->top_right, sort);

}




