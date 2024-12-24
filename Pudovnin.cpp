#include "Pudovnin.h"

using namespace std;
using namespace chrono;

std::unordered_set<int> get_new_ids(std::unordered_set<int> ids) {
  std::unordered_set<int> new_ids;
  int id;
  while (true) {
    std::cout << "Input -1 to close." << std::endl << "Input selected id: ";
    id = getCorrectNumber(-1, std::numeric_limits<int>::max());

    if (id == -1) {
      break;
    }

    else if (ids.find(id) != ids.end()) {
      new_ids.insert(id);
    } else {
      std::cout << "There is no object with that id" << std::endl;
    }
  }
  return new_ids;
}

bool pipeInputEdit() {
  cout << "Выберите состояние трубы:\n1. Труба находится в ремонте\n2. Труба "
          "работает\n";
  return getCorrectNumber(1, 2) == 1;
}

bool csInputEdit() {
  cout << "Выберите состояние трубы:\n1. Труба находится в ремонте\n2. Труба "
          "работает\n";
  return getCorrectNumber(1, 2) == 1;
}

int choose() {
  std::cout << "1.Choose all objects" << std::endl;
  std::cout << "2.Choose some objects" << std::endl;
  return getCorrectNumber(1, 3);
}

int del_or_edit() {
  std::cout << "1.Delete objects" << std::endl;
  std::cout << "2.Edit objects" << std::endl;
  return getCorrectNumber(1, 3);
}

void filter_pipe(unordered_map<int, Pipe>& pipes) {
  if (pipes.size() == 0) {
    cout << "There are no Pipes\n";
    return;
  }
  cout << "1.Filter by name" << std::endl
        << "2.Filter by \"In repearing\"" << std::endl
        << "3.Filter by \"Working\"" << std::endl;
  int choice = getCorrectNumber(1, 4);
  std::unordered_set<int> ids;
  switch (choice) {
    case 1: {
      string name;
      cout << "Input name of pipe: ";
      INPUT_LINE(cin, name);
      filterBy(ids, pipes, checkByName, name);
      break;
    }
    case 2:
      filterBy(ids, pipes, checkPipeInRepair, true);
      break;
    case 3:
      filterBy(ids, pipes, checkPipeInRepair, false);
      break;
    default:
      break;
  }
  if (show(ids, pipes)) {
    std::cout << "1.close" << std::endl
              << "2.filter pipes" << std::endl;
    choice = getCorrectNumber(1, 3);

    switch (choice) {
      case 1: {
        break;
      }
      case 2: {
        ids = get_new_ids(ids);
        choice = del_or_edit();
        switch (choice)
        {
        case 1:
          deleteObjects(ids, pipes);
          break;
        case 2: {
          bool in_rep;
          std::cout << "Choose status: 1.In repairing, 2.Working" << std::endl;
          in_rep = pipeInputEdit();
          for (int i : ids) {
            pipes[i].setInRepair(in_rep);
          }
          break;
        }
        default:
          break;
        }
      } 
    }
  }
}

void printComands() {
  cout << "1. Add a pipe\n";
  cout << "2. Add a CS\n";
  cout << "3. View all objects\n";
  cout << "4. Delete single pipe\n";
  cout << "5. Delete single CS\n";
  cout << "6. Edit single pipe\n";
  cout << "7. Edit single CS\n";
  cout << "8. Filter pipes\n";
  cout << "9. Filter CS\n";
  cout << "10. Save\n";
  cout << "11. Load\n";
  cout << "0. Exit\n";
  cout << "\nEnter your choice: ";
}

int main() {
  RedirectOutputWrapper cerr_out(cerr);
  string time = "";
  ofstream logfile("log_" + time + ".txt");
  if (logfile) cerr_out.redirect(logfile);
  unordered_map<int, Pipe> pipes;
  unordered_map<int, CompressorStation> compressor_stations;
  int choice;

  while (true) {
    printComands();
    choice = getCorrectNumber(0, 12);
    switch (choice) {
      case 1:
        addObject(pipes);
        break;
      case 2:
        addObject(compressor_stations);
        break;
      case 3:
        cout << "Pipes:\n";
        show(pipes);
        cout << "Compresor stations:\n";
        show(compressor_stations);
        break;
      case 4:
        deleteObject(pipes);
        break;
      case 5:
        deleteObject(compressor_stations);
        break;
      case 6:
        editObject(pipes);
        break;
      case 7:
        editObject(compressor_stations);
        break;
      case 8: {
        filter_pipe(pipes);
        break;
      }
      case 9: {
        if (compressor_stations.size() != 0)
          cout << "in develop\n";
          // filterCompressorStations(compressor_stations);
        else
          cout << "There are no CS\n";
        break;
      }
      case 10: {
        string name;
        cout << "Input name of file for saving: ";
        INPUT_LINE(cin, name);
        if (save_data(name, pipes, compressor_stations))
          cout << "Data was saved\n";
        else
          cout << "Data was not saved\n";
        break;
      }
      case 11: {
        string name;
        cout << "Input name of file for loading: ";
        INPUT_LINE(cin, name);
        if (read_data(name, pipes, compressor_stations))
          cout << "Data was loaded\n";
        else
          cout << "There is no file with that name\n";
        break;
      }
      case 0: {
        cout << "Goodbye\n";
        return 0;
      }
      default: {
        cout << "Invalid choice\n";
        break;
      }
    }
  }
}