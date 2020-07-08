#ifndef GTUMAP_H
#define GTUMAP_H

#include "GTUSet.h"
#include <iostream>

//#include "GTUSet.cpp"

namespace ekardas{

	template<class K, class V>
	class GTUMap : public GTUSet< std::pair<K,V> >{

		public:

			GTUMap<K, V>();

			V& operator[](const K& k);

	};

}

#endif //GTUMAP_H