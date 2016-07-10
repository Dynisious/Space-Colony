#include "Galactic\Solar\Star.h"

Space_Colony::Galactic::Solar::Star::Star() {}

Space_Colony::Galactic::Solar::Star::Star(unsigned __int32 outs[]) {
	for (unsigned __int32 i(0); i < ResourceType_max; i++)
		outputs[i] = outs[i];
}
