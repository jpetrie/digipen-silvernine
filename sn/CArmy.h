/*! =========================================================================
      
      @file    CArmy.h
      @brief   
      
    ========================================================================= */

/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_ARMY_H_
#define _C_ARMY_H_


/*                                                                   includes
----------------------------------------------------------------------------- */

#include "precompiled.h"

#include "CScriptMgrS.h"
#include "CScriptableM.h"

#include "CUnit.h"

#include "CTag_army.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

class CArmy : public CScriptableM< CArmy >
{
	public:
		// ct and dt
		CArmy(void);
		~CArmy(void);
		
		// load
		void InitFromTag(const CTag_army *tag);
		
		// accessors
		void AddUnit(CUnit*);
	  void AddActiveUnit(CUnit*);
		void AddUnit(const char*);
		void AddAttack(const std::string);
		void RemUnit(int);
		void RemActiveUnit(int);
		CUnit* GetUnit(int);
		CUnit* GetActiveUnit(int);
		int GetSizeofAvailable(void);
		int GetSizeofActive(void);
		int GetMoney(void)			{ return mMoneyCur; }
		void SetMoney(int money)	{ mMoneyCur = money; }

	private:
		// data members
		int mMoneyCur;		// current money of the army
		std::vector <CUnit*> mUnitV;
		std::vector <CUnit*> mActiveUnitV;
		std::vector <CAttack> mAttackV;
};

#endif  /* _C_ARMY_H_ */