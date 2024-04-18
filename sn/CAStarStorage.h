/*! =========================================================================

      @file    CAStarStorage
      @brief   Provides A* storage classes.

      (c) 2003 Scientific Ninja Studios

    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_ASTARSTORAGE_H_
#define _C_ASTARSTORAGE_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CAStarNode.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
class CAStarListStorage
/*! @brief A* linked-list storage class.

    The CAStarListStorage class provides node pool and open/closed list
    management for the A* search routine via a linked list.

    @param N_  User node type. Must conform to the "Node Type" model described
               in the documentation for the CAStar class.
    @param M_  User map type. Must conform to the "Map Type" model, described
               in the documentation for the CAStar class.
*/
{
  public:
    // ct and dt
    CAStarListStorage(void);
    ~CAStarListStorage(void);

    // accessors
    inline bool IsOpenEmpty(void);
    inline bool IsClosedEmpty(void);

    // manipulators
    void Clear(void);

    // insertion
    void MoveToOpen(CAStarNode< N_,B_ > &n);
    void MoveToClosed(CAStarNode< N_,B_ > &n);

    // search
    int FindInOpen(const N_ &n);
    int FindInClosed(const N_ &n);

    // retrieval
    inline CAStarNode< N_,B_ >* GetBest(const M_ &map,const B_ &behavior,const N_ &goal);
    inline CAStarNode< N_,B_ >* GetOpen(unsigned int key);
    inline CAStarNode< N_,B_ >* GetClosed(unsigned int key);


  private:
    // disabled
    CAStarListStorage(const CAStarListStorage &s);
    CAStarListStorage& operator=(const CAStarListStorage &rhs);
    
    // internal typedefs
    typedef typename std::vector< CAStarNode< N_,B_ >* >  TNodeList;
    typedef typename std::vector< CAStarNode< N_,B_ >* >::iterator               TNodeListItr;

    // member data
    TNodeList  mPool;    // Pointers to all nodes (has pointer ownership).
    TNodeList  mOpen;    // Pointers to open nodes.
    TNodeList  mClosed;  // Pointers to closed nodes.
};


