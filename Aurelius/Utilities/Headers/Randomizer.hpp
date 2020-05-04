//
//  Randomizer.hpp
//  Aurelius
//
//  Created by Haakon Svane on 31/12/2019.
//  Copyright © 2019 Haakon Svane. All rights reserved.
//

#pragma once
#include <random>

namespace Randomizer{
namespace{
constexpr int min = 0;
constexpr int max = static_cast<int>(std::numeric_limits<int>::max()/2);
std::random_device rd;
std::mt19937 m(rd());
std::uniform_int_distribution<int> dist{min, max};
}
inline int random_int(const int lowest, const int highest){
    return dist(m)%(highest-lowest+1)+lowest;
}
}
