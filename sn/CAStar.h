/*! =========================================================================

      @file    CAStarNode.h
      @brief   Provides an A* search node class.
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_ASTAR_H_
#define _C_ASTAR_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CAStarNode.h"
#include "CAStarStorage.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_,typename S_ = CAStarListStorage< N_,M_,B_ > >
class CAStar
/*! @brief A* search class.

    @param N_  User node type. Must conform to the "Node Type" model.
    @param M_  User map type. Must conform to the "Map Type" model.
    @param B_  User behavior type. Must conform to the "Behavior Type" model.
    @param S_  Storage type. Must conform to the "Storage Type" model.
               Defaults to CAStarListStorage< N_ >.
*/
{
  public:
    // ct and dt
     CAStar(void);
    ~CAStar();

    // pathing
    bool GeneratePathSync(M_ &map,B_ &behavior,N_ &start,N_ &goal,std::vector< N_ > &path);


  private:
    // disabled
    CAStar(const CAStar &s);
    CAStar& operator=(const CAStar &rhs);

    // list management
    void nOpenNode(N_ &n,CAStarNode< N_,B_ > *p,const B_ &behavior);
    void nCloseNode(CAStarNode< N_,B_ > *n);


    // data members
    S_  mStorage;
};


/*                                                           member functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_,typename S_ >
CAStar< N_,M_,B_,S_ >::CAStar(void)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_,typename S_ >
CAStar< N_,M_,B_,S_ >::~CAStar(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_,typename S_ >
bool CAStar< N_,M_,B_,S_ >::GeneratePathSync(M_ &map,B_ &behavior,N_ &start,N_ &goal,std::vector< N_ > &path)
/*! @brief Runs a synchronous A* search.

    GeneratePathSync() performs an A* search synchronously; the entire search
    is completed before the function returns.

    A path, if one exists, is found on the specified `map` from the `start`
    node to the `goal` node. The resulting path is returned through the `path`
    parameter.

    @param map    The search space.
    @param start  The start node.
    @param goal   The goal node.
    @param path   On return, contains the path found by the search, as a list
                  of nodes. The existing contents of the list is always lost.

    @return
    True if a path was found, false otherwise. If GeneratePathSync() returns
    false, the `path` parameter is an empty list.
*/
{
bool                  tFound = false;
CAStarNode< N_,B_ >   tNode(start);
CAStarNode< N_,B_ >  *tCurrent;

  // Clear storage between searches.
  mStorage.Clear();

  // Open the start node; make it current.
  mStorage.MoveToOpen(tNode);
  tCurrent = mStorage.GetBest(map,behavior,goal);

  // Loop until we find a path or exhaust every possibility.
  while(!mStorage.IsOpenEmpty())
  {
  std::vector< N_ >  tChildren;

    // If the current state is the goal, stop.
    tFound = tCurrent->IsEquivTo(goal);
    if(tFound)
      break;

    // Otherwise, continue by expanding its child nodes...
    map.AStarGetChildren(behavior,tCurrent->GetData(),tChildren);
    for(unsigned int i = 0; i < tChildren.size(); ++i)
      nOpenNode(tChildren[i],tCurrent,behavior);

    // ...closing the current node...
    nCloseNode(tCurrent);

    // ...and making the best open node current.
    tCurrent = mStorage.GetBest(map,behavior,goal);
  }

  // If we found a path, put it into `path`.
  if(tFound)
  {
    while(tCurrent != 0)
    {
      path.push_back(tCurrent->GetData());
      tCurrent = tCurrent->GetPrev();
    }
  }

  return (tFound);
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_,typename S_ >
void CAStar< N_,M_,B_,S_ >::nOpenNode(N_ &n,CAStarNode< N_,B_ > *p,const B_ &behavior)
/*! @brief Opens an A* node for possible examination.

    This function will add a node described by `n` to the open list if `n` is
    not already in the closed list. If `n` already exists in the open list, but
    as the result of a more expensive path than the one currently being
    explored, the bad path is broken and `n` is updated to belong to the new
    search path.

    @param n  The new user node to open.
    @param p  The parent CAStarNode of the new node.
*/
{
int  tIdx;

  // If the node is in the closed list, abort.
  tIdx = mStorage.FindInClosed(n);
  if(tIdx != -1)
    return;

  // If the node is in the open list...
  tIdx = mStorage.FindInOpen(n);
  //tIdx = mOpen.FindInOpen(n);
  if(tIdx != -1)
  {
 // CAStarNode< N_ > *tNode = mStorage.GetNode(tIdx);
  CAStarNode< N_,B_ > *tNode = mStorage.GetOpen(tIdx);

    // ...and if it's cheaper to get there through the new parent,
    // update it.
    if(p->GetPathCost(behavior) + n.AStarCost(behavior) < tNode->GetPathCost(behavior))
      tNode->SetPrev(p);
  }
  // Otherwise, set it up and add it.
  else
  {
  CAStarNode< N_,B_ >  tNode(n,p);
  
    mStorage.MoveToOpen(tNode);
  }
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_,typename S_ >
void CAStar< N_,M_,B_,S_ >::nCloseNode(CAStarNode< N_,B_ > *n)
/*! @brief Closes an A* node.

    This function will close the node described by `n`; removing it from the
    open list and adding it to the closed list.

    @param n  The node to close.
*/
{
  // Remove it from the open list, add it to the closed list.
  mStorage.MoveToClosed(*n);
}


#endif
