//import java.io.*;
import java.util.*;
import java.util.NoSuchElementException;
import java.lang.UnsupportedOperationException;
import java.security.InvalidParameterException;
import java.lang.reflect.Array;
import javafx.util.Pair;

@SuppressWarnings("unchecked")		  // warningleri ignore et					  

public class GTUSet<T> implements GTUSetInt<T>, Iterable<T>{

	protected T[] array;
	protected int capasity;
	protected int sizeVal;
	protected int maxsizeVal;

	public GTUSet(){
		sizeVal = 0;
		capasity = 10;
		array = (T[]) new Object[capasity];
	}
     
        public T getData(int i){
            return array[i];
        }

	@Override
	public boolean empty(){ return sizeVal==0; }

	@Override
	public int size(){ return sizeVal; }

	@Override
	public int max_size(){ return maxsizeVal; }

	@Override
	public void clear(){ sizeVal = 0; }

	@Override
	public int count(T val){
		if( search(val) == -1 )
			return 0;
		return 1;
	}

	@Override
	public int erase(T val){
		int ind = search(val);
		if( ind == -1 ){
			System.out.println("The item is not in the container.");
			return -1;
		}
		for(int i=ind; i<sizeVal-1; ++i)
			array[ind] = array[ind+1];
		array[sizeVal] = null;
		--sizeVal;
		return 1;
	}


//***************************************************************

	@Override
	public GTUIteratorInt<T> find(T val){
            int ind = search(val);
            if( ind==-1 )
                return new GTUIterator();
            else
                return new GTUIterator(ind);
	}


	@Override
	public GTUIteratorInt<T> begin(){ return new GTUIterator(); }

        @Override
	public GTUIteratorInt<T> end(){ return new GTUIterator(sizeVal-1); }

        @Override
	public Iterator<T> iterator(){ return new GTUIterator(); }

	public class GTUIterator implements GTUIteratorInt<T>{

		private int ind = 0;

		GTUIterator(int pos){ ind = pos; }

		GTUIterator(){ ind = 0; }

                @Override
		public boolean hasNext(){ return ind < sizeVal; }

                @Override
		public boolean hasPrevious(){ return ind > 0; }

                @Override
		public T next(){
			if( hasNext() )
				return array[ ind++ ];
			throw new NoSuchElementException();
		}

                @Override
		public T previous(){
			if( hasPrevious() )
				return array[ --ind ];
			throw new NoSuchElementException();
		}

                @Override
		public void remove() {
                    throw new UnsupportedOperationException();
		}

	}


	@Override
	//   GTUIterator insert(GTUIterator pos, T val);
	public void insert(T val)throws InvalidParameterException{
		if( search(val) != -1 )
			throw new InvalidParameterException();
		if( sizeVal >= capasity )
			resize();
		array[sizeVal] = val;
		++sizeVal;
		if( maxsizeVal<sizeVal )
			++maxsizeVal;
	}

	@Override
	// For the position where the element can be inserted.
	// Notice that this is just a hint and DOES NOT FORCE the new element 
        // to be inserted at that position within the set container.
	public GTUIteratorInt<T> insert(GTUIteratorInt<T> pos, T val)throws InvalidParameterException{
		if( search(val) != -1 )
                    throw new InvalidParameterException();
		if( sizeVal >= capasity+1 )
                    resize();

		T temp;
		if( pos.hasNext() )
                    temp = pos.next();
		else if( pos.hasPrevious() ){
                    pos.previous();
                    temp = pos.next();
		}
		else
                    temp = null;

		int ind = 0;
		for( ; ind<sizeVal; ++ind )
                    if( array[ind].equals(temp) )
			break;

		++sizeVal;
		for (int i=sizeVal-1; i>ind ; --i )
                    array[i] = array[i-1];
		array[ind] = val;

		if( maxsizeVal<sizeVal )
                    ++maxsizeVal;

		return pos;
	}


// returned set is the intersection of this set and the given set
	public GTUSetInt<T> intersection(GTUSetInt<T> other){

            GTUSet<T> obj = new GTUSet<>();
            GTUSet<T> other1 = (GTUSet<T>) other;
            for(int i=0; i<sizeVal; ++i){
                for(int j=0; j<other1.sizeVal; ++j){
                    if( (array[i]).equals(other1.array[j]) ){
                        obj.insert(other1.array[j]);
                    }
                }
            }
            return obj;
            
        }
        


	@Override
	public String toString(){
		String str = "SET:\n";
		for(int i=0; i<sizeVal; ++i)
			str = str + array[i] + " ";
		str = str + "\n";
		return str;
	}


// *************** PRIVATE METHODS ******************************

	private int search(T val){
            for(int i=0; i<sizeVal; ++i)
            	if( val.equals(array[i]) )
                    return i;
            return -1;
	}

	private void resize(){
            capasity += 10;
            T[] tempArray = (T[]) new Object[capasity];
            for( int i=0; i<sizeVal; ++i )
            	tempArray[i] = array[i];
            array = tempArray;
	}

}