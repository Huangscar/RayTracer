#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitable_list: public hitable
{
public:
	hitable **list;
	int list_size;
	hitable_list() {};
	hitable_list(hitable **l, int n);
	virtual bool hit(const ray&r, float tmin, float tmax, hit_record& rec) const;

private:

};



#endif // !HITABLELISTH

