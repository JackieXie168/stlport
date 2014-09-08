/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */ 

# include "stlport_prefix.h"

#include <fstream>

#ifdef __CYGWIN__
#  define __int64 long long
#endif

#if defined (__STL_USE_UNIX_IO)
// open/close/read/write
#  include <sys/stat.h>           // For stat
#  include <sys/mman.h>           // For mmap
#  include <unistd.h>
#  include <fcntl.h>
#elif defined (__STL_USE_WIN32_IO)
# define WIN32_LEAN_AND_MEAN
#  include <windows.h>
# ifdef __BORLANDC__
#  if (__BORLANDC__ > 0x530)
#  include <cfcntl.h>            // For _O_RDONLY, etc
#  else
#  include <fcntl.h>            // For _O_RDONLY, etc
#  endif
#  include <sys/stat.h>         // For _fstat
# else
#  include <io.h>               // For _get_osfhandle
#  include <fcntl.h>            // For _O_RDONLY, etc
#  include <sys/stat.h>         // For _fstat
# endif
# define _TEXTBUF_SIZE 0x1000
#elif defined (__STL_USE_UNIX_EMULATION_IO)
#  if defined( __MSL__ )
#   include <unistd.h>
#  else
#   include <io.h>
#  endif
#  include <fcntl.h>
#  include <sys/stat.h>
#elif defined (__STL_USE_STDIO_IO)
#  include <cstdio>
#  if !(defined(__MRC__)||defined(__SC__))	//*TY 02/25/2000 - MPW does not come with <sys/stat.h>
#   include <sys/stat.h>
#  endif									//*TY 02/25/2000 - 
#  if defined( __MSL__ )
#   include <unix.h>
#  endif
#else
#error "Configure i/o !"
#endif

// map permission masks
#if defined (__STL_USE_UNIX_EMULATION_IO) || defined (__STL_USE_STDIO_IO)
# ifndef S_IRUSR
#  define S_IRUSR _S_IREAD
#  define S_IWUSR _S_IWRITE
#  define S_IRGRP _S_IREAD
#  define S_IWGRP _S_IWRITE
#  define S_IROTH _S_IREAD
#  define S_IWOTH _S_IWRITE
# endif
# ifndef O_RDONLY
#   define O_RDONLY _O_RDONLY
#   define O_WRONLY _O_WRONLY
#   define O_RDWR   _O_RDWR
#   define O_APPEND _O_APPEND
#   define O_CREAT  _O_CREAT
#   define O_TRUNC  _O_TRUNC
#   define O_TEXT   _O_TEXT
#   define O_BINARY _O_BINARY
# endif

# ifdef __MSL__
#  define _O_TEXT 0x0
#  if !defined( O_TEXT )
#   define O_TEXT _O_TEXT
#  endif
#  define _S_IFREG S_IFREG
#  define S_IREAD        S_IRUSR
#  define S_IWRITE       S_IWUSR
#  define S_IEXEC        S_IXUSR
#  define _S_IWRITE S_IWRITE
#  define _S_IREAD S_IREAD
#  define _open open
#  define _lseek lseek
#  define _close close
#  define _read read
#  define _write write
# endif

#endif

#ifndef O_ACCMODE
#   define O_ACCMODE (O_RDONLY|O_WRONLY|O_RDWR)
#endif

#include "fstream_impl.h"

# ifdef __STL_LONG_LONG
# define ULL(x) ((unsigned long long)x)
# elif defined (_MSC_VER) || defined (__BORLANDC__)
# define ULL(x) ((__int64)x)
# elif defined(__MRC__) || defined(__SC__)		//*TY 02/25/2000 - added support for MPW compilers
# include <Math64.h>
# define ULL(x) (U64SetU(x))
# else
#  error "there should be some long long type on the system!"
# endif

__SGI_BEGIN_NAMESPACE

