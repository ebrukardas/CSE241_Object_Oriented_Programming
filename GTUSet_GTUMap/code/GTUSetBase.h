#ifndef GTUSETBASE_H
#define GTUSETBASE_H

#include <iostream>
#include <memory>
using namespace std;

namespace ekardas{

	template<class T>
	class GTUSetBase{

// OTHER FUNCTION PROTOTYPES ARE DOWN THERE.

		public:

			class GTUIterator{
				// written functions in header files because all of these are short functions.
				public:
					GTUIterator(T* ptr):pointer(ptr){/* EMPTY BODY */}

					inline T& operator*(){ return *pointer; }

					inline T* operator->(){ return pointer; }

					inline bool operator==( const GTUIterator& other ){ return ( pointer == other.pointer ); }

					inline bool operator!=( const GTUIterator& other ){ return ( pointer != (other.pointer) ); }

					GTUIterator operator++(){
						GTUIterator i = *this;
						++pointer;
						return i;
					}

					GTUIterator operator++(int){
						++pointer;
						return *this;
					}

					GTUIterator operator--(){
						GTUIterator i = *this;
						--pointer;
						return i;						
					}
					GTUIterator operator--(int){
						--pointer;
						return *this;
					}

					GTUIterator& operator=(const GTUIterator& other){
						if( this!= &other ){
							pointer = other.pointer;
						}
						return *this;
					}

				private:
					T* pointer;

			};


			virtual bool empty()const = 0 ;
			virtual int size()const = 0 ;
			virtual int max_size()const = 0 ;
			virtual void clear() = 0 ;

			int count(const T& value)const;
			int erase(const T& item);
			bool insert(const T& item)throw(std::invalid_argument);

			inline GTUIterator begin(){
				return GTUIterator( array.get() );
			}

			inline GTUIterator end(){
				return GTUIterator( &(array.get()[sizeVar]) );
			}

			GTUIterator find(const T& value)const{
				for (int i = 0; i < sizeVar; ++i)
					if( array.get()[i] == value )
						return GTUIterator( &(array.get()[i]) );
				return nullptr;
			}

		protected:
			shared_ptr<T> array;
			int sizeVar;

	};
}

#endif //GTUSETBASE_H
