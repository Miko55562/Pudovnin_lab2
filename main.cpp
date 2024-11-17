#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

class Pipeline {
 public:
  Pipeline() : name(""), length(-1), diameter(-1), inRepair(false) {}

  // Геттеры
  string getName() const { return name; }
  float getLength() const { return length; }
  float getDiameter() const { return diameter; }
  bool isInRepair() const { return inRepair; }

  // Сеттеры
  void setName(const string &n) { name = n; }
  void setLength(float l) { length = l > 0 ? l : -1; }
  void setDiameter(float d) { diameter = d > 0 ? d : -1; }
  void setInRepair(bool repair) { inRepair = repair; }

  void AddPipeline() {
    cout << "Enter pipe name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter pipe length: ";
    validInput(length);
    while (length <= 0) {
      cout << "Enter pipe length >0: ";
      validInput(length);
    }
    cout << "Enter pipe diameter: ";
    validInput(diameter);
    while (diameter <= 0) {
      cout << "Enter pipe diameter >0: ";
      validInput(diameter);
    }
    inRepair = false;
    cout << endl;
  }

  void Edit() {
    if (!name.empty()) {
      cout << "Pipe is repair?: ";
      validInput(inRepair);
    } else {
      cout << "Pipe not created\n";
    }
  }

  void Save(ofstream &file) const {
    file << name << "\n" << length << " " << diameter << " " << inRepair << endl;
  }

  void Load(ifstream &file) {
    getline(file, name);
    string line;
    getline(file, line);
    istringstream iss(line);
    iss >> length >> diameter >> inRepair;
  }

  friend ostream &operator<<(ostream &os, const Pipeline &pipe) {
    return os << "name: " << pipe.name << "\nlength: " << pipe.length
              << "\ndiameter: " << pipe.diameter << "\ninRepair: " << pipe.inRepair << endl
              << endl;
  }

 private:
  string name;
  float length;
  float diameter;
  bool inRepair;

  template <typename T>
  void validInput(T &arg) {
    while (!(cin >> arg)) {
      cout << "Please enter a valid value\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
};

class CompressorStation {
 public:
  CompressorStation() : name(""), totalWorkshops(-1), activeWorkshops(-1), efficiency(-1) {}

  // Геттеры
  string getName() const { return name; }
  int getTotalWorkshops() const { return totalWorkshops; }
  int getActiveWorkshops() const { return activeWorkshops; }
  float getEfficiency() const { return efficiency; }

  // Сеттеры
  void setName(const string &n) { name = n; }
  void setTotalWorkshops(int total) { totalWorkshops = total >= 0 ? total : -1; }
  void setActiveWorkshops(int active) {
    activeWorkshops = (active >= 0 && active <= totalWorkshops) ? active : -1;
  }
  void setEfficiency(float eff) { efficiency = (eff >= 0 && eff <= 1) ? eff : -1; }

  void AddCompressorStation() {
    cout << "Enter station name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter total number of workshops: ";
    validInput(totalWorkshops);
    activeWorkshops = 0;
    cout << "Enter efficiency (0-1): ";
    validInput(efficiency);
    while (efficiency < 0 || efficiency > 1) {
      cout << "Enter efficiency (0-1): ";
      validInput(efficiency);
    }
    cout << endl;
  }

  void Edit() {
    if (!name.empty()) {
      cout << "Enter active workshops: ";
      validInput(activeWorkshops);
      while (activeWorkshops > totalWorkshops) {
        cout << "Enter active workshops <= totalWorkshops: ";
        validInput(activeWorkshops);
      }
    } else {
      cout << "Compressor Station not created\n";
    }
  }

  void Save(ofstream &file) const {
    file << name << "\n" << totalWorkshops << " " << activeWorkshops << " " << efficiency << endl;
  }

  void Load(ifstream &file) {
    getline(file, name);
    string line;
    getline(file, line);
    istringstream iss(line);
    iss >> totalWorkshops >> activeWorkshops >> efficiency;
  }

  friend ostream &operator<<(ostream &os, const CompressorStation &cs) {
    return os << "name: " << cs.name << "\ntotalWorkshops: " << cs.totalWorkshops
              << "\nactiveWorkshops: " << cs.activeWorkshops << "\nefficiency: " << cs.efficiency
              << endl
              << endl;
  }

 private:
  string name;
  int totalWorkshops;
  int activeWorkshops;
  float efficiency;

  template <typename T>
  void validInput(T &arg) {
    while (!(cin >> arg)) {
      cout << "Please enter a valid value\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
};

class SystemManager {
 public:
  void SaveData(const Pipeline &pipe, const CompressorStation &cs) {
    ofstream file("data.txt");
    if (!file.is_open()) {
      cerr << "Failed to open file for saving." << endl;
      return;
    }
    if (!pipe.getName().empty()) {
      file << "pipe" << endl;
      pipe.Save(file);
    }
    if (!cs.getName().empty()) {
      file << "cs" << endl;
      cs.Save(file);
    }
    file.close();
    cout << "Data saved successfully." << endl;
  }

  void LoadData(Pipeline &pipe, CompressorStation &cs) {
    ifstream file("data.txt");
    if (!file.is_open()) {
      cerr << "Failed to open file for loading." << endl;
      return;
    }
    string line;
    while (getline(file, line)) {
      if (line == "pipe") {
        pipe.Load(file);
      } else if (line == "cs") {
        cs.Load(file);
      }
    }
    cout << "Data loaded successfully." << endl;
  }
};

int main() {
  char key;
  Pipeline pipeline;
  CompressorStation compressorstation;
  SystemManager systemManager;

  while (key != '0') {
    cout << "1. Add Pipe" << endl;
    cout << "2. Add Compressor Station" << endl;
    cout << "3. View All Objects" << endl;
    cout << "4. Edit Pipe (Toggle Repair Status)" << endl;
    cout << "5. Edit Compressor Station (Start/Stop Workshop)" << endl;
    cout << "6. Save Data" << endl;
    cout << "7. Load Data" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose an option: ";

    cin >> key;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (key) {
      case '1':
        pipeline.AddPipeline();
        break;
      case '2':
        compressorstation.AddCompressorStation();
        break;
      case '3':
        if (!pipeline.getName().empty()) cout << endl << pipeline;
        if (!compressorstation.getName().empty()) cout << compressorstation;
        break;
      case '4':
        pipeline.Edit();
        break;
      case '5':
        compressorstation.Edit();
        break;
      case '6':
        systemManager.SaveData(pipeline, compressorstation);
        break;
      case '7':
        systemManager.LoadData(pipeline, compressorstation);
        break;
      default:
        cout << "Invalid option! Try again." << endl;
    }
  }
  return 0;
}
