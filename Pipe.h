#ifndef PIPE_H
#define PIPE_H

#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

#include "utils.h"

class Pipe {
 private:
  static int id;
  std::string name;
  double length;
  double diameter;
  bool inRepair;

 public:
  Pipe();
  
  int getId() const;

  std::string getName() const;
  double getLength() const;
  double getDiameter() const;
  bool isInRepair() const;

  void setName(const std::string& name);
  void setLength(double length);
  void setInRepair(bool inRepair);

  void edit();

  friend std::istream& operator>>(std::istream& in, Pipe& pipe);
  friend std::ifstream& operator>>(std::ifstream& fin, Pipe& pipe);
  friend std::ostream& operator<<(std::ostream& out, const Pipe& pipe);
  friend std::ofstream& operator<<(std::ofstream& fout, const Pipe& pipe);
};

#endif  // PIPE_H