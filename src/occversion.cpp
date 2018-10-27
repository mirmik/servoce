#include <Standard_Version.hxx>
#include <gxx/util/macro.h>

#define NEEDVERSION 7.3

constexpr static float occversion = OCC_VERSION;
//static_assert(occversion == (float)NEEDVERSION,
  //            "your occversion wrong (" MACRO_STRING(OCC_VERSION) "), need " MACRO_STRING(NEEDVERSION));