#if !defined(__MSL__) && !defined(__MRC__) && !defined(__SC__)		//*TY 04/15/2000 - exclude mpw compilers also
ios_base::openmode flag_to_openmode(int mode)
{
  ios_base::openmode ret;
  
  switch(mode & O_ACCMODE) {

  case O_RDONLY:
    ret = ios_base::in; break;

  case O_WRONLY:
    ret = ios_base::out; break;

  case O_RDWR:
    ret = ios_base::in | ios_base::out; break;

  }

  if (mode & O_APPEND)
    ret |= ios_base::app;
  
#  ifdef __STL_USE_WIN32_IO
  if (mode & O_BINARY)
    ret |= ios_base::binary;
#  endif // _MSC_VER

  return ret;
  
}
# endif /* MSL */

// Helper functions for _Filebuf_base.

bool __is_regular_file(_STL_fd fd) {

#if defined (__STL_UNIX)

  struct stat buf;
  return fstat(fd, &buf) == 0 && S_ISREG(buf.st_mode);

#elif defined(__MRC__) || defined(__SC__)		//*TY 02/25/2000 - added support for MPW compilers

  #pragma unused(fd)
  return true;  // each file is a regular file under mac os, isn't it? (we don't have fstat())

#elif defined(__STL_USE_UNIX_EMULATION_IO) || defined (__STL_USE_STDIO_IO)

  struct stat buf;
  return fstat(fd, &buf) == 0 && (buf.st_mode & _S_IFREG) != 0 ;

#   elif defined (__STL_USE_WIN32_IO)

  return (GetFileType(fd) & ~FILE_TYPE_REMOTE) == FILE_TYPE_DISK;

#else
  (void)fd;    // dwa 4/27/00 - suppress unused parameter warning
  return false;

#endif
}

// Number of characters in the file.  
streamoff __file_size(_STL_fd fd) {
 streamoff ret = 0;

#if defined (__STL_UNIX)

  struct stat buf;
  if(fstat(fd, &buf) == 0 && S_ISREG(buf.st_mode))
    ret = buf.st_size > 0 ? buf.st_size : 0;

#elif defined(__MRC__) || defined(__SC__)		//*TY 02/25/2000 - added support for MPW compilers

  #pragma unused(fd)

#elif defined(__STL_USE_UNIX_EMULATION_IO) || defined (__STL_USE_STDIO_IO)

  struct stat buf;
  if(fstat(fd, &buf) == 0 && (buf.st_mode & _S_IFREG) != 0)
    ret = buf.st_size > 0 ? buf.st_size : 0;

#   elif defined (__STL_USE_WIN32_IO)

  DWORD FileSizeHigh;
  DWORD FileSize = GetFileSize(fd, &FileSizeHigh);
  // may use 64-bit
  ret = (((__int64)FileSizeHigh) << 32) | (__int64)FileSize;
  
# else
  (void)fd;    // dwa 4/27/00 - suppress unused parameter warning  
# endif
  
  return ret;

}


// Visual C++ and Intel use this, but not Metrowerks
#if !defined(__MSL__) && defined ( _MSC_VER ) && defined (_WIN32)

// fcntl(fileno, F_GETFL) for Microsoft library
// 'semi-documented' defines:
#define IOINFO_L2E          5
#define IOINFO_ARRAY_ELTS   (1 << IOINFO_L2E)
#define _pioinfo(i) ( __pioinfo[(i) >> IOINFO_L2E] + \
              ((i) & (IOINFO_ARRAY_ELTS - 1)) )
#define FAPPEND         0x20    // O_APPEND flag
#define FTEXT           0x80    // O_TEXT flag
// end of 'semi-documented' defines

// fbp : empirical
#define F_WRITABLE           0x04

// 'semi-documented' internal structure
extern "C" {
  struct ioinfo {
    long osfhnd;    // the real os HANDLE
    char osfile;    // file handle flags
    char pipech;    // pipe buffer
#   ifdef _MT
    // multi-threaded locking
    int lockinitflag;
    CRITICAL_SECTION lock;
#   endif  /* _MT */
  };
  extern _CRTIMP ioinfo * __pioinfo[];
} // extern "C"
// end of 'semi-documented' declarations 

