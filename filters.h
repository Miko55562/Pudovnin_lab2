#ifndef FILTERS_H
#define FILTERS_H
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "Compressor_station.h"
#include "Pipe.h"
#include "utils.h"

bool checkPipeInRepair(const Pipe& Pp, bool in_rep);
bool check_getUsagePercentage(const CompressorStation& Cs, double percent);
// void filter_pipes(std::unordered_map<int, Pipe>& pipes);
// void filterCompressorStations(
//     std::unordered_map<int, CompressorStation>& compressor_stations);

template <typename T>
bool checkByName(const T& object, std::string name) {
  return object.getName().find(name) != std::string::npos;
}

template <typename K, typename T>
using filter = bool (*)(const K&, T);

template <typename K, typename T>
std::unordered_set<int> find_ids(std::unordered_map<int, K>& map,
                                 filter<K, T> filter, T params) {
  std::unordered_set<int> ids;

  for (const auto& object : map) {
    if (filter(object.second, params)) {
      ids.insert(object.first);
    }
  }
  return ids;
}

template <typename K, typename T>
std::unordered_set<int> filterBy(std::unordered_set<int>& ids,
                                 std::unordered_map<int, K>& map,
                                 filter<K, T> filter, T params) {
  for (const auto& object : map) {
    if (filter(object.second, params)) {
      ids.insert(object.first);
    }
  }

  return ids;
}

#endif