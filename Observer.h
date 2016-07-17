#ifndef _OBSERVER_
#define _OBSERVER_

// Observer class for updating GUI based on subscribe
class Observer{
public:
	virtual void update() = 0;
};

#endif