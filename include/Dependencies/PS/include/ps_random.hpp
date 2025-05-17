#ifndef PS_RANDOM_HPP
#define PS_RANDOM_HPP

#include <random>

#include "ps_common.hpp"

/**
 * @namespace ps
 * @brief 提供随机数生成工具和唯一ID管理功能。
 *
 * 该命名空间包含静态随机数生成器和 RandomGenerator 类。
 * 
 * RandomGenerator 类功能包括：
 *   - uniform(): 生成指定范围内的随机实数。
 *   - unique(): 返回唯一的无符号整数ID，并可复用已释放的ID。
 *   - pop(): 释放已分配的ID以便后续复用。
 *
 * 静态成员说明：
 *   - randomDevice: 用于为随机引擎提供熵源。
 *   - randomEngine: 64位Mersenne Twister随机数引擎。
 *   - uniformDistribution: 用于生成指定范围内的均匀分布整数的分布器。
 *   - m_emptyList: 存储已释放、可复用的ID列表。
 *   - m_startId: 新ID生成的起始计数器。
 */
namespace ps
{
	static std::random_device randomDevice;
	static std::mt19937_64 randomEngine(randomDevice());
	static std::uniform_int_distribution<uint32_t> uniformDistribution(10000, 99999);
	static std::vector<uint32_t> m_emptyList;
	static uint32_t m_startId = 1000;
	class RandomGenerator
	{
	public:
		static real uniform(const real& min, const real& max)
		{
			std::uniform_real_distribution<real> distribution(min, max);
			return distribution(randomEngine);
		}
		static unsigned int unique()
		{
			//return uniformDistribution(randomEngine);
			if(!m_emptyList.empty())
			{
				auto result = m_emptyList.back();
				m_emptyList.pop_back();
				return result;
			}
			return m_startId++;
		}

		static void pop(uint32_t id)
		{
			m_emptyList.push_back(id);
		}
	};
}

#endif