#include "dataloader.h"

bool save_data(
    std::string f_name, const std::unordered_map<int, Pipe> &pipes,
    const std::unordered_map<int, CompressorStation> &compressor_stations) {
  std::ofstream file;
  file.open(f_name + ".txt");
  if (file.is_open()) {
    file << pipes.size() << ' ' << compressor_stations.size() << std::endl;

    for (const auto &Pp : pipes) {
      file << Pp.first << std::endl;
      file << Pp.second;
    }

    for (const auto &Cs : compressor_stations) {
      file << Cs.first << std::endl;
      file << Cs.second;
    }
    file.close();
    return true;
  }
  return false;
}

bool read_data(
    std::string f_name, std::unordered_map<int, Pipe> &pipes,
    std::unordered_map<int, CompressorStation> &compressor_stations) {
  std::ifstream file_handler;
  file_handler.open(f_name + ".txt");
  std::string name;

  if (file_handler.is_open()) {
    pipes.clear();
    compressor_stations.clear();

    int num_Pp;
    int num_Cs;
    file_handler >> num_Pp >> num_Cs;

    for (int i(0); i < num_Pp; ++i) {
      Pipe Pp;
      file_handler >> Pp;
      pipes[Pp.getId()] = Pp;
    }

    for (int i(0); i < num_Cs; ++i) {
      CompressorStation Cs;
      file_handler >> Cs;
      compressor_stations[Cs.getId()] = Cs;
    }

    file_handler.close();
    return true;

  }

  else {
    return false;
  }
}