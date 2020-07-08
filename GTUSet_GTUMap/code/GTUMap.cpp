#include "GTUMap.h"

namespace ekardas{

	template<class K, class V>
	GTUMap<K, V>::GTUMap():GTUSet< std::pair<K,V> >(){ /* Empty body */ }

	template<class K, class V>
	V& GTUMap<K, V>::operator[](const K& k){
		cout << "GIRDI\n";
		cout << this->size() << endl;
		for (int i = 0; i < this->size(); ++i){
			cout << "MAP []:" << i << "/" << (  (this->array).get()[i] ).first << "-" << (  (this->array).get()[i] ).second << endl;
			if( (  (this->array).get()[i] ).first == k ){
				return ( ( (this->array).get()[i]).second );
			}
		}
		//return NULL;
	}

}