#ifndef DATALOADER_H
#define DATALOADER_H
#include <iostream>

#include "Compressor_station.h"
#include "Pipe.h"

bool save_data(
    std::string f_name, const std::unordered_map<int, Pipe> &pipes,
    const std::unordered_map<int, CompressorStation> &compressor_stations);
bool read_data(std::string f_name, std::unordered_map<int, Pipe> &pipes,
               std::unordered_map<int, CompressorStation> &compressor_stations);

#endif