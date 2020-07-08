/**
 * Created by ebru on 15.12.2017.
 */
import java.util.*;
import java.security.InvalidParameterException;
//import javafx.util.Pair;

public interface GTUSetInt<T>{

	public boolean empty();
	public int size();
	public int max_size();
	public void clear();
	public int count(T val);
	public int erase(T val);

	public GTUIteratorInt<T> insert(GTUIteratorInt<T> pos, T val)throws InvalidParameterException;
	public void insert(T val)throws InvalidParameterException;

	public GTUIteratorInt<T> find(T val);

	public Iterator<T> begin();
	public Iterator<T> end();


// returned set is the intersection of this set and the given set
	public GTUSetInt<T> intersection(GTUSetInt<T> other);


}