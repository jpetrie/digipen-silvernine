/*! =========================================================================
      
      @file    CConfigMgrS.h
      @author  jmccrory
      @brief   Interface to configuration manager class.
      
    ========================================================================= */

#include "precompiled.h"

#ifndef _CCONFIGMGR_S_H_
#define _CCONFIGMGR_S_H_

enum TYPE {	eSTRING, eBOOL, eDOUBLE, eINT };

union VALUE
{
	std::string *s;
	bool b;
	double d;
	long int i;
};

struct DATA
{
	TYPE type;
	VALUE value;
};


class CConfigMgrS :public nsl::singleton<CConfigMgrS>
/*! @brief Config layer management singelton
*/
{
public:
	// construct and deconstruct
	CConfigMgrS(){}
	~CConfigMgrS();

	void ParseConfig(char* configFile);
	VALUE GetCfgValue(std::string);		
	void SetCfgValue(std::string, DATA);

	std::map < std::string, DATA > ConfigMap;
	
	
	
	//jpetrie  Added these during Christmas '03:
	bool        GetValueAsBool(const std::string &opt)                        { VALUE v = GetCfgValue(opt); return (v.b); }
	int         GetValueAsInt(const std::string &opt)                         { VALUE v = GetCfgValue(opt); return (v.i); }
	double      GetValueAsReal(const std::string &opt)                        { VALUE v = GetCfgValue(opt); return (v.d); }
	std::string GetValueAsString(const std::string &opt)                      { VALUE v = GetCfgValue(opt); return (*v.s); }
	void        SetValueAsBool(const std::string &opt,bool v)                 { DATA d; d.type = eBOOL; d.value.b = v; SetCfgValue(opt,d); }
	void        SetValueAsInt(const std::string &opt,int v)                   { DATA d; d.type = eINT; d.value.i = v; SetCfgValue(opt,d); }
	void        SetValueAsReal(const std::string &opt,double v)               { DATA d; d.type = eDOUBLE; d.value.d = v; SetCfgValue(opt,d); }
	void        SetValueAsString(const std::string &opt,const std::string &v) { DATA d; d.type = eSTRING; d.value.s = new std::string(v); SetCfgValue(opt,d); }
};



// singleton accessor
#define CConfigMgr  CConfigMgrS::instance()


#endif