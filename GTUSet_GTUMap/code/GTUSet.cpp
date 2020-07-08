#include "GTUSet.h"
#include "GTUSetBase.h"


namespace ekardas{

	template<class T>
	GTUSet<T>::GTUSet(){
		capa = 10;
		(this->sizeVar) = 0;
		maxSizeVar = -1;
		std::shared_ptr<T> tempptr(new T[10], default_delete<T[]>() );
		(this->array) = tempptr;
		tempptr = nullptr;
	}


	template<class T>
	bool GTUSet<T>::empty()const{ return ((this->sizeVar)==0); }

	template<class T>
	int GTUSet<T>::size()const{ return (this->sizeVar); }

	template<class T>
	int GTUSet<T>::max_size()const{ return maxSizeVar; }

	template<class T>
	void GTUSet<T>::clear(){ (this->sizeVar) = 0; }

	template<class T>
	int GTUSet<T>::count(const T& value)const{
		if( search(value) != -1 )
			return 1;
		return 0;
	}

	template<class T>
	bool GTUSet<T>::insert(const T& item)throw(std::invalid_argument){
		if( search(item) != -1 ){								//	if the item is found, throw exception
			throw std::invalid_argument("Item already exist in the container.\n");
		}else{
			if( (this->sizeVar) >= capa )
				resize();
			((this->array).get()[this->sizeVar]) = item;
			++(this->sizeVar);
			if( maxSizeVar<(this->sizeVar) )
				maxSizeVar = (this->sizeVar);
			return true;
		}
	}

	template<class T>
	int GTUSet<T>::erase(const T& item){

		int pos = search(item);
		if(pos==-1){
			cerr << "The item is not in the container.\n";
			return 0;
		}
		for(int i=pos; i<(this->sizeVar)-1; ++i){
			(this->array).get()[i] = (this->array).get()[(i+1)];
		}
		--(this->sizeVar);
		return 1;
	}


//	*************************************		PRIVATE FUNCTIONS
	template<class T>
	int GTUSet<T>::search(const T& value)const{
		for(int i=0; i<(this->sizeVar); ++i){
			if( ((this->array).get()[i]) == value ){
				return i;
			}
		}
		return -1;
	}


	template<class T>
	void GTUSet<T>::resize(){
		capa += 10;
		std::shared_ptr<T> tempptr(new T[capa+10], default_delete<T[]>() );
		for (int i = 0; i < (this->sizeVar); ++i){
			tempptr.get()[i] = (this->array).get()[i];
		}
		(this->array) = tempptr;
		tempptr = nullptr;
	}

//	*************************************			SETTERS

	//	getSize is inline function in header file
	template<class T>
	void GTUSet<T>::setSize(int value)throw(myException){
		if(value<0)
			throw myException("Size cannot be negative!\n");
		(this->sizeVar) = value;
		setMaxSize((this->sizeVar));

	}

	//	getMaxSize is inline function in header file
	template<class T>
	void GTUSet<T>::setMaxSize(int value)throw(myException){
		if(value<0)
			throw myException("Max size cannot be negative!\n");
		if(maxSizeVar<value)
			maxSizeVar = value;
	}
	
	//	getCapa is inline function in header file
	template<class T>
	void GTUSet<T>::setCapa(int value)throw(myException){
		if(value<0)
			throw myException("Capasity cannot be negative!\n");
		capa = value;
	}

}
