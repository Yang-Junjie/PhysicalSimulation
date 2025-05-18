#ifndef PS_SAP_HPP
#define PS_SAP_HPP
#include "ps_body.hpp"

namespace ps
{
	class SweepAndPrune
	{
	public:

		static Container::Vector<std::pair<Body*, Body*>> generate(const Container::Vector<Body*>& bodyList);
		static Container::Vector<Body*> query(const Container::Vector<Body*>& bodyList, const AABB& region);
	};
}

#endif // !PHYSICS_BROADPHASE_GRID_H
