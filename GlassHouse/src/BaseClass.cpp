
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "BaseClass.h"
#include <iostream>

BaseClass::BaseClass()
{
	std::cout << "Base constructor\n";
	id = -1;
}

int BaseClass::returnID() const
{
	return id;
}
