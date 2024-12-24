#ifndef PUDOVNIN_H
#define PUDOVNIN_H
#include <chrono>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Compressor_station.h"
#include "Pipe.h"
#include "dataloader.h"
#include "filters.h"
#include "utils.h"

/**
 * Adds a new object to an unordered_map container.
 *
 * This function reads an object of type T from the input, retrieves its ID using the `getId` method,
 * and inserts the object into the provided unordered_map. The ID is used as the key for the map.
 * 
 * @tparam T The type of objects stored in the unordered_map.
 *           The type T must have `getId` and `operator>>` implemented.
 * @param map An unordered_map container where the keys are IDs (int)
 *            and the values are objects of type T.
 */
template <typename T>
void addObject(std::unordered_map<int, T>& map) {
    // Create a new object and read its properties from input.
    T newObject;
    std::cin >> newObject;

    // Insert the object into the map using its ID as the key.
    auto result = map.insert({newObject.getId(), newObject});

    // Notify the user of the success or failure of the operation.
    if (result.second) {
        std::cout << "Object successfully added.\n";
    } else {
        std::cout << "Failed to add object. An object with the same ID already exists.\n";
    }
}

/**
 * Deletes an object from an unordered_map container by its ID.
 *
 * This function displays the objects in the map using the `show` function,
 * prompts the user to select an object ID, and then attempts to delete the object
 * with the specified ID using the `deleteById` function.
 * 
 * @tparam T The type of objects stored in the unordered_map.
 * @param map An unordered_map container where the keys are IDs (int) 
 *            and the values are objects of type T.
 */
template <typename T>
void deleteObject(std::unordered_map<int, T>& map)
{
    // Display the objects in the map; exit if no objects are shown.
    if (!show(map)) return;

    // Prompt the user to select an object ID for deletion.
    std::cout << "Select the object ID to delete: ";
    int id = getCorrectNumber(0, std::numeric_limits<int>::max());

    // Attempt to delete the object and provide feedback to the user.
    if (deleteById(id, map))
        std::cout << "Object was successfully deleted.\n";
    else
        std::cout << "No object found with the specified ID.\n";
}

/**
 * Edits an object in an unordered_map container by its ID.
 *
 * This function displays the objects in the map using the `show` function,
 * prompts the user to enter an object ID, and, if the object exists, calls
 * its `edit` method. Provides appropriate feedback to the user based on the
 * success or failure of the operation.
 * 
 * @tparam T The type of objects stored in the unordered_map.
 * @param map An unordered_map container where the keys are IDs (int) 
 *            and the values are objects of type T.
 */
template <typename T>
void editObject(std::unordered_map<int, T>& map) {
    // Display the objects in the map; exit if no objects are shown.
    if (!show(map)) return;

    // Prompt the user to input an object ID for editing.
    std::cout << "Enter the object ID to edit: ";
    int id = getCorrectNumber(0, std::numeric_limits<int>::max());

    // Check if the object with the given ID exists in the map.
    auto it = map.find(id);
    if (it != map.end()) {
        
        it->second.edit();  // Call the `edit` method on the found object.
        std::cout << "Object was successfully edited.\n";
    } else {
        std::cout << "No object found with the specified ID.\n";
    }
}

#endif