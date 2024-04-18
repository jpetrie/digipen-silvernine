/*!
	@@file		CProjectileGroup.cpp
	@@author	Scott Smith
	@@date		December 1, 2003

	@@brief	Implementation of a projectile group
______________________________________________________________________________*/
#include "CProjectileGroup.h"
#include "CEvent_CreateProjectile.h"
#include "CUnit.h"

/*!
______________________________________________________________________________*/

CProjectileGroup::CProjectileGroup(const std::string &tag, CUnit* owner,
									float x, float y, float destx, float desty, bool isammo)
:mCount(1), mGroup(0), mAngleBetween(0.0), mAngleTotal(0.0), mType(0), mDelay(30),
	mCurrDelay(0), mOwner(owner), mIsAmmo(isammo)
{
	
	
	if(tag.length() > 0)
	{
		LoadFromTag(tag);
	}
	

	// create distinct copies of each projectile
	for(int i = 0; i < mCount; ++i)
	{
		CProjectile *pr = new CProjectile(mTags[i], x, y, destx, desty, mIsAmmo);
		pr->SetOwner(mOwner);
		pr->Group(this);
		if(mIsAmmo)
			pr->Speed(0.f);
		mGroup.push_back(pr);
	}

	double base_angle = atan((desty - y)/(destx - x)) * (180.0/3.141592);//(mOwner ? mOwner->Facing() : 0.0) * 45.0;
	mAngleBetween = mAngleTotal / (double)mCount;
	base_angle -= (((double)mCount - 1.0)/2.0) * mAngleBetween;

	// setup for different types
	if(mType & kProjectileGroupType_Fan)
	{
		for(int i = 0; i < mCount; ++i)
		{
			mGroup[i]->SetDest(cos( (base_angle + i * mAngleBetween) * (3.141592/180.0) ), sin( (base_angle + i * mAngleBetween) * (3.141592/180.0)));
		}
	}
	if(mType & kProjectileGroupType_Random)
	{
		
		for(int i = 0; i < mCount; ++i)
		{
			int rand1 = (rand() % 2);
			int rand2 = (rand() % 2);
			if(rand1 == 0)
				rand1 = -1;
			if(rand2 == 0)
				rand2 = -1;
			mGroup[i]->SetDest((float)rand1 * nsl::randfloat(0.f, 1.f), (float)rand2 * nsl::randfloat(0.f, 1.f));
			
		}
	}
	
}
/*!
______________________________________________________________________________*/
CProjectileGroup::~CProjectileGroup() 
{
	//for(int i = 0; i < mCount; ++i)
	//	delete mGroup[i];
	
	//delete[] mGroup;
}
/*!
______________________________________________________________________________*/
void CProjectileGroup::LoadFromTag(const std::string &tag)
{
	CTag_pgrp *tTag = dcast< CTag_pgrp* >(CTagMgr->Unarchive(kTag_pgrp,tag));
	
	mTags = tTag->mTags;
	mCount = tTag->mCount;
	mType = tTag->mType;
	mAngleTotal = tTag->mSpread;
	
	CTagMgr->Release(tTag);

}
/*!
______________________________________________________________________________*/
void CProjectileGroup::Update(void)
{
	if((mType & kProjectileGroupType_Seek) && (mCurrDelay < mDelay))
	{
		for(int i = 0; i < mCount; ++i)
		{
			if(mTarget)
				mGroup[i]->SetDest(mTarget->X(), mTarget->Y());
		}
	}
	for(int i = 0; i < mCount; ++i)
	{
		mGroup[i]->Update();
	}
	
	++mCurrDelay;
}

