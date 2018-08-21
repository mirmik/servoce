#include <Standard_Version.hxx>
#include <gxx/util/macro.h>

constexpr static float occversion = OCC_VERSION;
static_assert(occversion == (float)7.2, 
	"your occversion wrong (" MACRO_STRING(OCC_VERSION) "), need 7.2");