/*! =========================================================================
      
      @file    CScriptableM.h
      @brief   Interface and implementation of scriptable mix-in.
      
    ========================================================================= */
    
/*                                                                      guard
----------------------------------------------------------------------------- */

#ifndef _C_SCRIPTABLE_M_H_
#define _C_SCRIPTABLE_M_H_



/*                                                                   includes
----------------------------------------------------------------------------- */

#include "NSL.h"

#include "CScriptMgrS.h"


/*                                                                    classes
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
template< typename T_ >
class CScriptableM : public CScriptableBase
/*! @brief Scriptability mix-in.

    Any class wishing to expose functionality to the scripting engine must
    publically derive from CScriptableM< T_ >, where T_ is the target class.
    Methods exported via the 'EXPORT' tag macro will then be available for
    use in script code.

    Prior to invoking any scripts that make use of scriptable classes, the
    static RegisterScriptableClass() method must be called for the class.

    Scriptable classes can be used in two ways: Objects of the class T_ can be
    created within scripts, where they have lifetime within that script only
    and are eventually reclaimed by the script engine's garbage collector.
    Alternatively, instances of class T_ created in C++ code can have scripts
    run on them by calling the ExecuteScript() method. When a script is run
    in such a manner, the object 'self' will be analagous to the C++ `this`
    pointer of the class executing the script.

    @sa CScriptableBase
    @sa CScriptMgrS
*/
{  
  public:
    // ct and dt
             CScriptableM(void);
    virtual ~CScriptableM(void);

    // class registration
    static void RegisterScriptableClass(const CScriptableBase &temporary);

    // script execution
    void ExecuteScript(const std::string &fn);
    void ExecuteTag(const std::string &tag);
  

  private:
    // dispatcher
    static int nThunkMethod(CScriptMgrS::TState *s);

    // object lifetime
    static int nScriptConstructType(CScriptMgrS::TState *s);
    static int nScriptDestructType(CScriptMgrS::TState *s);
    static int nScriptDestructReferenceType(CScriptMgrS::TState *s);
};


/*                                                           function members
----------------------------------------------------------------------------- */

/*  _________________________________________________________________________ */
template< typename T_ >
CScriptableM< T_ >::CScriptableM(void)
/*! @brief Default constructor.
*/
{
}


/*  _________________________________________________________________________ */
template< typename T_ >
CScriptableM< T_ >::~CScriptableM(void)
/*! @brief Destructor.
*/
{
}


