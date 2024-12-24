#ifndef COMPRESSOR_STATION_H
#define COMPRESSOR_STATION_H

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

#include "utils.h"

class CompressorStation {
 private:
  static int id;
  std::string name;
  int totalWorkshops;
  int runningWorkshops;
  double efficiency;

 public:
  CompressorStation();

  int getId() const;
  std::string getName() const;
  double getUsagePercentage() const;

  void edit();

  void updateRunningWorkshops(int delta);

  friend std::istream& operator>>(std::istream& in, CompressorStation& cs);
  friend std::ostream& operator<<(std::ostream& out,
                                  const CompressorStation& cs);
  friend std::ifstream& operator>>(std::ifstream& fin, CompressorStation& cs);
  friend std::ofstream& operator<<(std::ofstream& fout,
                                   const CompressorStation& cs);
};

#endif  // COMPRESSOR_STATION_H
