#pragma once
#include "../shape.h"

class rectangle : public shape {
public:
	rectangle(std::vector<std::unique_ptr<primitive>>&& _v) 
	{
		for (int i = 0; i < _v.size();++i)
		{
			visual.push_back(std::move(_v[i]));
		}
	}
	
};