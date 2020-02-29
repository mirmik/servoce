#ifndef SERVOCE_PYWRAP_DISPLAYABLE_H
#define SERVOCE_PYWRAP_DISPLAYABLE_H

template <class Cls>
static inline void pywrap_displayable(auto cls) 
{
	cls.def("produce_interactive", &Cls::produce_interactive);
}

#endif