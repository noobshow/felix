Package: src/packages/cheaders.fdoc


=========
C Headers
=========


Headers
=======

To use the facilities of C conveniently we first define some
classes naming the standard header files.

The  :code:`class` construction provides a namespace.

The contained  :code:`header` specification provides
a tag name for a C include line. A use of a 
type or function lifted from C depending on the
inclusion of the header text causes the Felix compiler
to emit the header text.


C Standards.
============

Each newer C Standard adds some header files.
The  :code:`inherit` statement is used to include the headers
from the previous standard into a more recent one.


C89 Standard.
-------------

The original ANSI Standard blessed as an ISO Standard.


.. index:: C89_headers(class)
.. index:: assert_h(header)
.. index:: ctype_h(header)
.. index:: errno_h(header)
.. index:: float_h(header)
.. index:: limits_h(header)
.. index:: locale_h(header)
.. index:: math_h(header)
.. index:: setjmp_h(header)
.. index:: signal_h(header)
.. index:: stdarg_h(header)
.. index:: stddef_h(header)
.. index:: stdio_h(header)
.. index:: stdlib_h(header)
.. index:: string_h(header)
.. index:: time_h(header)
.. code-block:: text

  // reference: Wikipedia: http://en.wikibooks.org/wiki/C_Programming/Reference_Tables#List_of_Standard_Headers 
  
  // ANSI C89 = ISO C90
  class C89_headers 
  {
    header assert_h =   "#include <assert.h>";
    header ctype_h =    "#include <ctype.h>";
    header errno_h =    "#include <errno.h>";
    header float_h =    "#include <float.h>";
    header limits_h =   "#include <limits.h>";
    header locale_h =   "#include <locale.h>";
    header math_h =     "#include <math.h>";
    header setjmp_h =   "#include <setjmp.h>";
    header signal_h =   "#include <signal.h>";
    header stdarg_h =   "#include <stdarg.h>";
    header stddef_h =   "#include <stddef.h>";
    header stdio_h =    "#include <stdio.h>";
    header stdlib_h =   "#include <stdlib.h>";
    header string_h =   "#include <string.h>";
    header time_h =     "#include <time.h>";
  }


C95 Amendment
-------------

Added support for wide characters.

.. index:: C95_headers(class)
.. index:: iso646_h(header)
.. index:: wchar_h(header)
.. index:: wctype_h(header)
.. code-block:: text

  // ISO C94/95 Amendment 1
  class C95_headers  
  {
    inherit C89_headers;
    header iso646_h =   "#include <iso646.h>";
    header wchar_h =    "#include <wchar.h>";
    header wctype_h =   "#include <wctype.h>";
  }


C99 Standard
------------

Added support for complex, exact integer types and
bool.

.. index:: C99_headers(class)
.. index:: complex_h(header)
.. index:: fenv_h(header)
.. index:: inttypes_h(header)
.. index:: wctype_h(header)
.. index:: stdbool_h(header)
.. index:: stdint_h(header)
.. index:: tgmath_h(header)
.. code-block:: text

  // ISO C99
  class C99_headers 
  {
    inherit C95_headers;
    header complex_h =  "#include <complex.h>";
    header fenv_h =     "#include <fenv.h>";
    header inttypes_h = "#include <inttypes.h>";
    header wctype_h =   "#include <wctype.h>";
    header stdbool_h =  "#include <stdbool.h>";
    header stdint_h =   "#include <stdint.h>";
    header tgmath_h =   "#include <tgmath.h>";
  }



C++ Standards.
==============

Each newer C++ Standard adds some header files.
The  :code:`inherit` statement is used to include the headers
from the previous standard into a more recent one.


C++90 Standard
--------------

The original C++ Standard.