/*  _________________________________________________________________________ */
template< typename T_ >
void CScriptableM< T_ >::RegisterScriptableClass(const CScriptableBase &temporary)
/*! @brief Class registrar.

    This function must be invoked prior to running any scripts that make use
    of the class, or they will fail during execution-time.

    This function sets up the interface between Lua and the scriptable class.
    It queries the script daemon's class binding table for all exported
    methods of the class T_, and exposes them to Lua in a lexical closure
    containing the mangled method name. The glue function used is the static
    class method nThunkMethod(), which simply calls the script daemon's
    dispatcher.
    
    In order for classes derived from a scriptable class to inherit the
    exposed methods of the base classes, RegisterScriptableClass() must be
    called in inheritance order (e.g., parent to child) for classes of a
    given hierarchy.

    The creation of the reference type ("refto__T_") is neccessary for
    supporting 'self' objects. The reference type uses a garbage collection
    metamethod that is a no-op, to prevent Lua's collector from releasing
    memory allocated by C++.
*/
{
static std::vector< std::string >  tChain;
static int                         tChainPos = 0;
std::vector< std::string >         tBound;
CScriptMgrS::TState               *tState = CScriptMgr->mState;
std::string                        tClassName;
std::string                        tClassRefName;
int                                tMethTable;
int                                tMetaTable;
int                                tRefMetaTable;

  // Get the name of the derived class. Chop off the six-character "class "
  // string returned by the (highly implementation-dependant) typeid operation.
  tClassName = typeid(temporary).name();
  tClassName = tClassName.substr(6);
  tClassRefName = "refto__";
  tClassRefName += tClassName;

  // Create a new table for methods and a new metatable.
  lua_newtable(tState);
  tMethTable = lua_gettop(tState);
  luaL_newmetatable(tState,tClassName.c_str());
  tMetaTable = lua_gettop(tState);
  luaL_newmetatable(tState,tClassRefName.c_str());
  tRefMetaTable = lua_gettop(tState);

  // Hide the metatable.
  lua_pushliteral(tState,"__metatable");
  lua_pushvalue(tState,tMethTable);
  lua_settable(tState,tMetaTable);
  lua_pushliteral(tState,"__metatable");
  lua_pushvalue(tState,tMethTable);
  lua_settable(tState,tRefMetaTable);

  // Use indexing to support method calls.
  lua_pushliteral(tState,"__index");
  lua_pushvalue(tState,tMethTable);
  lua_settable(tState,tMetaTable);
  lua_pushliteral(tState,"__index");
  lua_pushvalue(tState,tMethTable);
  lua_settable(tState,tRefMetaTable);

  // Use garbage collection to support destruction.
  lua_pushliteral(tState,"__gc");
  lua_pushcfunction(tState,nScriptDestructType);
  lua_settable(tState,tMetaTable);
  lua_pushliteral(tState,"__gc");
  lua_pushcfunction(tState,nScriptDestructReferenceType);
  lua_settable(tState,tRefMetaTable);

  // Drop metatables.
  lua_pop(tState,1);
  
  // If the class has any virtual functions, we will need to
  // bind them through the class's vtable to ensure the correct
  // functions are called at runtime.
  if(CScriptMgr->mVirtualClasses[tClassName])
  {
  long         *tVTable;
  int           tVTableSize;
#pragma warning(disable: 4311)
  unsigned long tThisPtr = rcast< unsigned long >(&temporary);
#pragma warning(default: 4311)
  
    __asm
    {
        mov eax,tThisPtr  // The vtable is at the 
        mov eax,[eax]     // beginning of the object.
      
        mov tVTable,eax   // Save the address.
        mov ecx,0x00      // Initialize counter.
      
    cnt:
        cmp [eax],0x00    // Does EAX point to zero?
        jz  end           // Then stop. Otherwise:
        add eax,0x04      // Next vtable entry; assumes four-byte pointers.
        inc ecx           // Increment entry count.
        jmp cnt           // Repeat.
      
    end:
        mov tVTableSize,ecx  // Recover vtable count.  
    }
    
    // Now we can walk the vtable.
    for(int i = 0; i < tVTableSize; ++i)
    {
      // Find the binding in the address map.
      // If we don't find it, we don't bind it (it's probably an unexposed virtual).
      if(CScriptMgr->mAddrBindingTable.find(tVTable[i]) != CScriptMgr->mAddrBindingTable.end())
      {
      CScriptMgrS::StBinding tB = CScriptMgr->mAddrBindingTable[tVTable[i]];
      
        // First push the name the method is called within Lua.
        lua_pushstring(tState,tB.name.c_str());
      
        // Then push closure data; first the class (nspace) the method is from,
        // and then, the mangled name of the method (used as a key).
        lua_pushstring(tState,tB.nspace.c_str());
        lua_pushstring(tState,tB.mangledSig.c_str());
      
        // Now push a closure. This associates the above name (tB.name) in Lua with
        // the actual C code specified here: nThunkMethod.
        lua_pushcclosure(tState,nThunkMethod,2);
        lua_settable(tState,tMethTable);
        
        tBound.push_back(tB.name);
      }
    }
  }
  
  
  // Find all methods exposed by this class and register them.
  // The method name is exposed to Lua in a closure containing
  // the mangled method name as a key. The key is used by
  // the glue function that actually dispatches the calls.
CScriptMgrS::TBindingMap            tBindings;
CScriptMgrS::TBindingMap::iterator  tBindingIt;

  tBindings = CScriptMgr->mClassBindingTable[tClassName];
  tBindingIt = tBindings.begin();

  while(tBindingIt != tBindings.end())
  {
  CScriptMgrS::StBinding tB = (*tBindingIt).second;

    // If the binding is flagged virtual, the vtable magic we just
    // performed above has taken care of it. Skip it.
    if(!tB.is_virtual)
    {
      // As before, first push the method name.
      lua_pushstring(tState,tB.name.c_str());
      
      // Then some closure data.
      lua_pushstring(tState,tClassName.c_str());
      lua_pushstring(tState,tB.mangledSig.c_str());
      
      // Then the closure.
      lua_pushcclosure(tState,nThunkMethod,2);
      lua_settable(tState,tMethTable);
      
      tBound.push_back(tB.name);
    }
    
    // Next binding.
    ++tBindingIt;
  }
  
  // Next, walk up the inheritance chain. Any exposed methods in THOSE classes that are NOT already
  // bound, must be bound. tChain will contain the type names of every class in this hierarchy,
  // assuming the users correctly call this function in hierarchy order.
int  tTempChainPos = tChainPos;
  
  while(tTempChainPos > 0)
  {
  std::string  tParentName = tChain[tTempChainPos - 1];  // The position will be one-off.
    
    tBindings = CScriptMgr->mClassBindingTable[tParentName];
    tBindingIt = tBindings.begin();
    
    while(tBindingIt != tBindings.end())
    {
    CScriptMgrS::StBinding tB = (*tBindingIt).second;

      // Make sure that we don't bind functions we've already bound.
      // Current we key this by name, but this of course prevents us from
      // correctly dealing with function overloads.
      if(std::find(tBound.begin(),tBound.end(),tB.name) == tBound.end())
      {
        // As before, first push the method name.
        lua_pushstring(tState,tB.name.c_str());
        
        // Then some closure data.
        lua_pushstring(tState,tClassName.c_str());
        lua_pushstring(tState,tB.mangledSig.c_str());
        
        // Then the closure.
        lua_pushcclosure(tState,nThunkMethod,2);
        lua_settable(tState,tMethTable);
        
        std::cout << "Binding from inherited: " << tB.name << "\n";
        tBound.push_back(tB.name);
      }
      
      // Next binding.
      ++tBindingIt;
    }
    
    // Next level up in hierarchy.
    --tTempChainPos;
  }
  
  // Put this class in the chain.
  ++tChainPos;
  tChain.push_back(tClassName);

  // Drop method table.
  lua_pop(tState,1); 

  // Register pseudo-constructor.
  lua_pushstring(tState,tClassName.c_str());
  lua_pushstring(tState,tClassName.c_str());
  lua_pushcclosure(tState,nScriptConstructType,1);
  lua_settable(tState,LUA_GLOBALSINDEX);
}


