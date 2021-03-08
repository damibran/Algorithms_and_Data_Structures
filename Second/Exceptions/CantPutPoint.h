#pragma once
#include <exception>
#include <string>

struct CantPutPoint : std::exception
{
	int x, y;
	CantPutPoint(const std::string& s, int _x, int _y) : std::exception(s.c_str()), x(_x), y(_y) { }
	CantPutPoint() = default;
};
