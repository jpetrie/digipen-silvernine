/*! =========================================================================
      
      @file    CArmy.cpp
      @author  jmccrory
      @brief   
      
    ========================================================================= */

/*                                                                   includes
----------------------------------------------------------------------------- */
#include "precompiled.h"
#include "CArmy.h"
#include "CAttack.h"

/*                                                           function members
----------------------------------------------------------------------------- */

CArmy::CArmy(void)
/*! @brief Default Constructor
*/
{
	SetMoney(100000);
}

CArmy::~CArmy(void)
/*! @brief Deconstructor
*/
{
  // Release units owned by the army.
  for(unsigned int i = 0; i < mUnitV.size(); --i)
    delete mUnitV[i];
  mUnitV.clear();
}


void CArmy::InitFromTag(const CTag_army *tag)
{
  mMoneyCur = tag->cash;
  std::cout << "\t\tCash: " << mMoneyCur << "\n";
  
  // Build the units.
  for(unsigned int i = 0; i < tag->size; ++i)
  {
  CUnit *tUnit;
  
    std::cout << "\t\tUnit " << i << ": " << tag->units[i].unitBase << " " << tag->units[i].mechBase << " ";
    std::cout << tag->units[i].armor << "/" << tag->units[i].armorMax << " "
              << tag->units[i].shields << "/" << tag->units[i].armorMax << " "
              << tag->units[i].sync << "/" << tag->units[i].syncMax << "\n";

   tUnit = new CUnit;
   tUnit->LoadFromTag("unit_dbg");
   tUnit->SetMech(tag->units[i].mechBase);
   tUnit->SetArmor(tag->units[i].armor);
   tUnit->SetArmorMax(tag->units[i].armorMax);
   tUnit->SetShields(tag->units[i].shields);
   tUnit->SetShieldsMax(tag->units[i].shieldsMax);
   tUnit->SetSync(tag->units[i].sync);
   tUnit->SetSyncMax(tag->units[i].syncMax);

   // Add this unit to the army.
   AddUnit(tUnit);
  }
}


void CArmy::AddUnit(CUnit* pUnit)
/*! @brief Adds unit to vector list

	\param unit  pointer to the unit to be added
*/
{
	mUnitV.push_back(pUnit);
}

void CArmy::AddActiveUnit(CUnit* pUnit)
/*! @brief Adds unit to active vector list

	\param unit  pointer to the unit to be added
*/
{
  //pUnit->Show(true);
	mActiveUnitV.push_back(pUnit);
}

void CArmy::AddUnit(const char* unitTag)
/*! @brief Overloaded AddUnit function makes a new unit and adds it
		to the vector list
	\param unitTag  The tag of the unit to be loaded
*/
{
	CUnit* unit = new CUnit(unitTag);
	AddUnit(unit);
}

void CArmy::AddAttack(const std::string attack)
{
  mAttackV.push_back(CAttack(attack));
}

void CArmy::RemUnit(int index)
/*! @brief Removes unit from list at specified index

	\param index  The index into the vector of the unit to be removed
		can range from 0 to the end of the unit vector list
		does nothing if the index is out of range
*/
{
	if (index >= 0 && index < (int)mUnitV.size())
	{
		vector <CUnit*>::iterator iter = mUnitV.begin() + index;
		mUnitV.erase(iter);
	}
}

void CArmy::RemActiveUnit(int index)
/*! @brief Removes unit from active list at specified index

	\param index  The index into the vector of the unit to be removed
		can range from 0 to the end of the unit vector list
		does nothing if the index is out of range
*/
{
	if (index >= 0 && index < (int)mActiveUnitV.size())
	{
		vector <CUnit*>::iterator iter = mActiveUnitV.begin() + index;
		mActiveUnitV.erase(iter);
	}
}

CUnit* CArmy::GetUnit (int index)
/*! @brief Finds the unit at the specified index

	\param index  The index into the vector of the unit to be retrieved
		can range from 0 to the end of the unit vector list

	\return A pointer to the unit at the index or NULL if the index is 
		out of range

*/
{
	if (index >= 0 && index < (int)mUnitV.size())
	{
		return mUnitV[index];
	}
	else
		return NULL;
}

CUnit* CArmy::GetActiveUnit (int index)
/*! @brief Finds the unit at the specified index

	\param index  The index into the active vector of the unit to be retrieved
		can range from 0 to the end of the unit vector list

	\return A pointer to the unit at the index or NULL if the index is 
		out of range

*/
{
	if (index >= 0 && index < (int)mActiveUnitV.size())
	{
		return mActiveUnitV[index];
	}
	else
		return NULL;
}

int CArmy::GetSizeofAvailable(void)
/*! @brief get the size of the available units vector
*/
{
	return (int)mUnitV.size();
}

int CArmy::GetSizeofActive(void)
/*! @brief get the size of the active units vector
*/
{
	return (int)mActiveUnitV.size();
}