ios_base::openmode _get_osfflags(int fd, HANDLE oshandle) {
  char dosflags = 0;

  dosflags = _pioinfo(fd)->osfile;
    // end of 'semi-documented' stuff 
  int mode = 0;
  
  if (dosflags & FAPPEND)
    mode |= O_APPEND;
  if (dosflags & FTEXT)
    mode |= O_TEXT;
  else
    mode |= O_BINARY;

  // we have to guess
# ifdef __macintosh
   DWORD dummy, dummy2;
   if (WriteFile(oshandle, &dummy2, 0, &dummy, 0))
     mode |= O_RDWR;
   else
     mode |= O_RDONLY;
# else
   // on Windows, this seems to work...
   if (dosflags & F_WRITABLE)
      mode |= O_RDWR;
   else
      mode |= O_RDONLY;
# endif
  
  return flag_to_openmode(mode);
}

#endif // _MSC_VER

__SGI_END_NAMESPACE

// All version of Unix have mmap and lseek system calls.  Some also have
// longer versions of thos system calls to accommodate 64-bit offsets.
// If we're on a Unix system, define some macros to encapsulate those
// differences.
#ifdef __STL_USE_UNIX_IO
# ifdef __sgi /* IRIX */
#  define LSEEK lseek64
#  define MMAP  mmap64
# else
#  define LSEEK lseek
#  define MMAP  mmap
# endif

#ifndef MAP_FAILED /* MMAP failure return code */
# define MAP_FAILED -1
#endif

#elif defined (__STL_USE_UNIX_EMULATION_IO)
#  define LSEEK _lseek
#endif


__STL_BEGIN_NAMESPACE

size_t
_Filebuf_base::_M_page_size = 4096;

_Filebuf_base::_Filebuf_base()
  : _M_file_id((_STL_fd)-1),
    _M_openmode(0),
    _M_is_open(false),
    _M_should_close(false)
{
  if (!_M_page_size)
#if defined (__STL_UNIX)
  _M_page_size = sysconf(_SC_PAGESIZE);
# elif defined (__STL_USE_WIN32_IO)
  {
  SYSTEM_INFO SystemInfo;
  GetSystemInfo(&SystemInfo);
  _M_page_size = SystemInfo.dwPageSize;
  // might be .dwAllocationGranularity
  }
  //  _M_CRLF_trans_buf = 0,
  //  _M_trans_buf_end=0,   
  _M_view_id = 0;
#endif

  if (_M_page_size <=0 )
    _M_page_size = 4096;

}


// Return the size of the file.  This is a wrapper for stat.
// Returns zero if the size cannot be determined or is ill-defined.
streamoff 
_Filebuf_base::_M_file_size()
{
  return SGI::__file_size(_M_file_id);
}

