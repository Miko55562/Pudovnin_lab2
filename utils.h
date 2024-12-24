#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>

/**
 * Macro to read a full line from the input stream, trimming leading whitespaces.
 * The line is also logged to `std::cerr` for debugging.
 * 
 * @param in Input stream.
 * @param str String variable to store the input.
 */
#define INPUT_LINE(in, str)    \
  getline(in >> std::ws, str); \
  std::cerr << str << std::endl

/**
 * Macro to print a parameter's name and value to the output stream.
 * 
 * @param out Output stream.
 * @param x Variable to print.
 */
#define PRINT_PARAM(out, x) out << #x << "=" << x << std::endl

/**
 * Class to temporarily redirect the output stream.
 */
class RedirectOutputWrapper {
  std::streambuf* const oldBuf;  ///< Pointer to the original buffer.
  std::ostream& stream;         ///< Reference to the stream being redirected.

 public:
  explicit RedirectOutputWrapper(std::ostream& src)
      : oldBuf(src.rdbuf()), stream(src) {}

  ~RedirectOutputWrapper() { stream.rdbuf(oldBuf); }

  /**
   * Redirects the stream to the destination stream.
   * 
   * @param dest Destination stream.
   */
  void redirect(std::ostream& dest) { stream.rdbuf(dest.rdbuf()); }
};

/**
 * Prompts the user to input a number within a specified range.
 * Validates the input type and range.
 * 
 * @tparam T Type of the number (e.g., int, double).
 * @param min Minimum acceptable value.
 * @param max Maximum acceptable value.
 * @return A valid number entered by the user.
 */
template <typename T>
T getCorrectNumber(T min, T max) {
  T x;
  while ((std::cin >> x).fail()      // Check input type
         || std::cin.peek() != '\n'  // Ensure buffer is empty
         || x < min || x > max) {    // Check range
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Type a number (" << min << " - " << max << "): ";
  }
  std::cerr << x << std::endl;  // Debug output
  return x;
}

/**
 * Finds the maximum ID among the objects in a map.
 * 
 * @tparam T Type of the objects in the map.
 * @param map The map containing the objects.
 * @return The maximum ID or 0 if the map is empty.
 */
template <typename T>
int getMaxId(const std::unordered_map<int, T>& map) {
  if (map.empty()) return 0;
  int maxId = 0;
  for (const auto& [key, object] : map) {
    if (object.getId() > maxId) {
      maxId = object.getId();
    }
  }
  return maxId;
}

/**
 * Deletes an object from a map by its ID.
 * 
 * @tparam T Type of the objects in the map.
 * @param id ID of the object to delete.
 * @param map The map containing the objects.
 * @return True if the object was found and deleted, false otherwise.
 */
template <typename T>
bool deleteById(int id, std::unordered_map<int, T>& map) {
  if (map.find(id) == map.end()) return false;
  map.erase(id);
  return true;
}

template <typename T>
void deleteObjects(std::unordered_set<int>& ids, std::unordered_map<int, T>& objects) {
	for (int i : ids) {
		objects.erase(i);
	}
}

/**
 * Displays all objects in a map.
 * 
 * @tparam T Type of the objects in the map.
 * @param map The map containing the objects.
 * @return True if there are objects to display, false otherwise.
 */
template <typename T>
bool show(const std::unordered_map<int, T>& map) {
  if (!map.empty()) {
    for (const auto& [id, object] : map) {
      std::cout << "Object ID: " << id << std::endl;
      std::cout << object;
    }
    return true;
  } else {
    std::cout << "There are no objects." << std::endl;
    return false;
  }
}

/**
 * Displays objects from a map based on a set of IDs.
 * 
 * @tparam T Type of the objects in the map.
 * @param ids The set of IDs to display.
 * @param objects The map containing the objects.
 * @return True if there are objects to display, false otherwise.
 */
template <typename T>
bool show(const std::unordered_set<int>& ids,
          const std::unordered_map<int, T>& objects) {
  if (!ids.empty()) {
    for (int id : ids) {
      std::cout << "Object ID: " << id << std::endl;
      std::cout << objects.at(id);  // Safe access assuming ID exists
    }
    return true;
  } else {
    std::cout << "There are no such objects." << std::endl;
    return false;
  }
}

#endif  // UTILS_H
