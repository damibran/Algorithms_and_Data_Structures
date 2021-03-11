#pragma once
#include "../shape.h"

class rectangle : public shape {
public:
	rectangle(std::vector<std::shared_ptr<primitive>> _v) {
		visual = _v;
	}
	
};