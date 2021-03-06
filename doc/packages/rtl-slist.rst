Package: src/packages/rtl-slist.fdoc


=====
slist
=====

============= ===========================
key           file                        
============= ===========================
flx_slist.cpp share/src/rtl/flx_slist.cpp 
flx_slist.hpp share/lib/rtl/flx_slist.hpp 
============= ===========================


Singly linked list of pointers
==============================

Not used any more.


.. index:: slist_node_t(struct)
.. code-block:: cpp

  //[flx_slist.hpp]
  #ifndef __FLX_SLIST_H__
  #define __FLX_SLIST_H__
  #include "flx_rtl_config.hpp"
  #include "flx_gc.hpp"
  #include "flx_serialisers.hpp"
  
  namespace flx { namespace rtl {
  struct RTL_EXTERN slist_t;   // singly linked list of void*
  struct RTL_EXTERN slist_node_t;   // singly linked list of void*
  RTL_EXTERN extern ::flx::gc::generic::gc_shape_t slist_node_ptr_map;
  RTL_EXTERN extern ::flx::gc::generic::gc_shape_t slist_ptr_map;
  
  // ********************************************************
  /// SLIST. singly linked lists: SHARABLE and COPYABLE
  /// SLIST manages pointers to memory managed by the collector
  // ********************************************************
  
  struct RTL_EXTERN slist_node_t {
    slist_node_t *next;
    void *data;
    slist_node_t(slist_node_t *n, void *d) : next(n), data(d) {}
  };
  
  
  struct RTL_EXTERN slist_t {
    slist_t(){}
  
    gc::generic::gc_profile_t *gcp;
    struct slist_node_t *head;
  
    slist_t (gc::generic::gc_profile_t*); ///< create empty list
  
    void push(void *data);                ///< push a gc pointer
    void *pop();                          ///< pop a gc pointer
    bool isempty()const;
  };
  
  }}
  #endif
  

.. code-block:: cpp

  //[flx_slist.cpp]
  #include "flx_slist.hpp"
  namespace flx { namespace rtl {
  
  // ********************************************************
  // slist implementation
  // ********************************************************
  
  slist_t::slist_t(::flx::gc::generic::gc_profile_t *_gcp) : gcp (_gcp), head(0) {}
  
  bool slist_t::isempty()const { return head == 0; }
  
  void slist_t::push(void *data)
  {
    head = new(*gcp,slist_node_ptr_map,false) slist_node_t(head,data);
  }
  
  // note: never fails, return NULL pointer if the list is empty
  void *slist_t::pop()
  {
    if(head) {
      void *data = head->data;
      head=head->next;
      return data;
    }
    else return 0;
  }
  
  // ********************************************************
  //OFFSETS for slist_node_t
  // ********************************************************
  static const ::flx::gc::generic::offset_entry_t slist_node_offsets[2]={
      {offsetof(slist_node_t,next),nullptr},
      {offsetof(slist_node_t,data),nullptr}
  };
  
  static ::flx::gc::generic::offset_data_t const slist_node_offset_data = { 2, slist_node_offsets };
  ::flx::gc::generic::gc_shape_t slist_node_ptr_map = {
    "rtl::slist_node_t",
    1,sizeof(slist_node_t),
    0, // no finaliser,
    0, // fcops
    &slist_node_offset_data,
    ::flx::gc::generic::scan_by_offsets,
    ::flx::gc::generic::tblit<slist_node_t>,::flx::gc::generic::tunblit<slist_node_t>, 
    ::flx::gc::generic::gc_flags_default,
    0UL, 0UL
  };
  
  
  // ********************************************************
  //OFFSETS for slist_t
  // ********************************************************
  static const ::flx::gc::generic::offset_entry_t slist_offsets[1]={
      {offsetof(slist_t,head),nullptr}
  };
  static ::flx::gc::generic::offset_data_t const slist_offset_data = { 1, slist_offsets };
  
  static CxxValueType<slist_t> _slist_t_fcops {};
  
  ::flx::gc::generic::gc_shape_t slist_ptr_map = {
    "rtl::slist_t",
    1,sizeof(slist_t),
    0, // no finaliser
    &_slist_t_fcops, // fcops
    &slist_offset_data,
    ::flx::gc::generic::scan_by_offsets,
    ::flx::gc::generic::tblit<slist_t>,::flx::gc::generic::tunblit<slist_t>, 
    ::flx::gc::generic::gc_flags_default,
    0UL, 0UL
  };
  
  }}
  