/*  _________________________________________________________________________ */
template< typename T_ >
void CScriptableM< T_ >::ExecuteScript(const std::string &fn)
/*! @brief Executes the specified script on the invoking object.

    Within the script executed, the object 'self' refers to the invoking
    object. Errors encountered during execution-time are printed to standard
    output.

    The 'self' object is created by boxing a pointer to 'this' (casted to
    T_*), associating the metatable for the class with the pointer, and
    then labelling the boxed pointer "self". Then we call the daemon's
    ExecuteFile() method.

    @param fn  Specifies the filename of the script to execute.
*/
{
T_          *tObj = static_cast< T_* >(this);
std::string  tClassName = typeid(*this).name();
std::string  tClassRefName = "refto__";
  
  // Chomp the 'class ' part of the typeid name.
  tClassName = tClassName.substr(6);
  tClassRefName += tClassName;
  
  // Need to use the WEAK (reference) type table, not the strong (real)
  // type table. 
  lua_boxpointer(CScriptMgr->mState,tObj);
  luaL_getmetatable(CScriptMgr->mState,tClassRefName.c_str());
  lua_setmetatable(CScriptMgr->mState,-2);
  lua_setglobal(CScriptMgr->mState,"self");
  
  CScriptMgr->ExecuteFile(fn);
}


