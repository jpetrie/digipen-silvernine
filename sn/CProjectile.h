/*!
	@file		CProjectile.h
	@author		Scott Smith
	@date		Novemeber 14, 2003

  @brief	Represents an in-game projectile.
______________________________________________________________________________*/

#ifndef	__CPROJECTILE_H__
#define	__CPROJECTILE_H__

#include "CObject.h"
#include "CVector.h"
#include "CTagFactory.h"
#include "CTag_proj.h"
#include <list>

// forward references
class CUnit;
class CProjectileGroup;
/*!
	@class CProjectile

	@brief	Represents an in game projectile.

	Projectiles are the only in-game objects that can inflict damage.  They also
	represent ammunition which can be scavenged.
______________________________________________________________________________*/
class CProjectile	: public CObject
{
public:
	// ct & dt
	CProjectile(const std::string &tag, float x, float y, float destx, float desty, bool isammo = false);
	virtual ~CProjectile(void);
    
  // initialization
  virtual void LoadFromTag(const std::string &tag);
	
	// accessors
	float X(void)	{ return mWorldX; }
	float	Y(void)	{ return mWorldY; }
	float Speed(void)	{ return mSpeed; }
	CVector Heading(void)	{ return mHeading; }
	CProjectileGroup * Group(void)const;
	//jpetrie: I need these for CEvent_DamageObject.
	float Damage(void) { return mDamage; }
	int   DamageType(void) { return mDamage_type; }
	
	// collision
	inline bool TestCollision(CObject *o);

	std::string givesAttack;
	// updating
  virtual void Update(void);

	// mutators
	void X(float x)	{ mWorldX = x; }
	void Y(float y) { mWorldY = y; }
	void Speed(float s) { mSpeed = s; }
	void SetDest(float x, float y);
	void Detonate(void) 
	{ 
		mDetonate = true; 
		mSprite->SetSequence(mDet_seq_idx, 0); 
		mSprite->SetZOrder(0);
		mSpeed = 0.f; 
	}
	void SetOwner(CUnit *owner) { mOwner = owner; }
	void Group(CProjectileGroup* group) { mGroup = group; }


private:
	float					mSpeed;							// projectile speed, in world units per simulation step
	CVector					mHeading;						// direction vector
	float					mDamage;						// damage value
	int 					mIn_flight_seq_idx;				// animation sequence - in flight
	int						mAt_rest_seq_idx;				// animation sequence - at rest
	int						mDet_seq_idx;					// animation sequence - detonation
	int						mDet_flags;						// detonation flags
	int 					mDam_flags;						// damage flags
	int						mDamage_type;					// type of damage it inflicts
	float					mDamage_min;					// minimum amount of damage the projectile can inflict
	float					mDamage_max;					// maximum amount of damage the projectile can inflict
	float					mDamage_radius;					// true damage radius (calculated)
	float					mDamage_radius_min;				// the minimum damage radius
	float					mDamage_radius_max;				// the maximum damage radius
	float					mDam_fill_rate;					// damage fill rate, as a percentage per frame
	float					mHeight;						// height above the ground - should be in CObject
	int						mCurrLifetime;					// how long has the projectile been 'alive'? (frames)
	int						mCurrDetLifetime;				// how long has the projectile been detonating? (frames)
	int						mMaxLifetime;					// how long can the projectile live?	(frames)
	int						mDetLifetime;					// how long should the projectile detonate? (frames)
	CLine*					mLine;							// for debug
	bool					mDetonate;						// should it detonate?
	bool					mDestroy;						// should it destroy itself?
	bool					mDead;							// has it been destroyed?
	bool					mAtRest;						// is it static?
	bool					mIsAmmo;						// is it ammunition?
	CUnit*					mOwner;							// the unit that fired the projectile
	CProjectileGroup *		mGroup;
	std::list< CSprite * >  mContrails;
	bool					mHasContrails;
	int						mMaxContrailsLength;
	std::string				mContrailSprite;
	
};

#endif