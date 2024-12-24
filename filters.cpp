#include "filters.h"

bool checkPipeInRepair(const Pipe& Pp, bool in_rep) {
  return Pp.isInRepair() == in_rep;
}

bool check_getUsagePercentage(const CompressorStation& Cs, double percent) {
  return Cs.getUsagePercentage() >= percent;
}

// void filter_pipes(std::unordered_map<int, Pipe>& pipes) {
//   std::cout << "1.Filter by name" << std::endl
//             << "2.Filter by \"In repearing\"" << std::endl
//             << "3.Filter by \"Working\"" << std::endl;
//   int choice = getCorrectNumber(1, 4);
//   std::unordered_set<int> ids;

//   switch (choice) {
//     case 1: {
//       std::string name;
//       std::cout << "Input name of pipe: ";
//       std::cin.ignore(10000, '\n');
//       std::getline(std::cin, name);
//       ids = findIds(pipes, checkByName, name);
//       break;
//     }
//     case 2:
//       ids = findIds(pipes, check_pipe_in_rep, true);
//       break;
//     case 3:
//       ids = findIds(pipes, check_pipe_in_rep, false);
//       break;
//     default:
//       break;
//   }

//   if (show(ids, pipes)) {
//     std::cout << "1.close" << std::endl << "2.filter pipes" << std::endl;
//     choice = getCorrectNumber(1, 3);

//     switch (choice) {
//       case 1: {
//         return;
//         break;
//       }
//         //     case 2: {

//         // 		choice = choose();

//         // 		if (choice == 2)
//         // 			ids = get_new_ids(ids);

//         // 		choice = del_or_edit();

//         // 		if (choice == 1) del_objects(ids, pipes);
//         // 		if (choice == 2) {
//         // 			bool in_rep;
//         // 			std::cout << "Choose status: 1.In
//         // repairing, 2.Working" << std::endl; 			in_rep =
//         // pipe_in_rep_input(); 			change_in_rep(in_rep,
//         // ids, pipes);
//         // }
//         // }
//       default:
//         break;
//     }
//   }
// }

// void filter_compressor_stations(
//     std::unordered_map<int, CompressorStation>& compressor_stations) {
//   std::cout << "1.Filter by name" << std::endl
//             << "2.Filter by \"percent of used worcstataoins >= \"" << std::endl;
//   int choice = getCorrectNumber(1, 5);
//   std::unordered_set<int> ids;

//   if (choice == 1) {
//     std::string name;
//     std::cout << "Input name of CS: ";
//     std::cin.ignore(10000, '\n');
//     std::getline(std::cin, name);
//     INPUT_LINE(std::cin, name);
//     ids = findIds(compressor_stations, checkByName, name);
//   }

//   if (choice == 2) {
//     std::cout << "Input percent: ";
//     double percent = getCorrectNumber(0.0, 100.0);
//     ids = findIds(compressor_stations, check_getUsagePercentage, percent);
//   }

//   if (show(ids, compressor_stations)) {
//     std::cout << "1.close" << std::endl << "2.filter CS" << std::endl;
//     choice = getCorrectNumber(1, 3);

//     if (choice == 1) {
//       return;
//     }

    // if (choice == 2) {

    // 	choice = choose();

    // 	if (choice == 2)
    // 		ids = get_new_ids(ids);

    // 	choice = del_or_edit();

    // 	if (choice == 1) del_objects(ids, compressor_stations);
    // 	if (choice == 2) {
    // 		std::cout << "Input number of workshops to add: ";
    // 		int num = getCorrectNumber(-std::numeric_limits<int>::max(),
    // std::numeric_limits<int>::max()); 		change_run_ws(num, ids,
    // compressor_stations);
    // 	}
    // }
  // }
// }
