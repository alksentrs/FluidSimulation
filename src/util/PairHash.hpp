/*
 * PairHash.hpp
 *
 *  Created on: 27 de mar. de 2025
 *      Author: aleksander
 */

#ifndef UTIL_PAIRHASH_HPP_
#define UTIL_PAIRHASH_HPP_

// Hash para std::pair<int, int>
struct PairHash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

#endif /* UTIL_PAIRHASH_HPP_ */
