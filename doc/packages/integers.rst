Package: src/packages/integers.fdoc


=======================
Operations on integers.
=======================

========== ============================
key        file                         
========== ============================
int.flx    share/lib/std/scalar/int.flx 
========== ============================



Conversion operators.
=====================



.. index:: Tiny(class)
.. index:: tiny(ctor)
.. index:: Short(class)
.. index:: short(ctor)
.. index:: short(ctor)
.. index:: Int(class)
.. index:: int(ctor)
.. index:: int(ctor)
.. index:: int(ctor)
.. index:: Long(class)
.. index:: long(ctor)
.. index:: long(ctor)
.. index:: Vlong(class)
.. index:: vlong(ctor)
.. index:: vlong(ctor)
.. index:: Utiny(class)
.. index:: utiny(ctor)
.. index:: utiny(ctor)
.. index:: Ushort(class)
.. index:: ushort(ctor)
.. index:: ushort(ctor)
.. index:: Uint(class)
.. index:: uint(ctor)
.. index:: uint(ctor)
.. index:: Ulong(class)
.. index:: ulong(ctor)
.. index:: ulong(ctor)
.. index:: Uvlong(class)
.. index:: uvlong(ctor)
.. index:: uvlong(ctor)
.. index:: Int8(class)
.. index:: int8(ctor)
.. index:: int8(ctor)
.. index:: Int16(class)
.. index:: int16(ctor)
.. index:: int16(ctor)
.. index:: Int32(class)
.. index:: int32(ctor)
.. index:: int32(ctor)
.. index:: Int64(class)
.. index:: int64(ctor)
.. index:: int64(ctor)
.. index:: Uint8(class)
.. index:: uint8(ctor)
.. index:: uint8(ctor)
.. index:: Uint16(class)
.. index:: uint16(ctor)
.. index:: uint16(ctor)
.. index:: Uint32(class)
.. index:: uint32(ctor)
.. index:: uint32(ctor)
.. index:: Uint64(class)
.. index:: uint64(ctor)
.. index:: uint64(ctor)
.. index:: Uint128(class)
.. index:: uint128(ctor)
.. index:: uint128(ctor)
.. index:: Uint256(class)
.. index:: uint256(ctor)
.. index:: uint256(ctor)
.. index:: Size(class)
.. index:: size(ctor)
.. index:: size(ctor)
.. index:: Ptrdiff(class)
.. index:: ptrdiff(ctor)
.. index:: Intptr(class)
.. index:: intptr(ctor)
.. index:: Uintptr(class)
.. index:: uintptr(ctor)
.. index:: Intmax(class)
.. index:: intmax(ctor)
.. index:: Uintmax(class)
.. index:: uintmax(ctor)
.. code-block:: felix

  //[int.flx]
  include "std/scalar/int256";
  
  open class Tiny
  {
    ctor tiny: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] tiny: T = "static_cast<#0>($1)/*int.flx: ctor*/";
  }
  
  open class Short
  {
    ctor short: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] short: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor short: short = "$1";
  }
  
  open class Int
  {
    ctor int: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] int: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor int : int = "$1";
    // special hack
    ctor int(x:bool)=> match x with | true => 1 | false => 0 endmatch;
  }
  
  open class Long
  {
    ctor long: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] long: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor long: long = "$1";
  }
  
  open class Vlong
  {
    ctor vlong: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] vlong: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor vlong: vlong = "$1";
  }
  
  open class Utiny
  {
    ctor utiny: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] utiny: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor utiny: utiny = "$1";
  }
  
  open class Ushort
  {
    ctor ushort: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] ushort: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor ushort: ushort= "$1";
  }
  
  open class Uint
  {
    ctor uint: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] uint: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor uint: uint= "$1";
  }
  
  open class Ulong
  {
    ctor ulong: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] ulong: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor ulong: ulong= "$1";
  }
  
  open class Uvlong
  {
    ctor uvlong: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] uvlong: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor uvlong: uvlong= "$1";
  }
  
  open class Int8
  {
    ctor int8: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] int8: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor int8: int8= "$1";
  }
  
  open class Int16
  {
    ctor int16: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] int16: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor int16: int16= "$1";
  }
  
  open class Int32
  {
    ctor int32: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] int32: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor int32: int32= "$1";
  }
  
  open class Int64
  {
    ctor int64: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] int64: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor int64: int64= "$1 /*int64 ident*/";
  }
  
  open class Uint8
  {
    ctor uint8: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] uint8: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor uint8: uint8= "$1";
  }
  
  open class Uint16
  {
    ctor uint16: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] uint16: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor uint16: uint16= "$1";
  }
  
  open class Uint32
  {
    ctor uint32: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] uint32: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor uint32: uint32= "$1";
  }
  
  open class Uint64
  {
    ctor uint64: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] uint64: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor uint64: uint64= "$1";
  }
  
  open class Uint128
  {
    ctor uint128: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] uint128: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor uint128: uint128= "$1";
  }
  
  
  open class Uint256
  {
    ctor uint256: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] uint256: T = "static_cast<#0>($1)/*int.flx: ctor*/";
    ctor uint256: uint256= "$1";
  }
  
  
  open class Size
  {
    ctor size: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] size: T = "static_cast<#0>($1)/*int.flx: ctor size from #0*/";
    ctor size: size = "($1)/*int.flx: ctor size IDENT*/";
  
    // special overrides so s.len - 1 works
    fun - : size * int -> size = "$1-$2";
    fun + : size * int -> size = "$1+$2";
  }
  
  open class Ptrdiff
  {
    ctor ptrdiff: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] ptrdiff: T = "static_cast<#0>($1)/*int.flx: ctor*/";
  }
  
  open class Intptr
  {
    ctor intptr: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] intptr: T = "static_cast<#0>($1)/*int.flx: ctor*/";
  }
  
  open class Uintptr
  {
    ctor uintptr: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] uintptr: T = "static_cast<#0>($1)/*int.flx: ctor*/";
  }
  
  open class Intmax 
  {
    ctor intmax: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] intmax: T = "static_cast<#0>($1)/*int.flx: ctor*/";
  }
  
  open class Uintmax
  {
    ctor uintmax: string = "static_cast<#0>(::std::atoi($1.c_str()))" requires Cxx_headers::cstdlib;
    ctor[T in reals] uintmax: T = "static_cast<#0>($1)/*int.flx: ctor*/";
  }
  
  
