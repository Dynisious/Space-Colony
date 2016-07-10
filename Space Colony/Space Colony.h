#pragma once

#include "..\..\Dyn_API\Dyn_API\Dyn_API\Exported Headers\Maths\matrix.h"

#define FILL_ARRAY(_TO, _FROM, _C, _I, _I_INIT)\
for (_I_INIT; _I < _C; _I++) { \
_TO[_I] = _FROM[_I]; \
}

#define COPY_ARRAY(_TYPE, _TO, _FROM, _C, _I, _I_INIT)\
_TYPE* const p(_TO); \
_TO = new _TYPE[_C]; \
FILL_ARRAY(_TO, _FROM, _C, _I, _I_INIT) \
delete [] p;

/*
The umbrella namespace for Space Colony.*/
namespace Space_Colony {
	/*
	How locations are represented in Space Colony.*/
	typedef Dyn_API::Maths::matrix<__int32, 2, 1> location;
	/*
	A typedef for faction values in the game.*/
	typedef __int32 Faction;

	/*
	An enumerator of the types of resources used in the game.*/
	enum ResourceType {
		gases,
		metals,
		minerals,
		energy,
		ResourceType_max
	};

}