bool _Filebuf_base::_M_open(const char* name, ios_base::openmode openmode,
                            long permission)
{
  _STL_fd file_no;

  if (_M_is_open)
    return false;

#if defined (__STL_USE_UNIX_IO) || defined (__STL_USE_UNIX_EMULATION_IO)

  int flags = 0;

  // Unix makes no distinction between text and binary files.
  switch(openmode & (~ios_base::ate & ~ios_base::binary)) {
  case ios_base::out:
  case ios_base::out | ios_base::trunc:
    flags = O_WRONLY | O_CREAT | O_TRUNC;
    break;
  case ios_base::out | ios_base::app:
    flags = O_WRONLY | O_CREAT | O_APPEND;
    break;
  case ios_base::in:
    flags = O_RDONLY;
    permission = 0;             // Irrelevant unless we're writing.
    break;
  case ios_base::in | ios_base::out:
    flags = O_RDWR;
    break;
  case ios_base::in | ios_base::out | ios_base::trunc:
    flags = O_RDWR | O_CREAT | O_TRUNC;
    break;
  default:                      // The above are the only combinations of 
    return false;               // flags allowed by the C++ standard.
  }

# if defined (__STL_USE_UNIX_EMULATION_IO)

  if (openmode & ios_base::binary)
    flags |= O_BINARY;
  else
    flags |= O_TEXT;

  file_no = _open(name, flags, permission);

# else

  file_no = open(name, flags, permission);

# endif /* __STL_USE_UNIX_EMULATION_IO */

  if (file_no < 0)
    return false;

  _M_is_open = true;

  if (openmode & ios_base::ate)
    if (LSEEK(file_no, 0, SEEK_END) == -1)
      _M_is_open = false;
  
#elif defined (__STL_USE_STDIO_IO)
  // use FILE-based i/o
  const char* flags;

  switch(openmode & (~ios_base::ate)) {
  case ios_base::out:
  case ios_base::out | ios_base::trunc:
    flags = "w";
    break;

  case ios_base::out | ios_base::binary:
  case ios_base::out | ios_base::trunc | ios_base::binary:
    flags = "wb";
    break;

  case ios_base::out | ios_base::app:
    flags = "a";
    break;

  case ios_base::out | ios_base::app | ios_base::binary:
    flags = "ab";
    break;

  case ios_base::in:
    flags = "r";
    break;

  case ios_base::in | ios_base::binary:
    flags = "rb";
    break;

  case ios_base::in | ios_base::out:
    flags = "r+";
    break;

  case ios_base::in | ios_base::out | ios_base::binary:
    flags = "r+b";
    break;


  case ios_base::in | ios_base::out | ios_base::trunc:
    flags = "w+";
    break;

  case ios_base::in | ios_base::out | ios_base::trunc | ios_base::binary:
    flags = "w+b";
    break;

  default:                      // The above are the only combinations of 
    return false;               // flags allowed by the C++ standard.
  }

  // fbp : TODO : set permissions !
  (void)permission; // currently unused		//*TY 02/26/2000 - added to suppress warning message
  _M_file = fopen(name, flags);
 
  if (_M_file) {
    file_no = fileno(_M_file);
  }
  else
    return false;

  // unset buffering immediately
  setbuf(_M_file, 0);

  _M_is_open = true;

  if (openmode & ios_base::ate)
    if (fseek(_M_file, 0, SEEK_END) == -1)
      _M_is_open = false;
  
#   elif defined (__STL_USE_WIN32_IO)

  DWORD dwDesiredAccess, dwShareMode, dwCreationDisposition;
  bool  doTruncate = false;

  switch(openmode & (~ios_base::ate & ~ios_base::binary)) {
  case ios_base::out:
  case ios_base::out | ios_base::trunc:
    dwDesiredAccess = GENERIC_WRITE;
    dwShareMode = FILE_SHARE_READ;
    dwCreationDisposition = OPEN_ALWAYS;
    // boris : even though it is very non-intuitive, standard
    // requires them both to behave same.
    doTruncate = true;
    break;

  case ios_base::out | ios_base::app:
    dwDesiredAccess = GENERIC_WRITE;
    dwShareMode = FILE_SHARE_READ;
    dwCreationDisposition = OPEN_ALWAYS;
    break;
  case ios_base::in:
    dwDesiredAccess = GENERIC_READ;
    dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    dwCreationDisposition = OPEN_EXISTING;
    permission = 0;             // Irrelevant unless we're writing.
    break;
  case ios_base::in | ios_base::out:
    dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
    dwShareMode = FILE_SHARE_READ;
    dwCreationDisposition = OPEN_EXISTING;
    break;
  case ios_base::in | ios_base::out | ios_base::trunc:
    dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
    dwShareMode = FILE_SHARE_READ;
    dwCreationDisposition = OPEN_ALWAYS;
    doTruncate = true;
    break;
  default:                      // The above are the only combinations of
    return false;               // flags allowed by the C++ standard.
  }

# ifdef _UNICODE
  file_no = CreateFileA(
# else
  file_no = CreateFile(
# endif
			name, dwDesiredAccess, dwShareMode, 0,
                         dwCreationDisposition, permission, 0);
  
  if ( file_no == INVALID_HANDLE_VALUE )
  return false;

  if ((doTruncate && SetEndOfFile(file_no) == 0) ||
      ((openmode & ios_base::ate) && SetFilePointer(file_no, 0, NULL, FILE_END) == -1)) {
    CloseHandle(file_no);
    return false;
  }

  _M_is_open = true;
 
#else
# error "Port!"  
#endif /* __unix */


  _M_file_id = file_no;
  _M_should_close = _M_is_open;
  _M_openmode = openmode;

  if (_M_is_open)
    _M_regular_file = SGI::__is_regular_file(_M_file_id);
  
  return _M_is_open;
}

  
bool _Filebuf_base::_M_open(const char* name, ios_base::openmode openmode)
{
  // This doesn't really grant everyone in the world read/write
  // access.  On Unix, file-creation system calls always clear 
  // bits that are set in the umask from the permissions flag.
# ifdef __STL_USE_WIN32_IO
  return this->_M_open(name, openmode, FILE_ATTRIBUTE_NORMAL);
# elif defined(__MRC__) || defined(__SC__)		//*TY 02/26/2000 - added support for MPW compilers
  return this->_M_open(name, openmode, 0);
# else
  return this->_M_open(name, openmode, S_IRUSR | S_IWUSR | S_IRGRP | 
                                       S_IWGRP | S_IROTH | S_IWOTH);
# endif
}

      
// Associated the filebuf with a file descriptor pointing to an already-
// open file.  Mode is set to be consistent with the way that the file
// was opened.
bool _Filebuf_base::_M_open(int file_no, ios_base::openmode init_mode) {

  if (_M_is_open || file_no < 0)
    return false;

# if defined (__STL_UNIX)
  (void)init_mode;    // dwa 4/27/00 - suppress unused parameter warning
  int mode ;
  mode = fcntl(file_no, F_GETFL);

  if (mode == -1)
    return false;

  _M_openmode = SGI::flag_to_openmode(mode);
  
# elif defined(__MRC__) || defined(__SC__)		//*TY 02/26/2000 - added support for MPW compilers
  (void)init_mode;    // dwa 4/27/00 - suppress unused parameter warning
  switch( _iob[file_no]._flag & (_IOREAD|_IOWRT|_IORW) )
  {
  case _IOREAD:
    _M_openmode = ios_base::in; break;
  case _IOWRT:
    _M_openmode = ios_base::out; break;
  case _IORW:
    _M_openmode = ios_base::in | ios_base::out; break;
  default:
  	return false;
  }
  
# elif defined (__STL_USE_UNIX_EMULATION_IO) || defined (__STL_USE_STDIO_IO) 
  (void)init_mode;    // dwa 4/27/00 - suppress unused parameter warning
  int mode ;
  struct stat buf;
  if (fstat(file_no, &buf) != 0)
    return false;
  mode = buf.st_mode;
  
  switch(mode & (_S_IWRITE | _S_IREAD) ) {
  case _S_IREAD:
    _M_openmode = ios_base::in; break;
  case _S_IWRITE:
    _M_openmode = ios_base::out; break;
  case (_S_IWRITE | _S_IREAD):
    _M_openmode = ios_base::in | ios_base::out; break;
  default:
    return false;
  }
# elif defined(__STL_USE_WIN32_IO) && defined (_MSC_VER)

  if (_M_is_open || file_no == -1)
    return false;

  HANDLE oshandle = (HANDLE)_get_osfhandle(file_no);
  
  if ((long)oshandle != -1)
	file_no = (int)oshandle;
  else
    return false;
  
  if (init_mode != ios_base::__default_mode)
    _M_openmode = init_mode;
  else
    _M_openmode = SGI::_get_osfflags(file_no, oshandle);
  
# else
  (void)init_mode;    // dwa 4/27/00 - suppress unused parameter warning

  // not available for the API
  return false;

# endif
  

  _M_is_open = true;
  _M_file_id = (_STL_fd)file_no;
  _M_should_close = false;
  _M_regular_file = SGI::__is_regular_file(_M_file_id);

  return true;
}

bool _Filebuf_base::_M_close() {
  if (!_M_is_open)
    return false;

  bool ok;

  if (!_M_should_close)
    ok = true;
  else {
    
#   if defined (__STL_USE_UNIX_IO)

    ok = (close(_M_file_id) == 0);

#   elif defined (__STL_USE_UNIX_EMULATION_IO)

    ok = (_close(_M_file_id) == 0);

#   elif defined (__STL_USE_STDIO_IO)

    ok = (fclose(_M_file) == 0);

#   elif defined (__STL_USE_WIN32_IO)

    ok = (CloseHandle(_M_file_id) != 0);

#   else

    ok = false;

#   endif /* __STL_USE_UNIX_IO */
  }

  _M_is_open = _M_should_close = false;
  _M_openmode = 0;
  return ok;
}


# define __STL_LF 10
# define __STL_CR 13
# define __STL_CTRLZ 26

// Read up to n characters into a buffer.  Return value is number of
// characters read.
ptrdiff_t _Filebuf_base::_M_read(char* buf, ptrdiff_t n) {
#   if defined (__STL_USE_UNIX_IO)

  return read(_M_file_id, buf, n);

#   elif defined (__STL_USE_UNIX_EMULATION_IO)

  return _read(_M_file_id, buf, n);

#   elif defined (__STL_USE_WIN32_IO)
  
  DWORD NumberOfBytesRead;
  ReadFile(_M_file_id, (LPVOID)buf, (DWORD)n, 
           &NumberOfBytesRead, 0);

  if ((! (_M_openmode & ios_base::binary)) && NumberOfBytesRead) { 
    // translate CR-LFs to LFs in the buffer
    char * to = buf, * last = buf + NumberOfBytesRead - 1;
    char * from;
    for (from = buf; from <= last && * from != __STL_CTRLZ; ++ from ) {
      if (* from != __STL_CR)
        * to ++ = * from;
      else { // found CR
        if (from < last) { // not at buffer end
          if (* (from + 1) != __STL_LF)
            * to ++ = __STL_CR;
        }
        else { // last char is CR, peek for LF
          char peek = ' ';
          DWORD NumberOfBytesPeeked;
          ReadFile(_M_file_id, (LPVOID)&peek, 
                        1, &NumberOfBytesPeeked, 0);
          if (NumberOfBytesPeeked)
            SetFilePointer(_M_file_id,(LONG)-1,0,SEEK_CUR);
          if (peek != __STL_LF)
            * to ++ = __STL_CR;
        }
      } // found CR
    } // for
    // seek back to TEXT end of file if hit CTRL-Z
    if (from <= last) // terminated due to CTRLZ
      SetFilePointer(_M_file_id,(LONG)((last+1) - from),0,SEEK_CUR);
    NumberOfBytesRead = to - buf;
  }
  return (ptrdiff_t)NumberOfBytesRead;
  
#   elif defined (__STL_USE_STDIO_IO)
  
  return fread(buf, 1, n, _M_file);
  
#   else 
#    error "Port!"
# endif /* __unix */
}

// Write n characters from a buffer.  Return value: true if we managed
// to write the entire buffer, false if we didn't.  
bool _Filebuf_base::_M_write(char* buf, ptrdiff_t n) {
  
  while (true) {
    ptrdiff_t written;
    
#   if defined (__STL_USE_UNIX_IO)

    written = write(_M_file_id, buf, n);

#   elif defined (__STL_USE_UNIX_EMULATION_IO)

    written = _write(_M_file_id, buf, n);

#   elif defined (__STL_USE_WIN32_IO)

    // In append mode, every write does an implicit seek to the end
    // of the file.
    if (_M_openmode & ios_base::app)
      _M_seek( 0, ios_base::end);
    
    if (_M_openmode & ios_base::binary) { 
      // binary mode
      DWORD NumberOfBytesWritten;
      WriteFile(_M_file_id, (LPVOID)buf, (DWORD)n, 
                &NumberOfBytesWritten, 0);
      written = (ptrdiff_t)NumberOfBytesWritten;
    }
    else {
      char textbuf[_TEXTBUF_SIZE + 1]; // extra 1 in case LF at end
      char * nextblock = buf, * ptrtextbuf = textbuf;
      char * endtextbuf = textbuf + _TEXTBUF_SIZE;
      char * endblock = buf + n;
      ptrdiff_t nextblocksize = (__STLPORT_STD::min)(n, _TEXTBUF_SIZE);
      char * nextlf;
      
      while ( (nextblocksize > 0) && 
              (nextlf = (char *)memchr(nextblock, __STL_LF, nextblocksize)) != 0) {
        ptrdiff_t linelength = nextlf - nextblock;
        memcpy(ptrtextbuf, nextblock, linelength);
        ptrtextbuf += linelength;
        nextblock += (linelength + 1);
        * ptrtextbuf ++ = __STL_CR;
        * ptrtextbuf ++ = __STL_LF;
        nextblocksize = (__STLPORT_STD::min)(ptrdiff_t(endblock - nextblock), 
                                             (__STLPORT_STD::max)(ptrdiff_t(0), ptrdiff_t(endtextbuf - ptrtextbuf)));
      }
      // write out what's left, > condition is here since for LF at the end , 
      // endtextbuf may get < ptrtextbuf ...
      if (nextblocksize > 0) {
        memcpy(ptrtextbuf, nextblock, nextblocksize);
        ptrtextbuf += nextblocksize;
        nextblock += nextblocksize;
      }
      // now write out the translated buffer
      char * writetextbuf = textbuf;
      for (ptrdiff_t NumberOfBytesToWrite = ptrtextbuf - textbuf; 
           NumberOfBytesToWrite;) {
        DWORD NumberOfBytesWritten;
        WriteFile((HANDLE)_M_file_id, (LPVOID)writetextbuf, 
                  NumberOfBytesToWrite, &NumberOfBytesWritten, 0);
        if (NumberOfBytesWritten == NumberOfBytesToWrite)
          break;
        if (!NumberOfBytesWritten) // write shortfall
          return false;
        writetextbuf += NumberOfBytesWritten;
        NumberOfBytesToWrite -=	NumberOfBytesWritten;
      }
      // count non-translated characters
      written = (nextblock - buf);
    }

#   elif defined (__STL_USE_STDIO_IO)

    written = fwrite(buf, 1, n, _M_file);

#   else 
#    error "Port!"
#   endif /* __unix */ 
    
    if (n == written)
      return true;
    else if (written > 0 && written < n) {
      n -= written;
      buf += written;
    }
    else
      return false;
  }
}


#ifdef __STL_USE_WIN32_IO
# define STL_SEEK_SET FILE_BEGIN
# define STL_SEEK_CUR FILE_CURRENT
# define STL_SEEK_END FILE_END
#else
# define STL_SEEK_SET SEEK_SET
# define STL_SEEK_CUR SEEK_CUR
# define STL_SEEK_END SEEK_END
#endif

// Wrapper for lseek or the like.
streamoff _Filebuf_base::_M_seek(streamoff offset, ios_base::seekdir dir)
{
  streamoff result = -1;

  int whence;

  switch(dir) {
  case ios_base::beg:
    if (offset < 0 || offset > _M_file_size())
      return streamoff(-1);
    whence = STL_SEEK_SET;
    break;
  case ios_base::cur:
    whence = STL_SEEK_CUR;
    break;
  case ios_base::end:
    if (offset > 0 || -offset > _M_file_size())
      return streamoff(-1);
    whence = STL_SEEK_END;
    break;
  default:
    return streamoff(-1);
  }

#if defined (__STL_USE_UNIX_IO) || defined (__STL_USE_UNIX_EMULATION_IO)

  result = LSEEK(_M_file_id, offset, whence);

#elif defined (__STL_USE_STDIO_IO)

  result = fseek(_M_file, offset, whence);

#elif defined (__STL_USE_WIN32_IO)

  long hi_seek = ULL(offset) >> 32;
  long ret = SetFilePointer(_M_file_id, offset, &hi_seek, whence);
  if (ret == -1)
    result = ret;
  else {
    result = hi_seek;
    result = (ULL(result)<<32) | ret;
  }

#else
#   error "Port!"
#endif

  return result;
}


// Attempts to memory-map len bytes of the current file, starting
// at position offset.  Precondition: offset is a multiple of the
// page size.  Postcondition: return value is a null pointer if the
// memory mapping failed.  Otherwise the return value is a pointer to 
// the memory-mapped file and the file position is set to offset.
void* _Filebuf_base::_M_mmap(streamoff offset, streamoff len) {
  void* base;
#if defined (__STL_UNIX)
  base = MMAP(0, len, PROT_READ, MAP_PRIVATE, _M_file_id, offset);
  if (base != (void*)MAP_FAILED) {
    if (LSEEK(_M_file_id, offset + len, SEEK_SET) < 0) {
      this->_M_unmap(base, len);
      base = 0;
    }
  } else
    base =0;

#elif defined (__STL_USE_WIN32_IO)

  _M_view_id = CreateFileMapping(_M_file_id, (PSECURITY_ATTRIBUTES)0 ,
				 PAGE_READONLY, 0 /* len >> 32 */ , 
				 0 /* len & 0xFFFFFFFF */ ,             // low-order DWORD of size
				 0);

  if (_M_view_id) {
# if 0
    printf("view %x created from file %x, error = %d, size = %d, map_offset = %d map_len = %d\n", 
	   _M_view_id, _M_file_id, GetLastError(), 
	   (int)cur_filesize, ULL(offset) & 0xffffffff, len);
# endif
    
    base = MapViewOfFile(_M_view_id, FILE_MAP_READ, ULL(offset)>>32, 
			 ULL(offset) & 0xffffffff, len);
    
    if (base) {
      if (_M_seek(offset+len, ios_base::beg) < 0) {
	this->_M_unmap(base, len);
	base = 0;
      }
    }
  }
#else
  (void)len;		//*TY 02/26/2000 - unused variables
  (void)offset;		//*TY 02/26/2000 - 
  base = 0;
#endif
  return base;  
}

void _Filebuf_base::_M_unmap(void* base, streamoff len) {
  // precondition : there is a valid mapping at the moment
#if defined (__STL_UNIX)
  munmap((caddr_t)base, len);
#elif defined (__STL_USE_WIN32_IO)
  UnmapViewOfFile(base);
  // destroy view handle as well
  CloseHandle(_M_view_id);
  _M_view_id = 0;
#else
  (void)len;		//*TY 02/26/2000 - unused variables
  (void)base;		//*TY 02/26/2000 - 
#endif
}

# define MMAP_CHUNK 0x1000000UL

int __STL_CALL
_Underflow<char, char_traits<char> >::_M_doit (basic_filebuf<char, char_traits<char> >* __this)  
{
  if (!__this->_M_in_input_mode) {
    if (!__this->_M_switch_to_input_mode())
      return traits_type::eof();
  }
  
  else if (__this->_M_in_putback_mode) {
    __this->_M_exit_putback_mode();
    if (__this->gptr() != __this->egptr()) {
      int_type __c = traits_type::to_int_type(*__this->gptr());
      return __c;
    }
  }
    
  // If it's a disk file, and if the internal and external character
  // sequences are guaranteed to be identical, then try to use memory
  // mapped I/O.  Otherwise, revert to ordinary read.
  if (__this->_M_base.__regular_file() 
      && __this->_M_always_noconv
      && __this->_M_base._M_in_binary_mode()) {
    // If we've mmapped part of the file already, then unmap it.
    if (__this->_M_mmap_base)
      __this->_M_base._M_unmap(__this->_M_mmap_base, __this->_M_mmap_len);
      
    // Determine the position where we start mapping.  It has to be
    // a multiple of the page size.
    streamoff __cur = __this->_M_base._M_seek(0, ios_base::cur);
    streamoff __size = __this->_M_base._M_file_size();
    if (__size > 0 && __cur >= 0 && __cur < __size) {
      streamoff __offset    = (__cur / __this->_M_base.__page_size())
	* __this->_M_base.__page_size();
      streamoff __remainder = __cur - __offset;

      __this->_M_mmap_len = __size - __offset;

      // fbp : let us map 1 MB maximum, just be sure not to trash VM
      if (__this->_M_mmap_len > MMAP_CHUNK)
	__this->_M_mmap_len = MMAP_CHUNK;

      if ((__this->_M_mmap_base =
	   __this->_M_base._M_mmap(__offset, __this->_M_mmap_len)) != 0) {
	__this->setg((char*) __this->_M_mmap_base,
		     (char*) __this->_M_mmap_base + __remainder,
		     (char*) __this->_M_mmap_base + __this->_M_mmap_len);
	return traits_type::to_int_type(*__this->gptr());
      }
    }
  }
    
  return __this->_M_underflow_aux();
}


//----------------------------------------------------------------------
// Force instantiation of filebuf and fstream classes.
#if !defined(__STL_NO_FORCE_INSTANTIATE)

template class basic_filebuf<char, char_traits<char> >;
template class basic_ifstream<char, char_traits<char> >;
template class basic_ofstream<char, char_traits<char> >;
template class basic_fstream<char, char_traits<char> >;

#endif
__STL_END_NAMESPACE

// Local Variables:
// mode:C++
// End:

