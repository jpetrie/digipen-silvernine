/*!
	@file		CProjectile.cpp
	@author	Scott Smith
	@date		Novemeber 17, 2003

  @brief	Represents an in-game projectile.
______________________________________________________________________________*/

#include "precompiled.h"
#include "CProjectile.h"
#include "CArmy.h"
#include "CGameEngine.h"

#include "CEvent_DetonateProjectile.h"
#include "CEvent_DestroyProjectile.h"

/*!
______________________________________________________________________________*/
CProjectile::CProjectile(const std::string &tag, float x, float y, float destx, float desty, bool isammo)
:mSpeed(20.f), mHeight(50.f), mCurrLifetime(0), mMaxLifetime(30), mDetonate(false), mDestroy(false), mDead(false),
mAtRest(false), mOwner(0), mIsAmmo(isammo), mDetLifetime(20), mCurrDetLifetime(0), mHasContrails(true)
{
	mWorldX = x;
	mWorldY = y;
	
	mMaxContrailsLength = 10;
	if(mIsAmmo)
	{
		mHasContrails = false;

	}

	if(mHasContrails)
	{
		mContrailSprite = "sprcbull";
		CTagMgr->Cache(kTag_sprc, mContrailSprite.c_str());
	}

	if(tag.length() > 0)
	{
		LoadFromTag(tag);
    SetPosition(mWorldX,mWorldY);
  }
	mSprite->SetFrameDelay(0);
	if(mIsAmmo)
		mSprite->SetSequence(mAt_rest_seq_idx, 0);

	SetDest(destx, desty);
	
}
/*!
______________________________________________________________________________*/
CProjectile::~CProjectile()
{
	delete mSprite;
}
/*!
______________________________________________________________________________*/
void CProjectile::LoadFromTag(const std::string &tag)
{
	CTag_proj *tTag = dcast< CTag_proj* >(CTagMgr->Unarchive(kTag_proj,tag));

  if(0 != tTag)
  {
    // Initialize object data.
		CObject::LoadFromTag(tTag->obje_tag);
  
    
		mIn_flight_seq_idx	= tTag->in_flight_seq_idx;
		mAt_rest_seq_idx	= tTag->at_rest_seq_idx;
		mDet_seq_idx		= tTag->det_seq_idx;
		mDet_flags			= tTag->det_flags;
		mDam_flags			= tTag->dam_flags;
		mDamage_type		= tTag->damage_type;
		mDamage_radius_min	= tTag->damage_radius_min;
		mDamage_radius_max	= tTag->damage_radius_max;
		mDamage_min			= tTag->damage_min;
		mDamage_max			= tTag->damage_max;
		mDamage				= nsl::randfloat(tTag->damage_min, tTag->damage_max);
		mDamage_radius		= nsl::randfloat(tTag->damage_radius_min, tTag->damage_radius_max);
		mDam_fill_rate		= tTag->damage_radius_fill_rate;

		// And load sprite data.
		//FIXME same thing as in mech regarding sprc size
		mSprite = new CSprite(mWorldX, mWorldY , 64, 64, tTag->sprc_tag , true ,mIn_flight_seq_idx, 0, 0);

	}
  
  CTagMgr->Release(tTag);
}
/*!
______________________________________________________________________________*/
inline bool CProjectile::TestCollision(CObject *o)
{//return false;
	return(nsl::ellipse_in_ellipse(mWorldX + mRadius, mWorldY, mRadius, mRadius/2.f, o->X() + o->Radius(), o->Y(), o->Radius(), o->Radius()/2.f));
}
/*!
______________________________________________________________________________*/
void CProjectile::Update(void)
{
	std::vector< CArmy* > Teams = CGame->RequestState()->teams;
	/*std::vector<CUnit*> Units;
	for(unsigned int i = 0; i < Teams.size(); ++i)
		for(int j = 0; j < Teams[i]->GetSizeofActive(); ++j)
			Units.push_back(Teams[i]->GetActiveUnit(j));
*/
	try{
	// negative speed - jump to the destination
	if(mSpeed <= 0.f)
	{
		mAtRest = true;
		SetPosition(mDestX,mDestY);
	}

	if(mIsAmmo)
		mMaxLifetime = 1000000000;

	++mCurrLifetime;
	if(mCurrLifetime < mMaxLifetime && !mDetonate && !mDestroy)
	{
		if(mSpeed != 0)
		{
			
			mWorldX += (float)(mSpeed * mHeading.X());
			mWorldY += (float)(mSpeed * mHeading.Y());
			SetPosition(mWorldX,mWorldY);
		}
		SetPosition(mWorldX,mWorldY);

		if(mHasContrails)
		{
			if(mContrails.size() < mMaxContrailsLength)
			{
				mContrails.push_back(new CSprite(mWorldX, mWorldY, 32, 32, mContrailSprite.c_str(), true, 0, 0, rand() % 3));
			}
			else
			{
				delete *mContrails.begin();
				mContrails.pop_front();
				mContrails.push_back(new CSprite(mWorldX, mWorldY, 32, 32, mContrailSprite.c_str(), true, 0, 0, rand() % 3));
			}
		}
		
		// test for and handle collision
		for(unsigned int i = 0; i < CGame->RequestState()->map->mUnitList.size(); ++i)
			if(TestCollision((CGame->RequestState()->map->mUnitList[i]->Mech())))
			{
			  if(CGame->RequestState()->map->mUnitList[i]->Dead()) continue;
				
				// ignore owner
				if( (mDam_flags & kIgnoresOwner) && (mOwner == CGame->RequestState()->map->mUnitList[i]))
					continue;
				if(mOwner == CGame->RequestState()->map->mUnitList[i] && mSpeed > 0.f)
					continue;
				
				// at rest
				if(mAtRest == true)
				{
					if(mIsAmmo)
					{
						// collect it
						CGame->RequestState()->map->mUnitList[i]->GiveAttack(CAttack(givesAttack));
					}
				}
				
	
				CEvent_DetonateProjectile *Det = scast< CEvent_DetonateProjectile* >(CGame->MakeEvent(kEvent_DetonateProjectile));
				Det->This = this;
				Det->HitMe = CGame->RequestState()->map->mUnitList[i]->Mech();//jpetrie  so we know which unit to damage through the event
				CGame->RequestState()->map->mUnitList[i]->Dead(true);
				CGame->PostEvent(Det);
				
				
			}
			return;
	}
	
    else if(mDetonate)
	{
		mSprite->SetZOrder(.1f);
		
		if(mHasContrails && !mContrails.empty())
		{
			for(std::list< CSprite * >::iterator it = mContrails.begin(); it != mContrails.end(); ++it)
				delete *it;
			mContrails.clear();
		}

		if(mCurrDetLifetime < mDetLifetime)
			mCurrDetLifetime++;

		else
		{
			mDetonate = false;
			mDestroy = true;
		}
		return;
	}
	else if(mDestroy)
	{
		// insert a destroy projectile event
		CEvent_DestroyProjectile *tEvt = scast< CEvent_DestroyProjectile* >(CGame->MakeEvent(kEvent_DestroyProjectile));
		tEvt->This = this;
		CGame->PostEvent(tEvt);
		mDead = true;
	}
	else if(!mDead)
	{
		/*CEvent_DetonateProjectile *Det = scast< CEvent_DetonateProjectile* >(CGame->MakeEvent(kEvent_DetonateProjectile));
		Det->This = this;
		CGame->PostEvent(Det);*/
		
		Detonate();
		//mDestroy = true;
	}
	if(mDead)
	{
		return;
	}
	
	}catch(...)
		{
			nlTHROW("I AM SKIPPY JON JONES, THE GREAT SWORD FAIGHTER!");
		}
}
/*!
______________________________________________________________________________*/
void CProjectile::SetDest(float x, float y)
{
	mDestX = x;
	mDestY = y;
	mHeading = CVector(mDestX - mWorldX, mDestY - mWorldY).Unit();	
}
CProjectileGroup * CProjectile::Group(void)const
{
	return mGroup;
}
