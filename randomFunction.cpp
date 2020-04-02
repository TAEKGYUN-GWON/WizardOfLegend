#include "stdafx.h"

randomFunction* randomFunction::GetInstance()
{
	static randomFunction* instance = new randomFunction();
	return instance;
}
