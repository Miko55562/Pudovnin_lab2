#include "Compressor_station.h"

using namespace std;

int CompressorStation::id = 0;

CompressorStation::CompressorStation()
    : name(""), totalWorkshops(0), runningWorkshops(0), efficiency(0.0) {
  id++;
}

int CompressorStation::getId() const { return id; }

string CompressorStation::getName() const { return name; }

double CompressorStation::getUsagePercentage() const {
  return totalWorkshops > 0
             ? (static_cast<double>(runningWorkshops) / totalWorkshops) * 100
             : 0.0;
}

void CompressorStation::edit() {
  cout << "Input new number of running workshops (0 to " << totalWorkshops
       << "): ";
  runningWorkshops = getCorrectNumber(0, totalWorkshops);
}

void CompressorStation::updateRunningWorkshops(int num) {
  if (runningWorkshops + num > totalWorkshops) {
    cout << "Cannot add more running workshops than total workshops (ID: "
         << getId() << ")" << endl;
    runningWorkshops = totalWorkshops;
  } else if (runningWorkshops + num < 0) {
    cout << "Cannot have negative running workshops (ID: " << getId() << ")"
         << endl;
    runningWorkshops = 0;
  } else {
    cout << "Updating number of running workshops (ID: " << getId() << ")"
         << endl;
    runningWorkshops += num;
  }
}

istream& operator>>(istream& in, CompressorStation& Cs) {
  cout << "Enter compressor station name: ";
  INPUT_LINE(in, Cs.name);

  cout << "Enter total number of workshops: ";
  Cs.totalWorkshops = getCorrectNumber(0, numeric_limits<int>::max());

  cout << "Enter number of running workshops: ";
  Cs.runningWorkshops = getCorrectNumber(0, Cs.totalWorkshops);

  cout << "Enter station efficiency: ";
  Cs.efficiency = getCorrectNumber(0.0, numeric_limits<double>::max());

  return in;
}

ostream& operator<<(ostream& out, const CompressorStation& Cs) {
  out << "----------------------------------------------------------------\n"
      << "Compressor Station (ID: " << Cs.id << ")\n"
      << "Name: " << Cs.name << "\n"
      << "Total Workshops: " << Cs.totalWorkshops << "\n"
      << "Running Workshops: " << Cs.runningWorkshops << "\n"
      << "Efficiency: " << Cs.efficiency << "\n"
      << "Usage: " << Cs.getUsagePercentage() << "%\n"
      << "----------------------------------------------------------------\n";

  return out;
}

ifstream& operator>>(ifstream& fin, CompressorStation& Cs) {
  fin >> Cs.id;
  fin.ignore();
  getline(fin, Cs.name);
  fin >> Cs.totalWorkshops >> Cs.runningWorkshops >> Cs.efficiency;
  return fin;
}

ofstream& operator<<(ofstream& fout, const CompressorStation& Cs) {
  fout << Cs.id << '\n'
       << Cs.name << '\n'
       << Cs.totalWorkshops << ' ' << Cs.runningWorkshops << ' '
       << Cs.efficiency << '\n';

  return fout;
}
