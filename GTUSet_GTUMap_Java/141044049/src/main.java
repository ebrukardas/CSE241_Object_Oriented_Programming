/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import javafx.util.Pair;

public class main{

	public static void main(String[] args) {
			//intersectionTest();
			//testSet();
			testMap();
		}

		public static void intersectionTest(){

			GTUSet<Integer> obj1 = new GTUSet<>();
			GTUSet<Integer> obj2 = new GTUSet<>();
			
			for(int i=0; i<5; ++i){
				obj1.insert(i);
			}

			for(int j=5; j<10; ++j){
				obj1.insert(j);
				obj2.insert(j);
			}

			obj2.insert(10);
			System.out.println( obj1 );
			System.out.println(obj2);
			System.out.println("MAIN intersection SET:\n"+ obj1.intersection(obj2) );

			GTUMap<Integer, String> obj3 = new GTUMap<>();
			GTUMap<Integer, String> obj4 = new GTUMap<>();
			
			for(int i=0; i<5; ++i){
				obj3.insert(new Pair<>(i, "eb"));
			}

			for(int j=5; j<10; ++j){
				obj3.insert(new Pair<>(j, "ru"));
				obj4.insert(new Pair<>(j, "ru"));
			}
			obj4.insert(new Pair<>(10, "ru"));

			System.out.println(obj3);
			System.out.println(obj4);
			System.out.println("MAIN intersection MAP:\n"+ obj3.intersection(obj4) );			
			
			
		}
		
		
		
		public static void testMap(){
		
			GTUMap< Integer, String > obj = new GTUMap<>();
			System.out.println("empty:" + obj.empty() );
			System.out.println("size:" + obj.size() );

			for ( int i=2; i<10 ; ++i )
				obj.insert(new Pair<>(i,"ebru"));

			System.out.println(obj);
			
			obj.erase(new Pair<>(5,"ebru"));
			System.out.println(obj);
/*
			obj.erase(new Pair<>(12,"ebru"));
			System.out.println(obj);
*/
			System.out.print("size:" + obj.size() );
			System.out.println(" maxsize:" + obj.max_size() );

			System.out.println("Count will be printed along map size:" + obj.size() );
			for ( int i=0; i<obj.size() ; ++i )
				System.out.println(i + " count:" + obj.count(new Pair<>(i,"ebru")) );


			try {

				System.out.println("Find check with iterator");
				GTUIteratorInt< Pair<Integer,String> > it = obj.find(new Pair<>(4,"ebru"));
				while( it.hasNext() )
					System.out.println("next-> " + it.next() );
					
				System.out.println("---------------");

				it = obj.end();
				while( it.hasPrevious() )
					System.out.println("Previous-> " + it.previous() );

				it.next();
				it.next();

				//iterator'ün en son kaldığı yerden ekleme yapıldı
				it = obj.insert(it, new Pair<>(567,"kardas"));
				System.out.println("\n567-ebru in inserted, iterator returned");
				System.out.println( "returned iter->"+it.next() );
				System.out.println(obj);

				System.out.println("Enchance for:");
				for(Pair<Integer,String> str : obj)
					System.out.println(str);


			} catch (Exception e) {
				System.out.println("Exception caught: " + e);
			}

			System.out.println( obj.at(567) );
			
			obj.clear();
			System.out.println("Object cleared");
			System.out.println(obj);
			System.out.println("empty:" + obj.empty() );
			
		}
		
	public static void testSet(){

		GTUSet<Integer> obj = new GTUSet<>();

		System.out.println("empty:" + obj.empty() );
		System.out.println("size:" + obj.size() );
		System.out.println(obj);

		for ( int i=2; i<10 ; ++i )
			obj.insert(i);

		obj.erase(8);
		System.out.println(obj);
/*
				obj.erase(10);
		System.out.println(obj);
*/
		System.out.print("size:" + obj.size() );
		System.out.println(" maxsize:" + obj.max_size() );

		for ( int i=0; i<obj.size() ; ++i )
			System.out.println(i + " count:" + obj.count(i) );



		try {


			GTUIteratorInt<Integer> it = obj.find(2);
			while( it.hasNext() )
				System.out.println("next-> " + it.next() );
			
			System.out.println("---------------");

			it = obj.end();
			while( it.hasPrevious() )
				System.out.println("Previous-> " + it.previous() );


			it = obj.insert(it, 567);
			System.out.println( "returned iter->"+it.next() );
			System.out.println(obj);


			System.out.println("Enchance for:");
			for(Integer str : obj)
				System.out.println(str);


		} catch (Exception e) {
			System.out.println("Exception caught: " + e);
		}

		obj.clear();
		System.out.println(obj);
		System.out.println("empty:" + obj.empty() );



	}


}