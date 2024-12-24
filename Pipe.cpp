#include "Pipe.h"

using namespace std;

int Pipe::id = 0;

Pipe::Pipe() : name(""), length(0.0), diameter(0.0), inRepair(false) { id++; 
  curent_id = id;
}

int Pipe::getId() const { return curent_id; }

std::string Pipe::getName() const { return name; }
double Pipe::getLength() const { return length; }
double Pipe::getDiameter() const { return diameter; }
bool Pipe::isInRepair() const { return inRepair; }

void Pipe::setName(const std::string& name) { this->name = name; }
void Pipe::setLength(double len) { this->length = len; }
void Pipe::setInRepair(bool inRepair) { this->inRepair = inRepair; }

void Pipe::edit() {
  cout << "Choose the pipe state:\n1. Pipe is under repair\n2. Pipe is "
          "operational\n";
  inRepair = (getCorrectNumber(1, 2) == 1);
}

istream& operator>>(istream& in, Pipe& Pp) {
  cout << "Enter pipe name: ";
  INPUT_LINE(in, Pp.name);
  cout << "Enter pipe length: ";
  Pp.length = getCorrectNumber(0.0, numeric_limits<double>::max());
  cout << "Enter pipe diameter: ";
  Pp.diameter = getCorrectNumber(0.0, numeric_limits<double>::max());
  cout << "Pipe state:\n1. Pipe is under repair\n2. Pipe is operational\n";
  Pp.inRepair = (getCorrectNumber(1, 2) == 1);
  return in;
}

ostream& operator<<(ostream& out, const Pipe& Pp) {
  out << "----------------------------------------\n";
  out << "Pipe information: (ID: " << Pp.getId() << ")\n";
  out << "Name: " << Pp.name << "\n";
  out << "Length: " << Pp.length << "\n";
  out << "Diameter: " << Pp.diameter << "\n";
  out << "State: " << (Pp.inRepair ? "Under repair" : "Operational") << "\n";
  out << "----------------------------------------\n";
  return out;
}

ifstream& operator>>(ifstream& fin, Pipe& Pp) {
  getline(fin, Pp.name);
  fin >> Pp.length >> Pp.diameter >> Pp.inRepair;
  return fin;
}

ofstream& operator<<(ofstream& fout, const Pipe& Pp) {
  fout << Pp.name << '\n'
       << Pp.length << ' ' << Pp.diameter << ' ' << Pp.inRepair << '\n';
  return fout;
}
