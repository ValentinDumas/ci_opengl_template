//
// Created by ThomasBI on 06/03/2018.
//

#ifndef DREAMINENGINE_COMPONENTSTORE_H
#define DREAMINENGINE_COMPONENTSTORE_H

#include <vector>
#include <unordered_map>

template <class T>
class ComponentStore {

private:
	std::vector<T*> vector;
	std::unordered_map<unsigned int, unsigned int> map;

public:

	std::vector<T*>& getVector() { return vector; }
	std::unordered_map<unsigned int, unsigned int>& getMap() { return map; };

	void add(T* obj, unsigned int id) {
		vector.emplace_back(obj);
		map[id] = vector.size() - 1;
	}

	// NOTE: The if/elsif statement is almost optional in this function: we could have done a if/if statement
	// NOTE: The choice of this statement is ONLY for PERFORMANCE purpose !
	bool remove(unsigned int instance_id) {
		if (vector.empty()) return false;
		if (map.empty()) return false;

		int vector_id = map[instance_id]; // Get the vector id from the given (entity/component) ID;
		int last = vector.size() - 1;
		
		vector[vector_id] = vector[last]; // Last comes to front (->continguous)

		std::unordered_map<unsigned int, unsigned int>::iterator itCopy;
		for (auto it = map.begin(); it != map.end(); ++it)
		{
			// Looks for the "filled vector id" in the map => to ERASE it
			if (it->second == vector_id)
			{
				itCopy = it;
			}
			// Looks for the "last vector id" value in the map => to UPDATE it
			else if (it->second == last)
			{
				map[it->first] = vector_id;
			}
		}
		map.erase(itCopy->first);

		vector.pop_back(); // remove last ;)

		return true;
	}

	T*& get(unsigned int indice) {
		return vector[map[indice]];
	};

	void kill() {
		for (auto it = vector.begin(); it != vector.end(); ++it)
		{
			delete (*it);
		}
		vector.clear();
	}

	~ComponentStore() {
		/*for (auto it = vector.begin() ; it != vector.end(); ++it)
		{
			delete (*it);
		}
		vector.clear();*/
	}
};

#endif //DREAMINENGINE_COMPONENTSTORE_H
