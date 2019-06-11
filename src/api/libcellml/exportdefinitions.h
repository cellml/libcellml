
#ifndef LIBCELLML_EXPORT_H
#define LIBCELLML_EXPORT_H

#ifdef LIBCELLML_STATIC_DEFINE
#  define LIBCELLML_EXPORT
#  define LIBCELLML_NO_EXPORT
#else
#  ifndef LIBCELLML_EXPORT
#    ifdef cellml_EXPORTS
        /* We are building this library */
#      define LIBCELLML_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define LIBCELLML_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef LIBCELLML_NO_EXPORT
#    define LIBCELLML_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef LIBCELLML_DEPRECATED
#  define LIBCELLML_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef LIBCELLML_DEPRECATED_EXPORT
#  define LIBCELLML_DEPRECATED_EXPORT LIBCELLML_EXPORT LIBCELLML_DEPRECATED
#endif

#ifndef LIBCELLML_DEPRECATED_NO_EXPORT
#  define LIBCELLML_DEPRECATED_NO_EXPORT LIBCELLML_NO_EXPORT LIBCELLML_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef LIBCELLML_NO_DEPRECATED
#    define LIBCELLML_NO_DEPRECATED
#  endif
#endif

#endif /* LIBCELLML_EXPORT_H */
