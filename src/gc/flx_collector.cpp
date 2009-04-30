#include <cstdlib>
#include <map>
#include <limits.h>
#include <cassert>
#include <cstdio>
#include <cstddef>
#include "flx_rtl_config.hpp"
#include "flx_collector.hpp"
#include "flx_rtl.hpp"
namespace flx {
namespace gc {
namespace collector {

static int mcount FLX_UNUSED = 0;

void *malloc_free::allocate(std::size_t amt)
{
  void *p = malloc(amt);
  if(debug)
    fprintf(stderr,"Malloc %ld bytes, address = %p\n",amt,p);
  if(p)return p;
  else {
    fprintf(stderr,"Felix: Malloc out of memory, blk=%ld\n",long(amt));
    throw flx::rtl::flx_out_of_memory_t();
  }
}

void malloc_free::deallocate(void *p)
{
  if(debug)
    fprintf(stderr,"Free %p\n",p);
  free(p);
}

void *flx_collector_t::v_allocate(gc_shape_t *ptr_map, unsigned long x) {
  return impl_allocate(ptr_map, x);
}

void flx_collector_t::v_finalise(void *frame) {
  impl_finalise(frame);
}

unsigned long flx_collector_t::v_collect() {
  // NO MUTEX
  return impl_collect();
}

void flx_collector_t::v_add_root(void *memory) {
  impl_add_root(memory);
}

void flx_collector_t::v_remove_root(void *memory) {
  impl_remove_root(memory);
}

void flx_collector_t::v_free_all_mem() {
  //fprintf(stderr, "Dispatching to impl free all mem\n");
  impl_free_all_mem();
}

unsigned long flx_collector_t::v_get_allocation_count()const {
  return impl_get_allocation_count();
}

unsigned long flx_collector_t::v_get_root_count()const {
  return impl_get_root_count();
}

unsigned long flx_collector_t::v_get_allocation_amt()const {
  return impl_get_allocation_amt();
}

unsigned long flx_collector_t::impl_get_allocation_count()const
{
  return allocation_count;
}

unsigned long flx_collector_t::impl_get_root_count()const
{
  return root_count;
}

unsigned long flx_collector_t::impl_get_allocation_amt()const
{
  return allocation_amt;
}


flx_collector_t::flx_collector_t(allocator_t *a, pthread::thread_control_t *tc)
  :allocation_count(0)
  ,root_count(0)
  ,allocation_amt(0)
  ,parity(false)
  ,allocator(a)
  ,thread_control(tc)
  ,j_shape(0)
  ,j_nalloc(0)
  ,j_nused(0)
  ,j_tmp(0)
{}

flx::pthread::thread_control_t *flx_collector_t::get_thread_control()const
{
  return thread_control;
}

void flx_collector_t::judyerror(char const *loc)
{
  fprintf(stderr, "JUDY ERROR %d in %s\n",je.je_Errno,loc);
  abort();
}

void * flx_collector_t::impl_allocate(gc_shape_t *shape, unsigned long nobj)
{
  // calculate how much memory to request
  std::size_t amt = nobj * shape->amt * shape->count;
  //fprintf(stderr, "req amt = %ld\n",amt);
  if(amt & 1) ++amt; // round up to even number
  //fprintf(stderr, "rounded req amt = %ld\n",amt);

  // allocate a block
  void *fp = (void *)allocator->allocate(amt);
  assert(fp); // Got some memory!

  if(debug)
    fprintf(stderr,"Allocated %p, shape=%p = new %s\n", fp,shape,shape->cname);

  Word_t *p = (Word_t*)(void*)JudyLIns(&j_shape,(Word_t)fp,&je);
  *p = ((Word_t)(void*)shape) | (parity & 1);
  if (nobj != 1uL) // array
  {
    Word_t *p = (Word_t*)(void*)JudyLIns(&j_nalloc,(Word_t)fp,&je);
    *p = nobj;
  }

  // update statistics
  allocation_count++;
  allocation_amt += amt;
  //fprintf(stderr,"ADDING %ld to allocation amt, result %ld\n",long(amt),long(allocation_amt));
  // return client memory pointer
  return fp;
}

void flx_collector_t::set_used(void *memory, unsigned long n)
{
  assert(memory);
  assert(n>=0);

  // this check is expensive, but set_used is not used often
  assert(n<=get_count(memory));
  //fprintf(stderr,"Set used of %p to %ld\n",memory,n);
  Word_t *p = (Word_t*)(void*)JudyLGet(j_nused,(Word_t)memory,&je);
  if(p==(Word_t*)PPJERR)judyerror("set_used");
  if(p==NULL)
  {
    //fprintf(stderr,"No recorded usage! Creating store for data\n");
    p = (Word_t*)(void*)JudyLIns(&j_nused,(Word_t)memory,&je);
  }
  //fprintf(stderr,"Slot for %p usage is address %p\n",memory,p);
  *p = (Word_t)n;
}

void flx_collector_t::incr_used(void *memory, unsigned long n)
{
  assert(memory);
  assert(n>=0);
  //fprintf(stderr,"Incr used of %p by %ld\n",memory,n);
  assert(get_used(memory) + n <= get_count(memory));
  Word_t *p = (Word_t*)(void*)JudyLGet(j_nused,(Word_t)memory,&je);
  if(p==(Word_t*)PPJERR)judyerror("incr_used");
  if(p==NULL)
  {
    p = (Word_t*)(void*)JudyLIns(&j_nused,(Word_t)memory,&je);
    *p = n;
  }
  else *p+=n;
}

// actual number of used slots in an array
unsigned long flx_collector_t::get_used(void *memory)
{
  assert(memory);
  //fprintf(stderr, "Get used of %p\n",memory);
  Word_t *p = (Word_t*)(void*)JudyLGet(j_nused,(Word_t)memory,&je);
  if(p==(Word_t*)PPJERR)judyerror("get_used");
  //fprintf(stderr, "Used slot at address %p\n",memory);
  unsigned long z = p!=NULL?*p:1; // defaults to 1 for non-array support
  //fprintf(stderr,"Used of %p is %ld\n",memory,z);
  return z;
}

// max number of available slots in an array
unsigned long flx_collector_t::get_count(void *memory)
{
  assert(memory);
  Word_t *p = (Word_t*)(void*)JudyLGet(j_nalloc,(Word_t)memory,&je);
  if(p==(Word_t*)PPJERR)judyerror("get_count");
  return p!=NULL?*p:1; // defaults to 1 for non-array support
}

gc_shape_t *flx_collector_t::get_shape(void *memory)
{
  assert(memory);
  Word_t *pshape= (Word_t*)JudyLGet(j_shape,(Word_t)memory,&je);
  if(pshape==(Word_t*)PPJERR)judyerror("get_shape");
  if(pshape==NULL) abort();
  return (gc_shape_t*)(*pshape & (~1ul));
}

void *flx_collector_t::create_empty_array(
  flx::gc::generic::gc_shape_t *shape,
  unsigned long count
)
{
  //fprintf(stderr,"create empty array length %ld\n",count);
  void *p = allocate(shape,count);
  set_used (p, 0); // make sure to override default 1 slot usage
  //fprintf(stderr,"Array at %p, used = %ld, max=%ld\n",p,get_used(p), get_count(p));
  return p;
}


void flx_collector_t::impl_finalise(void *fp)
{
  assert(fp!=NULL);
  gc_shape_t *shape = get_shape(fp);
  void (*finaliser)(collector_t*, void*) = shape->finaliser;
  if (finaliser)
  {
    unsigned char *cp = (unsigned char*)fp;
    unsigned long n_used = get_count(fp) * shape->count;
    unsigned long eltsize = shape->amt;
    for(unsigned long j = 0; j<n_used; ++j)
    {
      (*finaliser)(this,(void*)cp);
      cp += eltsize;
    }
  }
}

void flx_collector_t::unlink(void *fp)
{
  // check we have a pointer to an object
  assert(fp!=NULL);

  // call the finaliser if there is one
  impl_finalise(fp);

  allocation_count--;
  gc_shape_t *shape = get_shape(fp);
  unsigned long n_objects = get_count(fp);
  unsigned long nobj = shape -> count * n_objects;
  std::size_t size = shape->amt * nobj;
  allocation_amt -= size;

  // unlink the frame from the collectors list
  JudyLDel(&j_shape, (Word_t)fp, &je);
  JudyLDel(&j_nused, (Word_t)fp, &je);
  JudyLDel(&j_nalloc, (Word_t)fp, &je);
}

void flx_collector_t::post_delete(void *fp)
{
  Judy1Set(&j_tmp,(Word_t)fp,&je);
}

void flx_collector_t::delete_frame(void *fp)
{
  allocator->deallocate(fp);
}

unsigned long flx_collector_t::reap ()
{
  unsigned long count = 0;
  Word_t next=(Word_t)NULL;
  int res = Judy1First(j_tmp,&next,&je);
  while(res) {
    delete_frame((void *)(void*)next);
    ++count;
    res = Judy1Next(j_tmp,&next,&je);
  }
  Judy1FreeArray(&j_tmp,&je);
  if(debug)
    fprintf(stderr,"Reaped %lu objects\n",count);
  return count;
}

void flx_collector_t::mark(pthread::memory_ranges_t *px)
{
  if(debug)
    fprintf(stderr,"Collector: Running mark\n");
  assert (root_count == roots.size());

  if(px)
  {
    std::vector<pthread::memory_range_t>::iterator end = (*px).end();
    for(
      std::vector<pthread::memory_range_t>::iterator i = (*px).begin();
      i != end;
      ++i
    )
    {
      pthread::memory_range_t range = *i;
      if(debug)
        fprintf(stderr, "Conservate scan of memory %p->%p\n",range.b, range.e);
      void *end = range.e;
      for ( void *i = range.b; i != end; i = (void*)((void**)i+1))
      {
        //if(debug)
        //  fprintf(stderr, "Check if *%p=%p is a pointer\n",i,*(void**)i);
        scan_object(*(void**)i);
      }
      if(debug)
        fprintf(stderr, "DONE: Conservate scan of memory %p->%p\n",range.b, range.e);
    }
  }

  if(debug)
    fprintf(stderr, "Scanning roots\n");
  rootmap_t::iterator const end = roots.end();
  for(
    rootmap_t::iterator i = roots.begin();
    i != end;
    ++i
  )
  {
    if (debug)
      fprintf(stderr, "Scanning root %p\n", (*i).first);
    scan_object((*i).first);
  }
  if(debug)
    fprintf(stderr, "Done Scanning roots\n");
}



unsigned long flx_collector_t::sweep()
{
  if(debug)
    fprintf(stderr,"Collector: Sweep, garbage bit value=%d\n",(int)parity);
  unsigned long sweeped = 0;
  void *current = NULL;
  Word_t *pshape = (Word_t*)JudyLFirst(j_shape,(Word_t*)&current,&je);
  if(pshape==(Word_t*)PPJERR)judyerror("sweep");

  while(pshape!=NULL)
  {
    if((*pshape & 1) == (parity & 1UL))
    {
      if(debug)
        fprintf(stderr,"Garbage %p=%s\n",current,((gc_shape_t*)(*pshape & ~1UL))->cname);
      ++ sweeped;
      unlink(current);
      post_delete(current);
    }
    else
      if(debug)
        fprintf(stderr,"Reachable %p=%s\n",current,((gc_shape_t*)(*pshape & ~1UL))->cname);

    pshape = (Word_t*)JudyLNext(j_shape,(Word_t*)(void*)&current,&je);
  }

  parity = !parity;
  if(debug)
    fprintf(stderr,"Sweeped %ld\n",sweeped);
  return reap();
}

void flx_collector_t::impl_add_root(void *memory)
{
  if(!memory)
  {
    fprintf(stderr, "GC ERROR: ADD NULL ROOT\n");
    abort();
  }
  rootmap_t::iterator iter = roots.find(memory);
  if(iter == roots.end())
  {
    std::pair<void *const, unsigned long> entry(memory,1UL);
    roots.insert (entry);
    root_count++;
  }
  else
    ++(*iter).second;
}

void flx_collector_t::impl_remove_root(void *memory)
{
  rootmap_t::iterator iter = roots.find(memory);
  if(iter == roots.end())
  {
    fprintf(stderr, "GC ERROR: REMOVE ROOT WHICH IS NOT ROOT\n");
    abort();
  }
  if((*iter).second == 1UL)
  {
    roots.erase(iter);
    root_count--;
  }
  else
    --(*iter).second;
}

void flx_collector_t::scan_object(void *p)
{
  Word_t reachable = (parity & 1UL) ^ 1UL;
  if(debug)
    fprintf(stderr,"Scan object %p, reachable bit value = %d\n",p,(int)reachable);
  Word_t cand = (Word_t)p;
  Word_t fp=cand;
  Word_t *w = (Word_t*)JudyLLast(j_shape,&fp,&je);
  if(w==(Word_t*)PPJERR)judyerror("scan_object");
  if(w == NULL) return; // no lower object
  /*
  if(debug)
  {
    fprintf(stderr,"Found candidate object %p, &shape=%p, shape(1) %p\n",(void*)fp,(void*)w,(void*)(*w));
    fprintf(stderr," .. type=%s!\n",((gc_shape_t*)(*w & ~1UL))->cname);
  }
  */
  if( (*w & 1UL) == reachable) return;   // already handled

  gc_shape_t *shape = (gc_shape_t*)(*w & ~1UL);
  unsigned long n = get_count((void*)fp) * shape->count * shape->amt;
  if(cand >= (Word_t)(void*)((unsigned char*)(void*)fp+n)) return; // not interior
  if(debug)
    fprintf(stderr,"MARKING object %p, shape %p, type=%s\n",(void*)fp,shape,shape->cname);

  *w = (*w & ~1uL) | reachable;

  unsigned long n_used = get_used((void*)fp) * shape->count;
  std::size_t n_offsets = shape->n_offsets;
  std::size_t *offsets = shape->offsets;

  if(shape->flags & gc_flags_conservative)
  {
    // end of object, rounded down to size of a void*
    void **end = (void**)(
      (unsigned char*)(void*)fp +
      n_used * n / sizeof(void*) * sizeof(void*)
    );
    for ( void **i = (void**)p; i != end; i = i+1)
    {
      //if(debug)
      //  fprintf(stderr, "Check if *%p=%p is a pointer\n",i,*(void**)i);
      scan_object(*i);
    }
  }
  else
  {
    for(unsigned long j=0; j<n_used; ++j)
    {
      for(unsigned int i=0; i<n_offsets; ++i)
      {
        void **pq = (void**)(void*)((unsigned char*)p + offsets[i]);
        void *q = *pq;
        if(q)scan_object(q);
      }
      p=(void*)((unsigned char*)p+shape->amt);
    }
  }
}



unsigned long flx_collector_t::impl_collect()
{
  if(debug)
    fprintf(stderr,"Request to collect, thread %lx\n", (unsigned long)flx::pthread::get_current_native_thread());
  if (thread_control == NULL || thread_control->world_stop())
  {
    if(debug)
      fprintf(stderr,"Collecting, thread %lx\n", (unsigned long)flx::pthread::get_current_native_thread());
    pthread::memory_ranges_t * mr = thread_control? thread_control -> get_block_list() : NULL;
    mark(mr);
    delete mr;
    unsigned long collected = sweep();
    if(thread_control) thread_control->world_start();
    if(debug)
      fprintf(stderr,"FINISHED collect, thread %lx\n", (unsigned long)flx::pthread::get_current_native_thread());
    return collected;
  }
  else {
    if(debug)
      fprintf(stderr,"RACE: someone else is collecting, just yield\n");
    thread_control->yield();
    return 0ul;
  }
}

void flx_collector_t::impl_free_all_mem()
{
  //fprintf(stderr,"impl_free_all_mem -- freeing roots\n");
  roots.clear();
  root_count = 0;
  //fprintf(stderr,"freeing all heap with sweep()\n");
  sweep();
}

flx_collector_t::~flx_collector_t()
{
  //THIS IS VERY DANGEROUS! What if don't want to collect
  //the garbage for efficiency reasons???
  //
  // ELIDED .. already caused a bug!
  //
  //free_all_mem();
}

}}} // end namespaces
