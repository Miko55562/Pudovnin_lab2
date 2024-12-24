#include "Pipe.h"

using namespace std;

int Pipe::id = 0;

Pipe::Pipe() : name(""), length(0.0), diameter(0.0), inRepair(false) { id++; }

int Pipe::getId() const { return id; }

std::string Pipe::getName() const { return name; }
double Pipe::getLength() const { return length; }
double Pipe::getDiameter() const { return diameter; }
bool Pipe::isInRepair() const { return inRepair; }

void Pipe::setName(const std::string& name) { this->name = name; }
void Pipe::setLength(double len) { this->length = len; }
void Pipe::setInRepair(bool inRepair) { this->inRepair = inRepair; }

void Pipe::edit() {
  cout << "Выберите состояние трубы:\n1. Труба находится в ремонте\n2. Труба "
          "работает\n";
  inRepair = (getCorrectNumber(1, 2) == 1);
}

istream& operator>>(istream& in, Pipe& Pp) {
  cout << "Введите имя трубы: ";
  INPUT_LINE(in, Pp.name);
  cout << "Введите длину трубы: ";
  Pp.length = getCorrectNumber(0.0, numeric_limits<double>::max());
  cout << "Введите диаметр трубы: ";
  Pp.diameter = getCorrectNumber(0.0, numeric_limits<double>::max());
  cout << "Состояние трубы:\n1. Труба в ремонте\n2. Труба работает\n";
  Pp.inRepair = (getCorrectNumber(1, 2) == 1);
  return in;
}

ostream& operator<<(ostream& out, const Pipe& Pp) {
  out << "----------------------------------------\n";
  out << "Информация о трубе:\n";
  out << "Имя: " << Pp.name << "\n";
  out << "Длина: " << Pp.length << "\n";
  out << "Диаметр: " << Pp.diameter << "\n";
  out << "Состояние: " << (Pp.inRepair ? "В ремонте" : "Работает") << "\n";
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