/*                                                           member functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
CAStarListStorage< N_,M_,B_ >::CAStarListStorage(void)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
CAStarListStorage< N_,M_,B_ >::~CAStarListStorage(void)
/*! @brief Destructor.
*/
{
  Clear();
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
inline bool CAStarListStorage< N_,M_,B_ >::IsOpenEmpty(void)
/*! @brief Determines if the open list is empty.

    @return
    True if the open list is empty, false otherwise.
*/
{
  return (mOpen.empty());
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
inline bool CAStarListStorage< N_,M_,B_ >::IsClosedEmpty(void)
/*! @brief Determines if the closed list is empty.

    @return
    True if the closed list is empty, false otherwise.
*/
{
  return (mClosed.empty());
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
void CAStarListStorage< N_,M_,B_ >::Clear(void)
/*! @brief Clears lists and releases storage.
*/
{
  mOpen.erase(mOpen.begin(),mOpen.end());
  mClosed.erase(mClosed.begin(),mClosed.end());

  // Now clear the pool, actually deleting the allocated nodes.
  for(unsigned int i = 0; i < mPool.size(); ++i)
    delete mPool[i];

  // And remove the now-bogus entries from the pool.
  mPool.erase(mPool.begin(),mPool.end());
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
void CAStarListStorage< N_,M_,B_ >::MoveToOpen(CAStarNode< N_,B_ > &n)
/*! @brief Moves the specified node to the open list.

    If the node already exists in the open list, nothing happens; if the node
    exists in the closed list, it is removed from the closed list.

    @param n  The CAStarNode to add.
*/
{
int  tIdx;

  // Abort if node already in open list.
  tIdx = FindInOpen(n.GetData());
  if(tIdx != -1)
    return;

  // If the node is in the closed list...
  tIdx = FindInClosed(n.GetData());
  if(tIdx != -1)
  {
  TNodeListItr  tItr = mClosed.begin();

    // ...move it to the open list.
    mOpen.push_back(GetClosed(tIdx));

    // And then remove it from the closed list.
    for(int i = 0; i < tIdx; ++i)
      ++tItr;

    mClosed.erase(tItr);
  }
  // Otherwise, make a new node and put it on the open list.
  else
  {
  CAStarNode< N_,B_ > *tNewNode = new CAStarNode< N_,B_ >(n);

    mPool.push_back(tNewNode);
    mOpen.push_back(tNewNode);
  } 
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
void CAStarListStorage< N_,M_,B_ >::MoveToClosed(CAStarNode< N_,B_ > &n)
/*! @brief Moves the specified node to the closed list.

    If the node already exists in the closed list, nothing happens; if the node
    exists in the open list, it is removed from the open list.

    @param n  The CAStarNode to add.
*/
{
int  tIdx;

  // Abort if node already in closed list.
  tIdx = FindInClosed(n.GetData());
  if(tIdx != -1)
    return;

  // If the node is in the open list...
  tIdx = FindInOpen(n.GetData());
  if(tIdx != -1)
  {
  TNodeListItr  tItr = mOpen.begin();

    // ...move it to the closed list.
    mClosed.push_back(GetOpen(tIdx));

    // And then remove it from the open list.
    for(int i = 0; i < tIdx; ++i)
      ++tItr;

    mOpen.erase(tItr);
  }
  // Otherwise, make a new node and put it on the open list.
  else
  {
  CAStarNode< N_,B_ > *tNewNode = new CAStarNode< N_,B_ >(n);

    mPool.push_back(tNewNode);
    mClosed.push_back(tNewNode);
  } 
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
int CAStarListStorage< N_,M_,B_ >::FindInOpen(const N_ &n)
/*! @brief Retrieves a key for recovering a CAStarNode matching `n`.

    @return
    A key that can be used with the GetOpen() method to return a pointer to
    the CAStarNode object that matches the user node `n`. If no matching object
    is found, this function returns -1.
*/
{
int           tIdx = 0;
TNodeListItr  tItr = mOpen.begin();

  while(tItr != mOpen.end())
  {
    if((*tItr)->IsEquivTo(n))
      return (tIdx);

    ++tIdx;
    ++tItr;
  }

  // If we get here, we failed.
  return (-1);
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
int CAStarListStorage< N_,M_,B_ >::FindInClosed(const N_ &n)
/*! @brief Retrieves a key for recovering a CAStarNode matching `n`.

    @return
    A key that can be used with the GetClosed() method to return a pointer to
    the CAStarNode object that matches the user node `n`. If no matching object
    is found, this function returns -1.
*/
{
int           tIdx = 0;
TNodeListItr  tItr = mClosed.begin();

  while(tItr != mClosed.end())
  {
    if((*tItr)->IsEquivTo(n))
      return (tIdx);

    ++tIdx;
    ++tItr;
  }

  // If we get here, we failed.
  return (-1);
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
inline CAStarNode< N_,B_ >* CAStarListStorage< N_,M_,B_ >::GetBest(const M_ &/*map*/,const B_ &behavior,const N_ &goal)
/*! @brief Recovers the best (cheapest cost) CAStarNode in the open list.

    This function returns a pointer to the best CAStarNode in the open list,
    calculated using node path costs and a heuristic distance to the
    specified goal node (the distance is computed using the AStarDistance()
    method of the map class M_.

    @param map   Map used to in cheapest-cost calculations.
    @param goal  Goal node used in cheapest-cost calculations.

    @return
    A mutable pointer to the CAStarNode stored with the specified key value.
    If the key is invalid, the pointer will be NULL.
*/
{
TNodeListItr      tItr = mOpen.begin();
CAStarNode< N_,B_ > *tCurrent = mOpen[0];

  // Search the entire list.
  while(tItr != mOpen.end())
  {
    if((*tItr)->GetPathCost(behavior) + (*tItr)->GetData().AStarDist(behavior,goal) <
       tCurrent->GetPathCost(behavior) + tCurrent->GetData().AStarDist(behavior,goal))
    {
      tCurrent = (*tItr);
    }
    ++tItr;
  }

  return (tCurrent);
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
inline CAStarNode< N_,B_ >* CAStarListStorage< N_,M_,B_ >::GetOpen(unsigned int key)
/*! @brief Recovers the CAStarNode referenced by `key` in the open list.

    @return
    A mutable pointer to the CAStarNode stored with the specified key value.
    If the key is invalid, the pointer will be NULL.
*/
{
  // Stupid-proofing.
  if(key >= mOpen.size())
    return (0);

  return (mOpen[key]);
}


/*  _________________________________________________________________________ */
template< typename N_,typename M_,typename B_ >
inline CAStarNode< N_,B_ >* CAStarListStorage< N_,M_,B_ >::GetClosed(unsigned int key)
/*! @brief Recovers the CAStarNode referenced by `key` in the closed list

    @return
    A mutable pointer to the CAStarNode stored with the specified key value.
    If the key is invalid, the pointer will be NULL.
*/
{
  // Stupid-proofing.
  if(key >= mClosed.size())
    return (0);

  return (mClosed[key]);
}


#endif /* _C_ASTARSTORAGE_H_ */