/*  _________________________________________________________________________ */
template< typename T_ >
void CScriptableM< T_ >::ExecuteTag(const std::string &tag)
/*! @brief Executes the specified tag script on the invoking object.

    Within the script executed, the object 'self' refers to the invoking
    object. Errors encountered during execution-time are printed to the
    script daemon's journal.

    The 'self' object is created by boxing a pointer to 'this' (casted to
    T_*), associating the metatable for the class with the pointer, and
    then labelling the boxed pointer "self". Then we call the manager's
    ExecuteTag() method.

    @param fn  Specifies the filename of the script to execute.
*/
{
T_          *tObj = static_cast< T_* >(this);
std::string  tClassName = typeid(*this).name();
std::string  tClassRefName = "refto__";
  
  // Chomp the 'class ' part of the typeid name.
  tClassName = tClassName.substr(6); 
  tClassRefName += tClassName;
  
  lua_boxpointer(CScriptMgr->mState,tObj);
  luaL_getmetatable(CScriptMgr->mState,tClassRefName.c_str());
  lua_setmetatable(CScriptMgr->mState,-2);
  lua_setglobal(CScriptMgr->mState,"self");
  
  CScriptMgr->ExecuteTag(tag);
}


/*  _________________________________________________________________________ */
template< typename T_ >
int CScriptableM< T_ >::nThunkMethod(CScriptMgrS::TState *s)
/*! @brief Handles dispatching of class methods called from Lua.

    This function is the glue between the methods of the Lua object and the
    actual C++ object. It handles calls to methods from Lua by sending them
    to the script daemon's dispatcher, which does the real work.

    The function checks for both the refto_T_ type and the T_ type of the
    'self' object that Lua sends us. The check for the reference type is
    made first, since they are assumed to be more common.

    @param s  The Lua script engine state.

    @return
    An integer indicating the number of values to be returned to Lua.
*/
{
std::string  tMethod;
std::string  tClassName = lua_tostring(s,lua_upvalueindex(1));
std::string  tClassRefName = "refto__";
T_         **tSelf;


  tClassRefName += tClassName;
  tSelf = scast< T_** >(luaL_checkudata(s,1,tClassRefName.c_str()));

  // If we don't find an object of the reference type, we try for a regular type.
  if(0 == tSelf || 0 == *tSelf)
  {
    tSelf = scast< T_** >(luaL_checkudata(s,1,tClassName.c_str()));
    if(0 == tSelf || 0 == *tSelf)
      luaL_typerror(s,1,tClassName.c_str());
  }

  lua_remove(s,1);

  // Grab the method key and dispatch it.
  tMethod = lua_tostring(s,lua_upvalueindex(2));
  return (CScriptMgr->nDispatchMethod(tMethod,tClassName,*tSelf));
}


/*  _________________________________________________________________________ */
template< typename T_ >
int CScriptableM< T_ >::nScriptConstructType(CScriptMgrS::TState *s)
/*! @brief Invokes the default constructor of T_ during creation.

    This method is invoked when an object is created from within Lua code.

    @param s  The Lua script engine state.

    @return
    An integer indicating the number of values to be returned to Lua.
*/
{
T_          *tObj = new T_;
std::string  tClassName = lua_tostring(s,lua_upvalueindex(1));
  
  lua_boxpointer(s,tObj);
  luaL_getmetatable(s,tClassName.c_str());
  lua_setmetatable(s,-2);

  return (1);   
}

/*  _________________________________________________________________________ */
template< typename T_ >
int CScriptableM< T_ >::nScriptDestructType(CScriptMgrS::TState *s)
/*! @brief Invokes the destructor of T_ during garbage collection.

    This method is invoked when an object created from within Lua code is
    garbage-collected.

    @param s  The Lua script engine state.

    @return
    An integer indicating the number of values to be returned to Lua.
*/
{
T_ *tObj = scast< T_* >(lua_unboxpointer(s,1));

  std::cout << "NORMAL TYPE DESTRUCTED\n";
  delete tObj;
  return (0);
}


/*  _________________________________________________________________________ */
template< typename T_ >
int CScriptableM< T_ >::nScriptDestructReferenceType(CScriptMgrS::TState * /*s*/)
/*! @brief Invokes the destructor of a reference type during garbage collection.

    A "reference type" in this case is the 'self' object created when
    methods are called on an object from Lua. The 'self' object is nothing
    but a boxed pointer to data allocated from C++ somewhere; it is therefore
    not Lua's job to release it. This function is basically a no-op.

    @param s  The Lua script engine state.

    @return
    An integer indicating the number of values to be returned to Lua.
*/
{
  //std::cout << "WEAK TYPE DESTRUCTED\n";
  return (0);
}


#endif  /* _C_SCRIPTABLE_M_H_ */
