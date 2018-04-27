#include <string>

// Convert an integer array to string using a joiner
template<class T> std::string array_to_string(T array[], size_t size, std::string join="", std::string end="", std::string start="") {
	std::string output = start;
	if(size > 0) output += std::to_string(array[0]);
	for(T i = 1; i < size; i++) output += join + std::to_string(array[i]);
	return output + end;
}
