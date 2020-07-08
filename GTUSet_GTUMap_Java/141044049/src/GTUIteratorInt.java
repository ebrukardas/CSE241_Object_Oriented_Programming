import java.util.Iterator;

public interface GTUIteratorInt<T> extends Iterator<T>{
/*
    @Override
    public T next();
    @Override
    public boolean hasNext();
    @Override
    void remove();
*/
    public boolean hasPrevious();
    public T previous();
}