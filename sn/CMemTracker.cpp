
#include "CMemTracker.h"

// teh hax
#undef new
#undef delete

#include <typeinfo>

CMemTracker::DelStack * CMemTracker::top = 0;
CMemTracker::Alloc    * CMemTracker::first = 0;

std::map< void*,CMemTracker::Alloc > CMemTracker::mmap;

int  CMemTracker::leak = 0;


void *CMemTracker::DoMemAlloc(size_t sz,const char *f,unsigned int l)
{
Alloc a;
unsigned int i = 0;

  // copy name
  while(f[i] != '\0' && i < 128)
  {
    a.f[i] = f[i];
    ++i;
  }
  // and line number
  a.l = l;
  
  a.realAddress = a.logicAddress = malloc(sz);
  a.next = 0;
  //printf("ALLOC %s %u %d bytes\n",f,l,sz);
  //printf("THING IS A: %s\n",typeid(a.logicAddress).name());
  
  mmap[ a.realAddress ] = a;
leak++;

  return (a.realAddress);
}


void CMemTracker::DoMemRelease(void *p)
{
DelStack *t = top;


  printf("FREE\n");
  leak--;

  free(p);
}



void CMemTracker::WhereAlloc(void *p)
{
Alloc a = mmap[p];

  printf("ALLOC AT: %s %u\n",a.f,a.l);
  
}


void CMemTracker::PushDel(const char *f,unsigned int l)
{
  //printf("PUSH %f %u\n",f,l);
}


void* operator new(size_t sz,const char *f,unsigned int l)
{
  return CMemTracker::DoMemAlloc(sz,f,l);
}


void operator delete(void *p,const char *f,unsigned int l)   { CMemTracker::DoMemRelease(p); }