.. index:: Cxx_headers(class)
.. index:: exception(header)
.. index:: limits(header)
.. index:: new(header)
.. index:: typeinfo(header)
.. index:: stdexcept(header)
.. index:: utility(header)
.. index:: memory(header)
.. index:: string(header)
.. index:: locale(header)
.. index:: functional(header)
.. index:: algorithm(header)
.. index:: bitset(header)
.. index:: deque(header)
.. index:: iterator(header)
.. index:: list(header)
.. index:: map(header)
.. index:: set(header)
.. index:: stack(header)
.. index:: vector(header)
.. index:: complex(header)
.. index:: numeric(header)
.. index:: valarray(header)
.. index:: fstream(header)
.. index:: iomanip(header)
.. index:: ios(header)
.. index:: iosfwd(header)
.. index:: iostream(header)
.. index:: istream(header)
.. index:: ostream(header)
.. index:: streambuf(header)
.. index:: sstream(header)
.. index:: cassert(header)
.. index:: cctype(header)
.. index:: cerrno(header)
.. index:: cfloat(header)
.. index:: ciso646(header)
.. index:: climits(header)
.. index:: clocale(header)
.. index:: cmath(header)
.. index:: csetjmp(header)
.. index:: csignal(header)
.. index:: cstdarg(header)
.. index:: cstdio(header)
.. index:: cstdlib(header)
.. index:: cstring(header)
.. index:: ctime(header)
.. index:: cwchar(header)
.. index:: cwctype(header)
.. code-block:: text

  class Cxx_headers
  {
    header exception = '#include <exception>';
    header limits = '#include <limits>';
    header new = '#include <new>';
    header typeinfo = '#include <typeinfo>';
    header stdexcept = '#include <stdexcept>';
    header utility = '#include <utility>';
    header memory = '#include <memory>';
    header string = '#include <string>';
    header locale = '#include <locale>';
  
  // STL
    header functional = '#include <functional>';
    header algorithm = '#include <algorithm>';
    header bitset = '#include <bitset>';
    header deque = '#include <deque>';
    header iterator = '#include <iterator>';
    header list = '#include <list>';
    header map = '#include <map>';
    header set = '#include <set>';
    header stack = '#include <stack>';
    header vector = '#include <vector>';
    header complex = '#include <complex>';
    header numeric = '#include <numeric>';
    header valarray = '#include <valarray>';
  
  // I/O
    header fstream = '#include <fstream>';
    header iomanip = '#include <iomanip>';
    header ios = '#include <ios>';
    header iosfwd = '#include <iosfwd>';
    header iostream = '#include <iostream>';
    header istream = '#include <istream>';
    header ostream = '#include <ostream>';
    header streambuf = '#include <streambuf>';
    header sstream = '#include <sstream>';
  
  // ISO C wrappers
    header cassert = '#include <cassert>';
    header cctype = '#include <cctype>';
    header cerrno = '#include <cerrno>';
    header cfloat = '#include <cfloat>';
    header ciso646 = '#include <ciso646>';
    header climits = '#include <climits>';
    header clocale = '#include <clocale>';
    header cmath = '#include <cmath>';
    header csetjmp = '#include <csetjmp>';
    header csignal = '#include <csignal>';
    header cstdarg = '#include <cstdarg>';
    header cstdio = '#include <cstdio>';
    header cstdlib = '#include <cstdlib>';
    header cstring = '#include <cstring>';
    header ctime = '#include <ctime>';
    header cwchar = '#include <cwchar>';
    header cwctype = '#include <cwctype>';
  }
  
C++11 Standard.
---------------

A more recent standard from 2011. Added a huge number
of new features.

