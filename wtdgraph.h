//Samantha Lee PA 2 

#ifndef WTDGRAPH_H
#define WTDGRAPH_H
#include <cassert>
#include <cstdlib> 
#include <map>
#include "graph.h"

namespace main_savitch_15 {

	template <class Item>
	class wtdgraph : public graph<Item>
	{
	public:
	// define all constructors:
    	wtdgraph();
    	wtdgraph(std::size_t initial_allocation);
    	wtdgraph(const wtdgraph &source);

// make destructor virtual:
    	virtual ~wtdgraph();

// overload add_edge with default weight parameter:
    	void add_edge(std::size_t source, std::size_t target,
                  std::size_t weight=0);

// redefine others as needed to handle weights:
   	 	void remove_edge(std::size_t source, std::size_t target);
    	wtdgraph<Item> &operator=(const wtdgraph &source);

// override resize function to allocate weights:
    	virtual void resize(std::size_t new_allocation);

// add edge_weight function to return a weight:
    	std::size_t edge_weight(std::size_t source, std::size_t target) const;

	private:
		std::size_t sizeWeights;
// need a way to store the weights - for example:
    	std::map<std::size_t, std::size_t> *weights;
    	bool **edges;
	};
}


namespace main_savitch_15 {

template <class Item>
wtdgraph<Item>::wtdgraph() : graph<Item>() {
	sizeWeights = 0;
	weights = new std::map<std::size_t, std::size_t>[sizeWeights]; 
}

template <class Item>
wtdgraph<Item>::wtdgraph(std::size_t initial_allocation) : graph<Item>(initial_allocation) {
	sizeWeights = initial_allocation;
	weights = new std::map<std::size_t, std::size_t>[initial_allocation];

 }

//copy constructor
template <class Item>
wtdgraph<Item>::wtdgraph(const wtdgraph &source) : graph<Item>(source)
{
	sizeWeights = source.sizeWeights;
	weights = new std::map<std::size_t, std::size_t>[source.sizeWeights];
	std::copy(source.weights, source.weights + sizeWeights, weights);
	for (int i = 0; i < source.sizeWeights; i++) {
		weights[i] = source.weights[i];
    }
}
    // allocate space for weights only
    // then loop to copy just the weights from source

template <class Item>
wtdgraph<Item>::~wtdgraph() {
    // just return weights to free store IF NECESSARY
    delete [] weights;
}

// about the assignment operator:
template <class Item>
wtdgraph<Item>& wtdgraph<Item>::operator= (const wtdgraph<Item> &source)
{
	if (this == &source) {
		return *this;
	}

	sizeWeights = source.sizeWeights;
	graph<Item>::operator = (source);
	if (source.weights) {
		weights = new std::map<std::size_t, std::size_t>[source.sizeWeights];
		for (int i = 0; i < sizeWeights; i++) {
			weights[i] = source.weights[i];
		}

	}
	return *this;

    // just return *this if (this == &source)

    // find out (and remember) current allocation before
    // parent resizes; then let parent do its job:
    // graph<Item>::operator=(source);
    
    // allocate new space for weights if allocation changed
    // delete old weights if necessary
    // copy source weights
    
    // return *this at the end
}

template<class Item>
void wtdgraph<Item>::add_edge(std::size_t source, std::size_t target,
                  std::size_t weight) {

	graph<Item>::add_edge(source, target);
	if (this->sizeWeights < this->allocated) {
		this->resize(this->allocated);
	}
	weights[source][target] = weight;
	
	//if size weights is less than allocated 
	//access map for source 
	//update weight

}

template<class Item> 
void wtdgraph<Item>::remove_edge(std::size_t source, std::size_t target) {

	graph<Item>::remove_edge(source, target);
	//assert(weights >= 0); 
	weights[source].erase(target);

}

template<class Item>
std::size_t wtdgraph<Item>::edge_weight(std::size_t source, std::size_t target) const {
	this->graph<Item>::is_edge(source,target);
	assert(this->is_edge(source, target) == true);

	int edgeWeight = weights[source][target];
	return edgeWeight;
}

template<class Item>
void wtdgraph<Item>::resize(std::size_t new_allocation) { 
	graph<Item>::resize(new_allocation);

	if (new_allocation <= sizeWeights)
		return;
	else {
		std::map<std::size_t, std::size_t> *tempWeights = new std::map<std::size_t, std::size_t>[new_allocation];
		for (int i = 0; i < this->sizeWeights; i++) {
			tempWeights[i] = this->weights[i];	
		}

		delete [] weights;
		weights = tempWeights;
		this->sizeWeights = new_allocation;
	}	

	}


}

#endif 
