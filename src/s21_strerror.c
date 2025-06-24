
#include "s21_sprintf.h"

// AAAAAAAAAAAAAAAAAAAAAA

#ifdef __linux__
#define MAX_ERRNUM 133
static const char *errors[] = {
    "Success",                          /* 0 */
    "Operation not permitted",          /* 1: EPERM */
    "No such file or directory",        /* 2: ENOENT */
    "No such process",                  /* 3: ESRCH */
    "Interrupted system call",          /* 4: EINTR */
    "Input/output error",               /* 5: EIO */
    "No such device or address",        /* 6: ENXIO */
    "Argument list too long",           /* 7: E2BIG */
    "Exec format error",                /* 8: ENOEXEC */
    "Bad file descriptor",              /* 9: EBADF */
    "No child processes",               /* 10: ECHILD */
    "Resource temporarily unavailable", /* 11: EAGAIN */
    "Cannot allocate memory",           /* 12: ENOMEM */
    "Permission denied",                /* 13: EACCES */
    "Bad address",                      /* 14: EFAULT */
    "Block device required",            /* 15: ENOTBLK */
    "Device or resource busy",          /* 16: EBUSY */
    "File exists",                      /* 17: EEXIST */
    "Invalid cross-device link",        /* 18: EXDEV */
    "No such device",                   /* 19: ENODEV */
    "Not a directory",                  /* 20: ENOTDIR */
    "Is a directory",                   /* 21: EISDIR */
    "Invalid argument",                 /* 22: EINVAL */
    "Too many open files in system",    /* 23: ENFILE */
    "Too many open files",              /* 24: EMFILE */
    "Inappropriate ioctl for device",   /* 25: ENOTTY */
    "Text file busy",                   /* 26: ETXTBSY */
    "File too large",                   /* 27: EFBIG */
    "No space left on device",          /* 28: ENOSPC */
    "Illegal seek",                     /* 29: ESPIPE */
    "Read-only file system",            /* 30: EROFS */
    "Too many links",                   /* 31: EMLINK */
    "Broken pipe",                      /* 32: EPIPE */
    "Numerical argument out of domain", /* 33: EDOM */
    "Numerical result out of range",    /* 34: ERANGE */
    "Resource deadlock avoided",        /* 35: EDEADLK */
    "File name too long",               /* 36: ENAMETOOLONG */
    "No locks available",               /* 37: ENOLCK */
    "Function not implemented",         /* 38: ENOSYS */
    "Directory not empty",              /* 39: ENOTEMPTY */
    "Too many symbolic links",          /* 40: ELOOP */
    "",                                 /* 41: Reserved */
    "No message of desired type",       /* 42: ENOMSG */
    "Identifier removed",               /* 43: EIDRM */
    "Channel number out of range",      /* 44: ECHRNG */
    "Level 2 not synchronized",         /* 45: EL2NSYNC */
    "Level 3 halted",                   /* 46: EL3HLT */
    "Level 3 reset",                    /* 47: EL3RST */
    "Link number out of range",         /* 48: ELNRNG */
    "Protocol driver not attached",     /* 49: EUNATCH */
    "No CSI structure available",       /* 50: ENOCSI */
    "Level 2 halted",                   /* 51: EL2HLT */
    "Invalid exchange",                 /* 52: EBADE */
    "Invalid request descriptor",       /* 53: EBADR */
    "Exchange full",                    /* 54: EXFULL */
    "No anode",                         /* 55: ENOANO */
    "Invalid request code",             /* 56: EBADRQC */
    "Invalid slot",                     /* 57: EBADSLT */
    "",                                 /* 58: Reserved */
    "Bad font file format",             /* 59: EBFONT */
    "Device not a stream",              /* 60: ENOSTR */
    "No data available",                /* 61: ENODATA */
    "Timer expired",                    /* 62: ETIME */
    "Out of streams resources",         /* 63: ENOSR */
    "Machine is not on the network",    /* 64: ENONET */
    "Package not installed",            /* 65: ENOPKG */
    "Object is remote",                 /* 66: EREMOTE */
    "Link has been severed",            /* 67: ENOLINK */
    "Advertise error",                  /* 68: EADV */
    "Srmount error",                    /* 69: ESRMNT */
    "Communication error on send",      /* 70: ECOMM */
    "Protocol error",                   /* 71: EPROTO */
    "Multihop attempted",               /* 72: EMULTIHOP */
    "RFS specific error",               /* 73: EDOTDOT */
    "Bad message",                      /* 74: EBADMSG */
    "Value too large for data type",    /* 75: EOVERFLOW */
    "Name not unique on network",       /* 76: ENOTUNIQ */
    "File descriptor in bad state",     /* 77: EBADFD */
    "Remote address changed",           /* 78: EREMCHG */
    "Can not access a needed library",  /* 79: ELIBACC */
    "Corrupt or inaccessible library",  /* 80: ELIBBAD */
    "Library section corrupted",        /* 81: ELIBSCN */
    "Too many libraries",               /* 82: ELIBMAX */
    "Library execution error",          /* 83: ELIBEXEC */
    "Illegal byte sequence",            /* 84: EILSEQ */
    "Interrupted system call restart",  /* 85: ERESTART */
    "Streams pipe error",               /* 86: ESTRPIPE */
    "Too many users",                   /* 87: EUSERS */
    "Socket operation on non-socket",   /* 88: ENOTSOCK */
    "Destination address required",     /* 89: EDESTADDRREQ */
    "Message too long",                 /* 90: EMSGSIZE */
    "Protocol wrong type for socket",   /* 91: EPROTOTYPE */
    "Protocol not available",           /* 92: ENOPROTOOPT */
    "Protocol not supported",           /* 93: EPROTONOSUPPORT */
    "Socket type not supported",        /* 94: ESOCKTNOSUPPORT */
    "Operation not supported",          /* 95: EOPNOTSUPP */
    "Protocol family not supported",    /* 96: EPFNOSUPPORT */
    "Address family not supported",     /* 97: EAFNOSUPPORT */
    "Address already in use",           /* 98: EADDRINUSE */
    "Cannot assign requested address",  /* 99: EADDRNOTAVAIL */
    "Network is down",                  /* 100: ENETDOWN */
    "Network is unreachable",           /* 101: ENETUNREACH */
    "Network reset",                    /* 102: ENETRESET */
    "Connection aborted",               /* 103: ECONNABORTED */
    "Connection reset by peer",         /* 104: ECONNRESET */
    "No buffer space available",        /* 105: ENOBUFS */
    "Socket is already connected",      /* 106: EISCONN */
    "Socket is not connected",          /* 107: ENOTCONN */
    "Cannot send after shutdown",       /* 108: ESHUTDOWN */
    "Too many references",              /* 109: ETOOMANYREFS */
    "Connection timed out",             /* 110: ETIMEDOUT */
    "Connection refused",               /* 111: ECONNREFUSED */
    "Host is down",                     /* 112: EHOSTDOWN */
    "No route to host",                 /* 113: EHOSTUNREACH */
    "Operation already in progress",    /* 114: EALREADY */
    "Operation now in progress",        /* 115: EINPROGRESS */
    "Stale file handle",                /* 116: ESTALE */
    "Structure needs cleaning",         /* 117: EUCLEAN */
    "Not a XENIX named type file",      /* 118: ENOTNAM */
    "No XENIX semaphores available",    /* 119: ENAVAIL */
    "Is a named type file",             /* 120: EISNAM */
    "Remote I/O error",                 /* 121: EREMOTEIO */
    "Disk quota exceeded",              /* 122: EDQUOT */
    "No medium found",                  /* 123: ENOMEDIUM */
    "Wrong medium type",                /* 124: EMEDIUMTYPE */
    "Operation canceled",               /* 125: ECANCELED */
    "Required key not available",       /* 126: ENOKEY */
    "Key has expired",                  /* 127: EKEYEXPIRED */
    "Key has been revoked",             /* 128: EKEYREVOKED */
    "Key was rejected by service",      /* 129: EKEYREJECTED */
    "Owner died",                       /* 130: EOWNERDEAD */
    "State not recoverable",            /* 131: ENOTRECOVERABLE */
    "Operation not possible",           /* 132: ERFKILL */
    "Memory page has hardware error"    /* 133: EHWPOISON */
};
#elif defined(__APPLE__)
#define MAX_ERRNUM 106
static const char *errors[] = {
    "No error",                          /* 0 */
    "Operation not permitted",           /* 1: EPERM */
    "No such file or directory",         /* 2: ENOENT */
    "No such process",                   /* 3: ESRCH */
    "Interrupted system call",           /* 4: EINTR */
    "Input/output error",                /* 5: EIO */
    "Device not configured",             /* 6: ENXIO */
    "Argument list too long",            /* 7: E2BIG */
    "Exec format error",                 /* 8: ENOEXEC */
    "Bad file descriptor",               /* 9: EBADF */
    "No child processes",                /* 10: ECHILD */
    "Resource deadlock avoided",         /* 11: EDEADLK */
    "Cannot allocate memory",            /* 12: ENOMEM */
    "Permission denied",                 /* 13: EACCES */
    "Bad address",                       /* 14: EFAULT */
    "Block device required",             /* 15: ENOTBLK */
    "Resource busy",                     /* 16: EBUSY */
    "File exists",                       /* 17: EEXIST */
    "Cross-device link",                 /* 18: EXDEV */
    "Operation not supported by device", /* 19: ENODEV */
    "Not a directory",                   /* 20: ENOTDIR */
    "Is a directory",                    /* 21: EISDIR */
    "Invalid argument",                  /* 22: EINVAL */
    "Too many open files in system",     /* 23: ENFILE */
    "Too many open files",               /* 24: EMFILE */
    "Inappropriate ioctl for device",    /* 25: ENOTTY */
    "Text file busy",                    /* 26: ETXTBSY */
    "File too large",                    /* 27: EFBIG */
    "No space left on device",           /* 28: ENOSPC */
    "Illegal seek",                      /* 29: ESPIPE */
    "Read-only file system",             /* 30: EROFS */
    "Too many links",                    /* 31: EMLINK */
    "Broken pipe",                       /* 32: EPIPE */
    "Numerical argument out of domain",  /* 33: EDOM */
    "Result too large",                  /* 34: ERANGE */
    "Resource temporarily unavailable",  /* 35: EAGAIN */
    "Operation now in progress",         /* 36: EINPROGRESS */
    "Operation already in progress",     /* 37: EALREADY */
    "Socket operation on non-socket",    /* 38: ENOTSOCK */
    "Destination address required",      /* 39: EDESTADDRREQ */
    "Message too long",                  /* 40: EMSGSIZE */
    "Protocol wrong type for socket",    /* 41: EPROTOTYPE */
    "Protocol not available",            /* 42: ENOPROTOOPT */
    "Protocol not supported",            /* 43: EPROTONOSUPPORT */
    "Socket type not supported",         /* 44: ESOCKTNOSUPPORT */
    "Operation not supported",           /* 45: EOPNOTSUPP */
    "Protocol family not supported",     /* 46: EPFNOSUPPORT */
    "Address family not supported",      /* 47: EAFNOSUPPORT */
    "Address already in use",            /* 48: EADDRINUSE */
    "Can't assign requested address",    /* 49: EADDRNOTAVAIL */
    "Network is down",                   /* 50: ENETDOWN */
    "Network is unreachable",            /* 51: ENETUNREACH */
    "Network reset",                     /* 52: ENETRESET */
    "Connection aborted",                /* 53: ECONNABORTED */
    "Connection reset by peer",          /* 54: ECONNRESET */
    "No buffer space available",         /* 55: ENOBUFS */
    "Socket is already connected",       /* 56: EISCONN */
    "Socket is not connected",           /* 57: ENOTCONN */
    "Can't send after socket shutdown",  /* 58: ESHUTDOWN */
    "Too many references",               /* 59: ETOOMANYREFS */
    "Connection timed out",              /* 60: ETIMEDOUT */
    "Connection refused",                /* 61: ECONNREFUSED */
    "Loop in symbolic links",            /* 62: ELOOP */
    "File name too long",                /* 63: ENAMETOOLONG */
    "Host is down",                      /* 64: EHOSTDOWN */
    "No route to host",                  /* 65: EHOSTUNREACH */
    "Directory not empty",               /* 66: ENOTEMPTY */
    "Too many processes",                /* 67: EPROCLIM */
    "Too many users",                    /* 68: EUSERS */
    "Disk quota exceeded",               /* 69: EDQUOT */
    "Stale NFS file handle",             /* 70: ESTALE */
    "Object is remote",                  /* 71: EREMOTE */
    "RPC struct is bad",                 /* 72: EBADRPC */
    "RPC version wrong",                 /* 73: ERPCMISMATCH */
    "RPC program not available",         /* 74: EPROGUNAVAIL */
    "Program version wrong",             /* 75: EPROGMISMATCH */
    "Bad procedure for program",         /* 76: EPROCUNAVAIL */
    "No locks available",                /* 77: ENOLCK */
    "Function not implemented",          /* 78: ENOSYS */
    "Inappropriate file type or format", /* 79: EFTYPE */
    "Authentication error",              /* 80: EAUTH */
    "Need authenticator",                /* 81: ENEEDAUTH */
    "Identifier removed",                /* 82: EIDRM */
    "No message of desired type",        /* 83: ENOMSG */
    "Value too large",                   /* 84: EOVERFLOW */
    "Illegal byte sequence",             /* 85: EILSEQ */
    "Not supported",                     /* 86: ENOTSUP */
    "Operation canceled",                /* 87: ECANCELED */
    "Bad message",                       /* 88: EBADMSG */
    "No data available",                 /* 89: ENODATA */
    "No STREAM resources",               /* 90: ENOSR */
    "Not a STREAM",                      /* 91: ENOSTR */
    "Timer expired",                     /* 92: ETIME */
    "Out of STREAMs resources",          /* 93: ENOSR */
    "Link has been severed",             /* 94: ENOLINK */
    "Protocol error",                    /* 95: EPROTO */
    "Multihop attempted",                /* 96: EMULTIHOP */
    "",                                  /* 97: Reserved */
    "No space for data",                 /* 98: ENOSPC */
    "Too many references",               /* 99: ETOOMANYREFS */
    "File table overflow",               /* 100: ENFILE */
    "Invalid exchange",                  /* 101: EBADE */
    "Invalid request descriptor",        /* 102: EBADR */
    "Exchange full",                     /* 103: EXFULL */
    "No anode",                          /* 104: ENOANO */
    "Invalid request code",              /* 105: EBADRQC */
    "Invalid slot"                       /* 106: EBADSLT */
};
#else
#error "Unsupported OS"
#endif

char *s21_strerror(int errnum) {
  static char unknown[32];
  if (errnum >= 0 && errnum <= MAX_ERRNUM) {
    return (char *)errors[errnum];
  }
  s21_sprintf(unknown, "Unknown error: %d", errnum);
  return unknown;
}