Convert to decimal string.
==========================



.. index:: str(fun)
.. index:: str(fun)
.. index:: str(fun)
.. index:: str(fun)
.. index:: str(fun)
.. code-block:: felix

  //[int.flx]
  instance Str[tiny] {
    fun str: tiny -> string = "::flx::rtl::strutil::str<int>($1)" requires package "flx_strutil";
  }
  
  instance Str[utiny] {
    fun str: utiny -> string = "::flx::rtl::strutil::str<unsigned int>($1)" requires package "flx_strutil";
  }
  instance Str[int8] {
    fun str: int8 -> string = "::flx::rtl::strutil::str<int>($1)" requires package "flx_strutil";
  }
  
  instance Str[uint8] {
    fun str: uint8-> string = "::flx::rtl::strutil::str<unsigned int>($1)" requires package "flx_strutil";
  }
  
  instance
  [
    T in 
      short \cup ushort \cup int \cup uint \cup long \cup ulong \cup vlong \cup uvlong \cup 
      exact_ints \cup weird_sints \cup weird_uints
  ] 
  Str[T] 
  {
    fun str: T -> string = "::flx::rtl::strutil::str<#1>($1)" requires package "flx_strutil";
  }
  
  fun hex[T]: T -> string = '(::flx::rtl::strutil::fmt_hex<#1>($1))' requires package "flx_strutil";
  fun hex: tiny -> string = '(::flx::rtl::strutil::fmt_hex((int)$1))' requires package "flx_strutil";
  fun hex: utiny -> string = '(::flx::rtl::strutil::fmt_hex((unsigned int)$1)+"UTINY")' requires package "flx_strutil";
  fun hex: int8 -> string = '(::flx::rtl::strutil::fmt_hex((int)$1))' requires package "flx_strutil";
  fun hex: uint8 -> string = '(::flx::rtl::strutil::fmt_hex((unsigned int)$1)+"UINT8")' requires package "flx_strutil";
  
Convert to lexical string.
==========================



.. code-block:: felix

  //[int.flx]
  instance Repr[tiny]   { fun repr[with Str[tiny]]   (t:tiny)   : string => (str t) + "t";  }
  instance Repr[short]  { fun repr[with Str[short]]  (t:short)  : string => (str t) + "s";  }
  instance Repr[int]   { fun repr[with Str[int]]   (t:int)   : string => (str t) + "";  }
  instance Repr[long]   { fun repr[with Str[long]]   (t:long)   : string => (str t) + "l";  }
  instance Repr[vlong]  { fun repr[with Str[vlong]]  (t:vlong)  : string => (str t) + "v";  }
  instance Repr[int8]  { fun repr[with Str[int8]]  (t:int8)  : string => (str t) + "i8";  }
  instance Repr[int16]  { fun repr[with Str[int16]]  (t:int16)  : string => (str t) + "i16";  }
  instance Repr[int32]  { fun repr[with Str[int32]]  (t:int32)  : string => (str t) + "i32";  }
  instance Repr[int64]  { fun repr[with Str[int64]]  (t:int64)  : string => (str t) + "i64";  }
  instance Repr[intmax]  { fun repr[with Str[intmax]]  (t:intmax)  : string => (str t) + "j";  }
  instance Repr[intptr]  { fun repr[with Str[intptr]]  (t:intptr)  : string => (str t) + "p";  }
  instance Repr[ptrdiff]  { fun repr[with Str[ptrdiff]]  (t:ptrdiff)  : string => (str t) + "d";  }
  
  instance Repr[utiny]  { fun repr[with Str[utiny]]  (t:utiny)  : string => (str t) + "ut"; }
  instance Repr[ushort] { fun repr[with Str[ushort]] (t:ushort) : string => (str t) + "us"; }
  instance Repr[uint]   { fun repr[with Str[uint]]   (t:uint)   : string => (str t) + "u";  }
  instance Repr[ulong]  { fun repr[with Str[ulong]]  (t:ulong)  : string => (str t) + "ul"; }
  instance Repr[uvlong] { fun repr[with Str[uvlong]] (t:uvlong) : string => (str t) + "uv"; }
  instance Repr[uint8]  { fun repr[with Str[uint8]]  (t:uint8)  : string => (str t) + "u8";  }
  instance Repr[uint16]  { fun repr[with Str[uint16]]  (t:uint16)  : string => (str t) + "u16";  }
  instance Repr[uint32]  { fun repr[with Str[uint32]]  (t:uint32)  : string => (str t) + "u32";  }
  instance Repr[uint64]  { fun repr[with Str[uint64]]  (t:uint64)  : string => (str t) + "u64";  }
  instance Repr[size]  { fun repr[with Str[size]]  (t:size)  : string => (str t) + "uz";  }
  instance Repr[uintmax]  { fun repr[with Str[uintmax]]  (t:uintmax)  : string => (str t) + "uj";  }
  instance Repr[uintptr]  { fun repr[with Str[uintptr]]  (t:uintptr)  : string => (str t) + "up";  }
  
  
Methods of integers
===================



.. index:: succ(fun)
.. index:: pre_incr(proc)
.. index:: post_incr(proc)
.. index:: pred(fun)
.. index:: pre_decr(proc)
.. index:: post_decr(proc)
.. index:: advance(fun)
.. index:: maxval(fun)
.. index:: minval(fun)
.. code-block:: felix

  //[int.flx]
  instance[t in ints] Addgrp[t] {}
  instance[t in ints] Ring[t] {}
  instance[t in ints] MultSemi1[t] {}
  instance[t in ints] Dring[t] {}
  
  instance [t in uints] Bits [t] {
    fun \^ : t * t -> t = "(?1)($1^$2)";
    fun \| : t * t -> t = "(?1)($1|$2)";
    fun \& : t * t -> t = "(?1)($1&$2)";
  
    // note: the cast is essential to ensure ~1tu is 254tu
    fun ~ : t -> t = "(?1)~$1";
    proc ^= : &t * t = "*$1^=$2;";
    proc |= : &t * t = "*$1|=$2;";
    proc &= : &t * t = "*$1&=$2;";
  }
  
  instance[t in ints] ForwardSequence[t] {
    fun succ: t -> t = "$1+1";
    proc pre_incr: &t = "++*$1;";
    proc post_incr: &t = "(*$1)++;";
  }
  
  instance[t in ints] BidirectionalSequence[t] {
    fun pred: t -> t = "$1-1";
    proc pre_decr: &t = "--*$1;";
    proc post_decr: &t = "(*$1)--;";
  }
  instance[t in ints] RandomSequence[t] {
    fun advance: int * t -> t = "$1+$2";
  }
  instance[t in ints] UpperBoundTotalOrder[t] {
    fun maxval: 1 -> t = "::std::numeric_limits<?1>::max()";
  }
  instance[t in ints] LowerBoundTotalOrder[t] {
    fun minval: 1 -> t = "::std::numeric_limits<?1>::min()";
  }
  
  instance[t in ints] Integer[t] {
    fun << : t * t -> t = "$1<<$2";
    fun >> : t * t -> t = "$1>>$2";
  }
  
Methods of signed integers
==========================



.. index:: sgn(fun)
.. index:: abs(fun)
.. code-block:: felix

  //[int.flx]
  instance[t in sints] Signed_integer[t] {
    fun sgn: t -> int = "$1<0??-1:$1>0??1:0";
    fun abs: t -> t = "$1<0??-$1:$1";
  }
  
Methods of unsigned integers
============================



.. code-block:: felix

  //[int.flx]
  instance[t in uints] Unsigned_integer[t] {}
  
Make functions accessible without qualification
===============================================



.. code-block:: felix

  //[int.flx]
  //open[T in sints] Signed_integer[T];
  open Signed_integer[tiny];
  open Signed_integer[short];
  open Signed_integer[int];
  open Signed_integer[long];
  open Signed_integer[vlong];
  open Signed_integer[int8];
  open Signed_integer[int16];
  open Signed_integer[int32];
  open Signed_integer[int64];
  open Signed_integer[intmax];
  open Signed_integer[ptrdiff];
  open Signed_integer[intptr];
  
  //open[T in uints] Unsigned_integer[T];
  open Unsigned_integer[utiny];
  open Unsigned_integer[ushort];
  open Unsigned_integer[uint];
  open Unsigned_integer[ulong];
  open Unsigned_integer[uvlong];
  open Unsigned_integer[uint8];
  open Unsigned_integer[uint16];
  open Unsigned_integer[uint32];
  open Unsigned_integer[uint64];
  open Unsigned_integer[uint128];
  open Unsigned_integer[uint256];
  open Unsigned_integer[uintmax];
  open Unsigned_integer[size];
  open Unsigned_integer[uintptr];
  
Integer Subtyping Rules
=======================


.. code-block:: felix

  //[int.flx]
  
  supertype vlong: long = "(long long)$1";
  supertype long: int = "(long)$1";
  supertype int : short= "(int)$1";
  supertype short : tiny = "(short)$1";
  
  supertype int64: int32 = "(int64_t)$1";
  supertype int32 : int16 = "(int32_t)$1";
  supertype int16 : int8 =  "(int16_t)$1";
  
  /* currently breaks instance Str[fcomplex] for unknown reason! 
  
  But almost certainly its because of the definition of complex[t]
  by a type match, plus, then open[t in floats] Complex[complex[t],t]
  */
  /*
  supertype fcomplex: float = "::std::complex<float>($1)";
  supertype dcomplex: double = "::std::complex<double>($1)";
  supertype lcomplex: ldouble = "::std::complex<long double>($1)";
  
  Guessing name map contains unreduced type match ... indeed I think
  it HAS to, because there is no provision in the type map data structure
  for constraints. This is why above
  
  open[T in units] Unsigned_integer[T] is commented out.
  
  open supports specialisations but not constraints including typeset constraints
  
  However we don't open Complex with a constraint. The instances use
  constraints but this is unrelated to the failure.
  */
  
  