.. index:: Cxx11_headers(class)
.. index:: system_error(header)
.. index:: typeidex(header)
.. index:: type_traits(header)
.. index:: chrono(header)
.. index:: initialiser_list(header)
.. index:: tuple(header)
.. index:: scope_allocator(header)
.. index:: cuchar(header)
.. index:: array(header)
.. index:: forward_list(header)
.. index:: unordered_set(header)
.. index:: unordered_map(header)
.. index:: ratio(header)
.. index:: cfenv(header)
.. index:: codecvt(header)
.. index:: regex(header)
.. index:: random(header)
.. index:: atomic(header)
.. index:: thread(header)
.. index:: mutex(header)
.. index:: future(header)
.. index:: condition_variable(header)
.. index:: ctgmath(header)
.. index:: cstdalign(header)
.. index:: cstdbool(header)
.. code-block:: text

  class Cxx11_headers  // http://en.cppreference.com/w/cpp/header
  {
    inherit Cxx_headers;
    header system_error = '#include <system_error>'; // std=?
    header typeidex = '#include <typeindex>';
    header type_traits = '#include <type_traits>';
    header chrono = '#include <chrono>';
    header initialiser_list = '#include <initialiser_list>';
    header tuple = '#include <tuple>';
    header scope_allocator = '#include <tuple>';
    header cuchar = '#include <cuchar>';
    header array = '#include <array>';
    header forward_list = '#include <forward_list>';
    header unordered_set = '#include <unordered_set>';
    header unordered_map = '#include <unordered_map>';
    header ratio = '#include <ratio>';
    header cfenv= '#include <ratio>';
    header codecvt = '#include <codecvt>';
    header regex = '#include <regex>';
    header random = '#include <random>';
    header atomic = '#include <atomic>';
    header thread = '#include <thread>';
    header mutex = '#include <mutex>';
    header future = '#include <future>';
    header condition_variable = '#include <condition_variable>';
    header ctgmath = '#include <ctgmath>';
    header cstdalign = '#include <cstdalign>';
    header cstdbool = '#include <cstdbool>';
  }


Posix
=====

There are multiple Posix standards but we just include headers
from the most recent, most final one.


