#ifndef PHYSICAL_SIMULATION_RANDOM_HPP
#define PHYSICAL_SIMULATION_RANDOM_HPP

#include <random>

#include "ps_common.hpp"

namespace ps
{
	static std::random_device randomDevice;
	static std::mt19937_64 randomEngine(randomDevice());
	static std::uniform_int_distribution<uint32_t> uniformDistribution(10000, 99999);
	static std::vector<uint32_t> m_emptyList;
	static uint32_t m_startId = 1000;
	class   RandomGenerator
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