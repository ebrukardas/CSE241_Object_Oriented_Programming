#ifndef GTUSET_H
#define GTUSET_H

#include <iostream>
#include <cstdlib>
#include <memory>
#include "myException.h"

using namespace std;
#include "GTUSetBase.h"

namespace ekardas{

	template<class T>
	class GTUSet : public GTUSetBase<T>{

		public:

			// CONSTRUCTOR
			GTUSet<T>();

			bool empty()const;
			int size()const;
			int max_size()const;
			void clear();
			int count(const T& value)const;
			bool insert(const T& item)throw(std::invalid_argument);
			int erase(const T& item);

		protected:

			inline int getSize()const{ return this->sizeVar; }
			void setSize(int value)throw(myException);

			int maxSizeVar;
			inline int getMaxSize()const{ return maxSizeVar; }
			void setMaxSize(int value)throw(myException);

			int capa;
			inline int getCapa()const{ return capa; }
			void setCapa(int value)throw(myException);

			int search(const T& value)const;

			void resize();

	};

}

#endif //GTUSET_H
