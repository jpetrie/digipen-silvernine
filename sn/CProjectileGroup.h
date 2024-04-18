/*!
	@file		CProjectileGroup.h
	@author	Scott Smith
	@date		Novemeber 26, 2003

	@brief	Interface to a projectile group
______________________________________________________________________________*/

#ifndef	__C_PROJECTILE_GROUP_H__
#define	__C_PROJECTILE_GROUP_H__

#include "CProjectile.h"
#include "CTag_pgrp.h"

class CUnit;
/*!
	@@class	CProjectileGroup
	@@brief	Provides a means of grouping projectiles with like beahavior.
______________________________________________________________________________*/
class CProjectileGroup
{
public:
	// construct the group

	CProjectileGroup(const std::string &tag, CUnit* owner, float x, float y, float destx, float desty, bool isammo = false);
	// delete the group
	~CProjectileGroup(); 
	
	void Update(void);
	void SetTarget(CUnit* target) { mTarget = target; }
	void SetOwner(CUnit *owner) { mOwner = owner; }
	CProjectile* operator[](int index) { return mGroup[index]; }
	int Count(void)	{ return mCount; }
	std::vector<CProjectile*>	mGroup;
protected:
		void LoadFromTag(const std::string &tag);
private:
	//CProjectile **mGroup;								///<	The Array of projectiles
	
	int						mCount;								///<	The number of projectiles in the group
	int						mType;								///<	The damage type
	double				mAngleBetween;				///<	The angle between projectiles
	double				mAngleTotal;					///<	The total spread angle
	int						mDelay;								///<	Frame delay before seeking
	int						mCurrDelay;						///<	Frames passed since launch
	CUnit*			mTarget;							///<	The targets for seeking
	CUnit*			mOwner;								///<	The spawning object
	bool			mIsAmmo;
  std::vector<std::string> mTags;			///<	A list of tag files for the projectile group
};

#endif