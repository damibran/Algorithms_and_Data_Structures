#pragma once
#include "../shape.h"

class rectangle : public shape {
public:
	void setBuffer(std::vector<edge>& _v)
	{
		for (int i = 0; i < _v.size(); ++i)
		{
			visual.push_back(&_v[i]);
		}
	}

};