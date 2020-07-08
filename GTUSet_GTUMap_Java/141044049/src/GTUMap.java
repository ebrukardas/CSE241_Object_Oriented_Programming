//import java.io.*;
//import java.util.*;
import javafx.util.Pair;
import java.lang.reflect.Array;               //??

public class GTUMap<K,V> extends GTUSet< Pair<K,V> >{

	public GTUMap(){
		this.sizeVal = 0;
		this.capasity = 10;
		this.array = (Pair<K,V>[]) new Pair[this.capasity];
        }
    
// If k matches the key of an element in the map, the method returns
// a reference to its mapped value.

	V at( K k ){

		for (int i=0; i<sizeVal ; ++i ) {
			if( k.equals(array[i].getKey()) )
				return array[i].getValue();
		}
		return null;
	}
/*
	public GTUMap<Pair<K,V> > intersection( GTUMap< Pair<K,V> > other){
            GTUMap< Pair<K,V> > obj = new GTUMap<>();
            for(int i=0; i<sizeVal; ++i){
                for(int j=0; j<other.sizeVal; ++j){
                    System.out.print(array[i]);
                    System.out.println("-"+other.array[j]);
                    if( (array[i]).equals(other.array[j]) ){
                        obj.insert(other.array[j]);
                    }
                }
            }
            return obj;
        }
*/        
	@Override
	public GTUIteratorInt<Pair<K,V>> find(Pair<K,V> val){
            int ind = 0;
            for( ; ind<this.sizeVal; ++ind ){
                if( (this.array[ind]).getKey().equals(val.getKey()) ){
                    return new GTUSet.GTUIterator(ind);
                }
            }
            return new GTUSet.GTUIterator(0);
	}

        @Override
	public int erase(Pair<K,V> val){
            int ind = 0;
            for( ; ind<this.sizeVal; ++ind ){
                if( (this.array[ind]).getKey().equals(val.getKey()) ){
                    for(int i=ind; i<sizeVal-1; ++i)
                            array[i] = array[i+1];
                    //array[sizeVal] = null;
                    --sizeVal;
                    return 0;
		}
            }
            System.out.println("The item is not in the container.");
            return -1;
        }

        @Override 
	public String toString(){
		String str = "MAP:\n";
		for (int i=0; i<this.sizeVal; ++i) {
                    str = str +  this.array[i] + " ";
		}
		str = str + "\n";
		return str;

	}

}