/* 
 * This file has been automatically generated by the jrl-cmakemodules.
 * Please see https://github.com/jrl-umi3218/jrl-cmakemodules/blob/master/warning.hh.cmake for details.
*/

#ifndef VIVEPLUGIN_WARNING_HH
# define VIVEPLUGIN_WARNING_HH

// Emits a warning in a portable way.
//
// To emit a warning, one can insert:
//
// #pragma message VIVEPLUGIN_WARN("your warning message here")
//
// The use of this syntax is required as this is /not/ a standardized
// feature of C++ language or preprocessor, even if most of the
// compilers support it.

# define VIVEPLUGIN_WARN_STRINGISE_IMPL(x) #x
# define VIVEPLUGIN_WARN_STRINGISE(x) \
         VIVEPLUGIN_WARN_STRINGISE_IMPL(x)
# ifdef __GNUC__
#   define VIVEPLUGIN_WARN(exp) ("WARNING: " exp)
# else
#  ifdef _MSC_VER
#   define FILE_LINE_LINK __FILE__ "(" \
           VIVEPLUGIN_WARN_STRINGISE(__LINE__) ") : "
#   define VIVEPLUGIN_WARN(exp) (FILE_LINE_LINK "WARNING: " exp)
#  else
// If the compiler is not recognized, drop the feature.
#   define VIVEPLUGIN_WARN(MSG) /* nothing */
#  endif // __MSVC__
# endif // __GNUC__

#endif //! VIVEPLUGIN_WARNING_HH
