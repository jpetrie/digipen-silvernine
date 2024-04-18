/*! =========================================================================

      @file    CAStarNode.h
      @brief   Provides an A* search node class.

      (c) 2003 Scientific Ninja Studios

    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_ASTARNODE_H_
#define _C_ASTARNODE_H_


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
class CAStarNode
/*! @brief A* search node class.

    A search node is a point within the A* search space, described by its cost
    and some additional user-defined properties (that take the form of the
    template parameter N_).

    The purpose of the CAStarNode class is to facilitate the creation of
    custom A* storage classes; the casual end-user of the CAStar class who can
    make use of the default storage classes doesn't need to utilize CAStarNode
    at all.

    @param N_  User node type. Must conform to the "Node Type" model described
               in the documentation for the CAStar class.
*/
{
  public:
    // ct and dt
    CAStarNode(const N_ &n);
    CAStarNode(const N_ &n,CAStarNode *p);
    CAStarNode(const CAStarNode &s);
    ~CAStarNode(void);

    // = operator
    CAStarNode& operator=(const CAStarNode &rhs);

    // accessors
    inline const N_&   GetData(void);
    inline CAStarNode* GetPrev(void);
    inline int         GetStepCost(const B_ &behavior);
    inline int         GetPathCost(const B_ &behavior);
    inline int         GetDistance(const B_ &behavior,const N_ &goal);

    // manipulators
    inline void SetPrev(CAStarNode *p) { mPrev = p; }

    // equivalence
    inline bool IsEquivTo(const N_ &n);
    inline bool IsEquivTo(const CAStarNode &n);


  private:
    // member data
    N_           mData;  // User node.
    CAStarNode  *mPrev;  // Previous node in search path.
};


/*                                                           member functions
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
CAStarNode< N_,B_ >::CAStarNode(const N_ &n)
/*! @brief Constructor.

    @param n  User node data.
*/
: mData(n),
  mPrev(0)
{
}


/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
CAStarNode< N_,B_ >::CAStarNode(const N_ &n,CAStarNode< N_,B_ > *p)
/*! @brief Constructor.

    @param n  User node data.
    @param p  Parent node.
*/
: mData(n),
  mPrev(p)
{
}


/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
CAStarNode< N_,B_ >::CAStarNode(const CAStarNode< N_,B_ > &s)
/*! @brief Copy constructor.

    The copy of `s` to the invoking object is shallow.

    @param s  CAStarNode object to copy.
*/
: mData(s.mData),
  mPrev(s.mPrev)
{
}


/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
CAStarNode< N_,B_ >::~CAStarNode(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
CAStarNode< N_,B_ >& CAStarNode< N_,B_ >::operator=(const CAStarNode< N_,B_ > &rhs)
/*! @brief = operator overload.

    The copy of `rhs` to the invoking object is shallow.

    @param rhs  Right-hand side of operation.
*/
{
  mData = rhs.mData;
  mPrev = rhs.mPrev;
  return (*this);
}


/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
inline const N_& CAStarNode< N_,B_ >::GetData(void)
/*! @brief Retrieves the user node data of the invoking object..

    @return
    A reference to the user node data.
*/
{
  return (mData);
}


/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
inline CAStarNode< N_,B_ >* CAStarNode< N_,B_ >::GetPrev(void)
/*! @brief Retrieves the previous node in the search path.

    @return
    A pointer to the previous CAStarNode object in the invoking node's path.
*/
{
  return (mPrev);
}



/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
inline int CAStarNode< N_,B_ >::GetStepCost(const B_ &behavior)
/*! @brief Retrieves the single-step cost of the invoking node.

    @return
    The movement cost or penalty required to move across this search node.
*/
{
  return (mData.AStarCost(behavior));
}


/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
inline int CAStarNode< N_,B_ >::GetPathCost(const B_ &behavior)
/*! @brief Retrieves the full-path cost of the invoking node.

    @return
    The movement cost or penalty required to move across this search node, as
    well as all the search nodes that preceded it, back to the original node.
*/
{
  if(0 == mPrev)
    return (mData.AStarCost(behavior));
  else
    return (mData.AStarCost(behavior) + mPrev->GetPathCost(behavior));
}


/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
inline int CAStarNode< N_,B_ >::GetDistance(const B_ &behavior,const N_ &goal)
/*! @brief Retrieves the heuristic distance to the specified goal node.

    @param goal  Goal node to compute distance between.

    @return
    The "Manhatten Distance" between the invoking node and the specified goal
    node.
*/
{
  return (abs(goal.AStarDist(behavior)));
}


/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
inline bool CAStarNode< N_,B_ >::IsEquivTo(const N_ &n)
/*! @brief Determines if the A* node `n` is equivalent to the invoking node.

    @param n  The user node to test.
    
    @return
    True if the node's are equivalent (represent the same space or state),
    otherwise false.
*/
{
  return (mData.AStarEquiv(n));
}


/*  _________________________________________________________________________ */
template< typename N_,typename B_ >
inline bool CAStarNode< N_,B_ >::IsEquivTo(const CAStarNode< N_,B_ > &n)
/*! @brief Determines if the A* node `n` is equivalent to the invoking node.

    @param n  The CAStarNode to test.
    
    @return
    True if the node's are equivalent (represent the same space or state),
    otherwise false.
*/
{
  if(0 == n)
    return (false);

  return (mData.AStarEquiv(n->mData));
}


#endif /* _C_ASTARNODE_H_ */