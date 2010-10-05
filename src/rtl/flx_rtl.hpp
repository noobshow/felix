#ifndef __FLX_RTL_H__
#define __FLX_RTL_H__

#include "flx_rtl_config.hpp"
#include "flx_meta.hpp"
#include "flx_exceptions.hpp"
#include "flx_gc.hpp"

// temporary compatibility hack
#include "flx_compiler_support_headers.hpp"
#include "flx_compiler_support_bodies.hpp"

#include <string>
#include <functional>

namespace flx { namespace rtl {

// ********************************************************
// Felix system classes
// ********************************************************

struct RTL_EXTERN con_t;     // continuation
struct RTL_EXTERN fthread_t; // f-thread
struct RTL_EXTERN _uctor_;   // union constructor
struct RTL_EXTERN schannel_t;   // synchronous channel type
struct RTL_EXTERN slist_t;   // singly linked list of void*

struct RTL_EXTERN unit {};   // unit
  // INLINE DEFINITION, PROBLEMATIC!!

// ********************************************************
// Shape (RTTI) objects for system classes
// con_t is only an abstract base, so has no fixed shape
// shapes for instance types generated by Felix compiler
// we provide a shape for C 'int' type as well
// ********************************************************

RTL_EXTERN extern ::flx::gc::generic::gc_shape_t _fthread_ptr_map;
RTL_EXTERN extern ::flx::gc::generic::gc_shape_t schannel_ptr_map;
RTL_EXTERN extern ::flx::gc::generic::gc_shape_t _uctor_ptr_map;
RTL_EXTERN extern ::flx::gc::generic::gc_shape_t _int_ptr_map;
RTL_EXTERN extern ::flx::gc::generic::gc_shape_t _address_ptr_map;
RTL_EXTERN extern ::flx::gc::generic::gc_shape_t unit_ptr_map;
RTL_EXTERN extern ::flx::gc::generic::gc_shape_t slist_ptr_map;

// ********************************************************
/// CONTINUATION.
// ********************************************************

struct RTL_EXTERN con_t ///< abstract base for mutable continuations
{
  FLX_PC_DECL               ///< interior program counter
  _uctor_ *p_svc;           ///< pointer to service request

  con_t();                  ///< initialise pc, p_svc to 0
  virtual con_t *resume()=0;///< method to perform a computational step
  virtual ~con_t();
  con_t * _caller;          ///< callers continuation (return address)
};

// ********************************************************
/// SLIST. singly linked lists: SHARABLE and COPYABLE
/// SLIST manages pointers to memory managed by the collector
// ********************************************************

struct RTL_EXTERN slist_t {
  gc::generic::gc_profile_t *gcp;
  struct slist_node_t *head;

  slist_t (gc::generic::gc_profile_t*); ///< create empty list
  slist_t (slist_t const &);            ///< shallow copy

  void push(void *data);                ///< push a gc pointer
  void *pop();                          ///< pop a gc pointer
  bool isempty()const;
};

// ********************************************************
/// FTHREAD. Felix threads
// ********************************************************

struct RTL_EXTERN fthread_t // fthread abstraction
{
  con_t *cc;                    ///< current continuation

  fthread_t();                  ///< dead thread, suitable for assignment
  fthread_t(con_t*);            ///< make thread from a continuation
  _uctor_ *run();               ///< run until dead or driver service request
  void kill();                  ///< kill by detaching the continuation
  _uctor_ *get_svc()const;      ///< get current service request of waiting thread
private: // uncopyable
  fthread_t(fthread_t const&);
  void operator=(fthread_t const&);
};

// ********************************************************
/// SCHANNEL. Synchronous channels
// ********************************************************

struct RTL_EXTERN schannel_t
{
  slist_t *waiting_to_read;             ///< fthreads waiting for a writer
  slist_t *waiting_to_write;            ///< fthreads waiting for a reader
  schannel_t(gc::generic::gc_profile_t*);
  void push_reader(fthread_t *);        ///< add a reader
  fthread_t *pop_reader();              ///< pop a reader, NULL if none
  void push_writer(fthread_t *);        ///< add a writer
  fthread_t *pop_writer();              ///< pop a writer, NULL if none
private: // uncopyable
  schannel_t(schannel_t const&);
  void operator= (schannel_t const&);
};

// ********************************************************
/// VARIANTS. Felix union type
/// note: non-polymorphic, so ctor can be inline
// ********************************************************

struct RTL_EXTERN _uctor_
{
  int variant;  ///< Variant code
  void *data;   ///< Heap variant constructor data
  _uctor_() : variant(-1), data(0) {}
  _uctor_(int i, void *d) : variant(i), data(d) {}
  _uctor_(int *a, _uctor_ x) : variant(a[x.variant]), data(x.data) {}
};


// ********************************************************
// SERVICE REQUEST CODE
// THESE VALUES MUST SYNCH WITH THE STANDARD LIBRARY
// ********************************************************

enum svc_t               // what the dispatch should do
{                        // when the resume callback returns
  svc_yield = 0,
  svc_get_fthread=1,
  svc_read=2,
  svc_general=3,         // temporary hack by RF
  svc_reserved=4,
  svc_spawn_pthread=5,
  svc_spawn_detached=6,
  svc_sread=7,           // synchronous read
  svc_swrite=8,          // synchronous write
  svc_kill=9,           // kill fthread
  svc_collect=10,        // run collector
  svc_end
};

struct readreq_t {
  schannel_t *chan;
  void *variable;
};

struct flx_trace_t
{
  unsigned long count;
  int enable_trace;
};

extern RTL_EXTERN int flx_enable_trace;

RTL_EXTERN void flx_trace(flx_trace_t* tr,flx_range_srcref_t sr, char const *file, int line, char const *msg);

}} // namespaces

#endif
