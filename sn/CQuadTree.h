/*!
	@file		CQuadTree.h
	@author	Scott Smith
	@date		November 18, 2003

	@brief	Interface file for a quadtree data structure
______________________________________________________________________________*/

#ifndef __CQUADTREE_H__
#define __CQUADTREE_H__

#include <vector>
class CGraphicsObject;
/*!
	@struct	QNode
______________________________________________________________________________*/
struct QNode
{
	QNode(int xmin_ = 0.f, int xmax_ = 0.f, int ymin_ = 0.f, int ymax_ = 0.f);
	
	int testx, testy;								// the partition lines
	int xmin, xmax, ymin, ymax;					// the boundaries of the node
	int depth;										// current tree depth
	QNode *top_left;								// points to the upper left quadrant
	QNode *top_right;								// points to the upper right quadrant
	QNode *bottom_left;							// points to the lower left quadrant
	QNode *bottom_right;							// points to the lower right quadrant
	std::vector<void *>	Objects;		// static objects visible in the node
	
};

/*!
	@class CQuadTree
______________________________________________________________________________*/
class CQuadTree
{
public:
	CQuadTree(int xmin = 0.f, int xmax = 0.f, int ymin = 0.f, int ymax = 0.f, int max_depth = 4);
	~CQuadTree();

	void BuildTree(void);		// construct the quadtree
	QNode *TestPoint(int x, int y);
	void AddObject(QNode *Tree, void *o);	// static images
	int GetXStep(void) const { return NodeWidth; }
	int GetYStep(void) const { return NodeHeight; }
	void SortTree( bool(*sort)(void*, void*) );
	
private:
	// data members
	QNode *Tree;
	/*
		maximum 'depth' of the tree.  
		Root == 1 level, partition size == mapsize / 2^n at depth n.
	*/
	int resolution;			 
	int NodeWidth;
	int NodeHeight;
	// private member functions
	void FreeTree(QNode *tree);
	QNode *NewQuadTreeNode(int xl, int xr, int yt, int yb, int d);
	void BuildQuadTree(QNode *tree);
	void CQuadTree::InternalSort( QNode *tree, bool(*sort)(void*, void*) );

};

#endif