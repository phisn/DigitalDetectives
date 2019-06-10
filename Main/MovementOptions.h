#pragma once

#include "Common.h"

RESOURCE_BEGIN

struct Movement
{
	byte position;
	byte target;
	byte d;
};

RESOURCE_END
