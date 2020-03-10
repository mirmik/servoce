#ifndef SERVOCE_PYWRAP_DISPLAYABLE_H
#define SERVOCE_PYWRAP_DISPLAYABLE_H

template <class Cls, class U>
static inline void pywrap_displayable(U&& cls) 
{
	cls.def("produce_interactive", &Cls::produce_interactive);
}

#endif