.. index:: Posix_headers(class)
.. index:: aio_h(header)
.. index:: arpa_inet_h(header)
.. index:: cpio_h(header)
.. index:: dirent_h(header)
.. index:: dlfcn_h(header)
.. index:: fcntl_h(header)
.. index:: fmtmsg_h(header)
.. index:: fnmatch_h(header)
.. index:: ftw_h(header)
.. index:: glob_h(header)
.. index:: grp_h(header)
.. index:: iconv_h(header)
.. index:: langinfo_h(header)
.. index:: libgen_h(header)
.. index:: monetary_h(header)
.. index:: mqueue_h(header)
.. index:: ndbm_h(header)
.. index:: net_if_h(header)
.. index:: netdb_h(header)
.. index:: netinet_in_h(header)
.. index:: netinet_tcp_h(header)
.. index:: nl_types_h(header)
.. index:: poll_h(header)
.. index:: pthread_h(header)
.. index:: pwd_h(header)
.. index:: regex_h(header)
.. index:: sched_h(header)
.. index:: search_h(header)
.. index:: semaphore_h(header)
.. index:: spawn_h(header)
.. index:: strings_h(header)
.. index:: stropts_h(header)
.. index:: sys_ipc_h(header)
.. index:: sys_mman_h(header)
.. index:: sys_msg_h(header)
.. index:: sys_resource_h(header)
.. index:: sys_select_h(header)
.. index:: sys_sem_h(header)
.. index:: sys_shm_h(header)
.. index:: sys_socket_h(header)
.. index:: sys_stat_h(header)
.. index:: sys_statvfs_h(header)
.. index:: sys_time_h(header)
.. index:: sys_times_h(header)
.. index:: sys_types_h(header)
.. index:: sys_uio_h(header)
.. index:: sys_un_h(header)
.. index:: sys_utsname_h(header)
.. index:: sys_wait_h(header)
.. index:: syslog_h(header)
.. index:: tar_h(header)
.. index:: termios_h(header)
.. index:: trace_h(header)
.. index:: ulimit_h(header)
.. index:: unistd_h(header)
.. index:: utime_h(header)
.. index:: utmpx_h(header)
.. index:: wordexp_h(header)
.. code-block:: text

  class Posix_headers {
    header aio_h = "#include <aio.h>";
    header arpa_inet_h = "#include <arpa/inet.h>";
    header cpio_h = "#include <cpio.h>";
    header dirent_h = "#include <dirent.h>";
    header dlfcn_h = "#include <dlfcn.h>";
    header fcntl_h = "#include <fcntl.h>";
    header fmtmsg_h = "#include <fmtmsg.h>";
    header fnmatch_h = "#include <fnmatch.h>";
    header ftw_h = "#include <ftw.h>";
    header glob_h = "#include <glob.h>";
    header grp_h = "#include <grp.h>";
    header iconv_h = "#include <iconv.h>";
    header langinfo_h = "#include <langinfo.h>";
    header libgen_h = "#include <libgen.h>";
    header monetary_h = "#include <monetary.h>";
    header mqueue_h = "#include <mqueue.h>";
    header ndbm_h = "#include <ndbm.h>";
    header net_if_h = "#include <net/if.h>";
    header netdb_h = "#include <netdb.h>";
    header netinet_in_h = "#include <netinet/in.h>";
    header netinet_tcp_h = "#include <netinet/tcp.h>";
    header nl_types_h = "#include <nl_types.h>";
    header poll_h = "#include <poll.h>";
    header pthread_h = "#include <pthread.h>";
    header pwd_h = "#include <pwd.h>";
    header regex_h = "#include <regex.h>";
    header sched_h = "#include <sched.h>";
    header search_h = "#include <search.h>";
    header semaphore_h = "#include <semaphore.h>";
    header spawn_h = "#include <spawn.h>";
    header strings_h = "#include <strings.h>";
    header stropts_h = "#include <stropts.h>";
    header sys_ipc_h = "#include <sys/ipc.h>";
    header sys_mman_h = "#include <sys/mman.h>";
    header sys_msg_h = "#include <sys/msg.h>";
    header sys_resource_h = "#include <sys/resource.h>";
    header sys_select_h = "#include <sys/select.h>";
    header sys_sem_h = "#include <sys/sem.h>";
    header sys_shm_h = "#include <sys/shm.h>";
    header sys_socket_h = "#include <sys/socket.h>";
    header sys_stat_h = "#include <sys/stat.h>";
    header sys_statvfs_h = "#include <sys/statvfs.h>";
    header sys_time_h = "#include <sys/time.h>";
    header sys_times_h = "#include <sys/times.h>";
    header sys_types_h = "#include <sys/types.h>";
    header sys_uio_h = "#include <sys/uio.h>";
    header sys_un_h = "#include <sys/un.h>";
    header sys_utsname_h = "#include <sys/utsname.h>";
    header sys_wait_h = "#include <sys/wait.h>";
    header syslog_h = "#include <syslog.h>";
    header tar_h = "#include <tar.h>";
    header termios_h = "#include <termios.h>";
    header trace_h = "#include <trace.h>";
    header ulimit_h = "#include <ulimit.h>";
    header unistd_h = "#include <unistd.h>";
    header utime_h = "#include <utime.h>";
    header utmpx_h = "#include <utmpx.h>";
    header wordexp_h = "#include <wordexp.h>";
  }
  


Windows
=======

The name win32 for the original 32 bit Windows has stuck,
even for 64 bit Windows.


.. index:: Win32_headers(class)
.. index:: windows_h(header)
.. index:: io_h(header)
.. index:: direct_h(header)
.. index:: sys_timeb_h(header)
.. index:: sys_utime_h(header)
.. index:: process_h(header)
.. code-block:: text

  class Win32_headers {
    header windows_h = "#include <windows.h>";
    header io_h = "#include <io.h>";
    header direct_h = "#include <direct.h>";
    header sys_timeb_h = "#include <sys/timeb.h>";
    header sys_utime_h = "#include <sys/utime.h>";
    header process_h = "#include <process.h>";
  }


