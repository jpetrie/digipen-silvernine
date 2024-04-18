

#ifndef _C_MEMTRACKER_H_
#define _C_MEMTRACKER_H_

#include <cstdio>
#include <cstdlib>

#include <map>

class CMemTracker
{
  public:
     CMemTracker(void) { };
    ~CMemTracker(void) { };

    static void *DoMemAlloc(size_t sz,const char *f,unsigned int l);
    static void  DoMemRelease(void *p);
    
    static void PushDel(const char *f,unsigned int l);
    
    
    static void WhereAlloc(void *p);
    
    
    struct DelStack
    {
      char f[128];
      unsigned int l;
      void *addr;
      
      DelStack *next;
    };

    struct Alloc
    {
      void *realAddress;
      void *logicAddress;
      unsigned int sz;
      char f[128];
      unsigned int l;

      Alloc *next;
    };
    
   static  DelStack *top;

   static Alloc *first;

  static std::map< void*,Alloc > mmap;

 static  int leak;

};



void* operator new(size_t sz,const char *f,unsigned int l);


// VC 6 requires these
void operator delete(void *p,const char *f,unsigned int l);
//void operator delete[](void *p,const char *f,unsigned int l) { free(p); }


#define new      new(__FILE__,__LINE__)
#define delete   CMemTracker::PushDel(__FILE__,__LINE__),delete



#endif