#include "ps_sap.hpp"

#include "ps_body.hpp"

namespace ps
{
	Container::Vector<std::pair<Body *, Body *>> SweepAndPrune::generate(const Container::Vector<Body *> &bodyList)
	{
		Container::Vector<std::pair<Body*, Body*>> result;
		//sort by x axis
		Container::Vector<std::pair<Body*, AABB>> bodyBoxPairList;
		bodyBoxPairList.reserve(bodyList.size());

		for(auto&& elem: bodyList)
			bodyBoxPairList.emplace_back(std::make_pair(elem, elem->aabb()));

		Container::Vector<std::pair<Body*, AABB>> sortXAxis = bodyBoxPairList;
		Container::Vector<std::pair<Body*, AABB>> sortYAxis = bodyBoxPairList;
		std::sort(sortXAxis.begin(), sortXAxis.end(), [](const std::pair<Body*, AABB>& left, const std::pair<Body*, AABB>& right)
			{
				return left.second.minimumX() < right.second.minimumX();
			});
		std::sort(sortYAxis.begin(), sortYAxis.end(), [](const std::pair<Body*, AABB>& left, const std::pair<Body*, AABB>& right)
			{
				return left.second.minimumY() < right.second.minimumY();
			});

		Container::Vector<Body::BodyPair> xPairs;
		Container::Vector<Body::BodyPair> yPairs;

		for (auto before = sortXAxis.begin(); before != sortXAxis.end(); ++before)
		{
			for (auto next = std::next(before); next != sortXAxis.end(); ++next)
			{
				const real minBefore = before->second.minimumX();
				const real maxBefore = before->second.maximumX();
				const real minNext = next->second.minimumX();
				const real maxNext = next->second.maximumX();

				if (!(maxBefore < minNext || maxNext < minBefore))
					xPairs.emplace_back(Body::BodyPair::generateBodyPair(before->first, next->first));
				else
					break;
			}
		}

		for (auto before = sortYAxis.begin(); before != sortYAxis.end(); ++before)
		{
			for (auto next = std::next(before); next != sortYAxis.end(); ++next)
			{
				const real minBefore = before->second.minimumY();
				const real maxBefore = before->second.maximumY();
				const real minNext = next->second.minimumY();
				const real maxNext = next->second.maximumY();

				if (!(maxBefore < minNext || maxNext < minBefore))
					yPairs.emplace_back(Body::BodyPair::generateBodyPair(before->first, next->first));
				else
					break;
			}
		}

		std::sort(xPairs.begin(), xPairs.end(), [](const Body::BodyPair& left, const Body::BodyPair& right)
			{
				return left.pairID < right.pairID;
			});
		std::sort(yPairs.begin(), yPairs.end(), [](const Body::BodyPair& left, const Body::BodyPair& right)
			{
				return left.pairID < right.pairID;
			});

		//double pointer check
		auto xPair = xPairs.begin();
		auto yPair = yPairs.begin();
		while (xPair != xPairs.end() && yPair != yPairs.end())
		{
			if (xPair->pairID == yPair->pairID && (xPair->bodyA->bitmask() & xPair->bodyB->bitmask()))
			{
				result.emplace_back(std::make_pair(xPair->bodyA, xPair->bodyB));
				xPair = std::next(xPair);
				yPair = std::next(yPair);
			}
			else if(xPair->pairID > yPair->pairID)
				yPair = std::next(yPair);
			else
				xPair = std::next(xPair);
		}

		return result;
		// Container::Vector<std::pair<Body *, Body *>> result;
		// if (bodyList.empty())
		// 	return result;

		// // 按X轴排序
		// Container::Vector<std::pair<Body *, AABB>> bodyBoxPairList;
		// bodyBoxPairList.reserve(bodyList.size());
		// for (auto &&elem : bodyList)
		// 	bodyBoxPairList.emplace_back(elem, elem->aabb());

		// std::sort(bodyBoxPairList.begin(), bodyBoxPairList.end(),
		// 		  [](const std::pair<Body *, AABB> &left, const std::pair<Body *, AABB> &right)
		// 		  {
		// 			  return left.second.minimumX() < right.second.minimumX();
		// 		  });

		// // 滑动窗口查找重叠
		// for (size_t i = 0; i < bodyBoxPairList.size(); ++i)
		// {
		// 	const auto &[bodyA, aabbA] = bodyBoxPairList[i];
		// 	for (size_t j = i + 1; j < bodyBoxPairList.size(); ++j)
		// 	{
		// 		const auto &[bodyB, aabbB] = bodyBoxPairList[j];
		// 		if (aabbA.maximumX() < aabbB.minimumX())
		// 			break; // 后面都不会重叠

		// 		if (bodyA == bodyB)
		// 			continue; // 排除自碰撞
		// 		if (aabbA.collide(aabbB) && (bodyA->bitmask() & bodyB->bitmask()))
		// 			result.emplace_back(bodyA, bodyB);
		// 	}
		// }
		// return result;
	}

	Container::Vector<Body *> SweepAndPrune::query(const Container::Vector<Body *> &bodyList, const AABB &region)
	{
		Container::Vector<Body *> result;

		Container::Vector<std::pair<Body *, AABB>> bodyBoxPairList;
		bodyBoxPairList.reserve(bodyList.size());

		for (auto &&elem : bodyList)
			bodyBoxPairList.emplace_back(std::make_pair(elem, elem->aabb()));

		// brute search
		for (auto &&elem : bodyBoxPairList)
			if (region.collide(elem.second))
				result.emplace_back(elem.first);

		return result;
	}
}
