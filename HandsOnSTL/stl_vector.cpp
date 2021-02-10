#include <iostream>
#include <vector>

using namespace std;

template<class T>
void print_vector(T& vec){
	if(vec.size() == 0){
		cout << "Empty vecotr";
	}else{
		for(auto& ele: vec){
			cout << ele << " ";
		}
	}
	cout << endl;
}

class Person{
public:
	int age;
	string name;
	Person(){
		age = 0;
		name = "noname";
	}
	Person(int age, string name){
		this->age = age;
		this->name = name;
	}
};

std::ostream& operator<<(std::ostream& os, Person& person){
	cout << person.name << "-" << person.age;
	return os;
}

int main(){
	cout << "Hell STL Vector" << endl;

	{
		//construct
		cout << endl << "==== create init numbers ====" << endl;
		//vector (const allocator_type& alloc = allocator_type());
		std::vector<int> numbers1;
		print_vector(numbers1);

		//vector (size_type n);
		std::vector<int> numbers2(5);
		print_vector(numbers2);

		//vector (size_type n, const value_type& val,const allocator_type& alloc = allocator_type());
		std::vector<int> numbers3(5,10);
		print_vector(numbers3);

		//vector (initializer_list<value_type> il,const allocator_type& alloc = allocator_type());
		std::vector<int> numbers4({1,2,3,4,5});
		print_vector(numbers4);

		//vector (const vector& x);
		std::vector<int> numbers5(numbers4);
		print_vector(numbers5);

		//template <class InputIterator>vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		std::vector<int> numbers6{numbers4.begin()+1,numbers4.end()-1};
		print_vector(numbers6);

		//vector& operator= (const vector& x);
		std::vector<int> numbers7 = numbers4;
		print_vector(numbers7);
	}

	{
		cout << endl << "==== creat init persons ====" << endl;

		//vector (const allocator_type& alloc = allocator_type());
		std::vector<Person> persons1;
		print_vector(persons1);

		//vector (size_type n);
		std::vector<Person> persons2(5);
		print_vector(persons2);

		//vector (size_type n, const value_type& val,const allocator_type& alloc = allocator_type());
		std::vector<Person> persons3(5,Person(10, "John"));
		print_vector(persons3);

		//vector (initializer_list<value_type> il,const allocator_type& alloc = allocator_type());
		std::vector<Person> persons4({Person(10, "John"), Person(20, "Rose"), Person(30,"Jacob")});
		print_vector(persons4);

		//vector (const vector& x);
		std::vector<Person> persons5(persons4);
		print_vector(persons5);

		//template <class InputIterator>vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		std::vector<Person> persons6{persons4.begin()+1,persons4.end()-1};
		print_vector(persons6);

		//vector& operator= (const vector& x);
		std::vector<Person> persons7 = persons4;
		print_vector(persons7);
	}

	std::vector<Person> babies{
		Person(1, "baby1"),
		Person(2, "baby2"),
		Person(3, "baby3"),
		Person(4, "baby4"),
		Person(5, "baby5"),
	};

	
	{
		//iterators: begin/end, rbegin/rend, cbegin/cend, crbegin/crend
		//begin: Returns an iterator pointing to the first element in the array container.
		//end: Returns an iterator pointing to the past-the-end element in the array container.
		//rbegin: Returns a reverse iterator pointing to the last element in the array container.
		//rend: Returns a reverse iterator pointing to the theoretical element preceding the first element in the array (which is considered its reverse end).
		cout << endl << "==== iterators ====" << endl;

		std::vector<Person> persons = babies;

		for(std::vector<Person>::iterator it = persons.begin(); it != persons.end(); it++){
			cout << *it << " ";
		}
		cout << endl;
		for(std::vector<Person>::reverse_iterator it = persons.rbegin(); it != persons.rend(); it++){
			cout << *it << " ";
		}
		cout << endl;
	}

	{
		//capacity
		//size: Returns the number of elements in the vector.
		//max_size: Returns the maximum number of elements that the vector can hold, limited system or library implementation.
		//capacity: Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
		//empty: Returns whether the vector is empty (i.e. whether its size is 0).
		//reserve: Requests that the vector capacity be at least enough to contain n elements.
		//shrink_to_fit: Requests the container to reduce its capacity to fit its size.
		//resize: Resizes the container so that it contains n elements.

		cout << endl << "==== capacity ====" << endl;
		std::vector<Person> persons = babies;

		//size_type size() const noexcept;
		//size_type max_size() const noexcept;
		//size_type capacity() const noexcept;
		//bool empty() const noexcept;
		cout << persons.size() << endl;
		cout << persons.capacity() << endl;
		cout << persons.max_size() << endl;
		cout << boolalpha << persons.empty() << endl;


		persons.push_back(Person(6,"baby6"));

		cout << persons.size() << endl;
		cout << persons.capacity() << endl;
		cout << persons.max_size() << endl;

		persons.push_back(Person(6,"baby6"));
		persons.push_back(Person(6,"baby6"));
		persons.push_back(Person(6,"baby6"));
		persons.push_back(Person(6,"baby6"));
		persons.push_back(Person(6,"baby6"));
		cout << persons.size() << endl;
		cout << persons.capacity() << endl;
		cout << persons.max_size() << endl;

		persons.erase(--persons.end());
		persons.erase(--persons.end());
		persons.erase(--persons.end());
		persons.erase(--persons.end());
		cout << persons.size() << endl;
		cout << persons.capacity() << endl;
		cout << persons.max_size() << endl;

		//void reserve (size_type n);
		persons.reserve(30);
		cout << persons.size() << endl;
		cout << persons.capacity() << endl;

		persons.reserve(20);
		cout << persons.size() << endl;
		cout << persons.capacity() << endl;

		//shrink_to_fit
		//void shrink_to_fit();

		persons.shrink_to_fit();
		cout << persons.size() << endl;
		cout << persons.capacity() << endl;

		//resize
		//void resize (size_type n);
		persons.resize(10);
		cout << persons.size() << endl;
		cout << persons.capacity() << endl;
		print_vector(persons);

		//void resize (size_type n, const value_type& val);
		persons.resize(20, Person(20, "Maisy"));
		cout << persons.size() << endl;
		cout << persons.capacity() << endl;
		print_vector(persons);

		persons.resize(9);
		cout << persons.size() << endl;
		cout << persons.capacity() << endl;
		print_vector(persons);

	}

	{
		//access: [], at, front, back, data
		cout << endl << "====access====" << endl;
		std::vector<Person> persons = babies;

		// [n], Returns a reference to the element at position n in the array container.
		// at(n): Returns a reference to the element at position n in the array.
		// front: Returns a reference to the first element in the array container.
		// end: Returns a reference to the last element in the array container
		// data: Returns a pointer to the first element in the array object.

		//reference operator[] (size_type n);
		cout << persons[1] << endl;

		//reference at (size_type n);
		cout << persons.at(1) << endl;

		cout << persons[5] << endl;
		try{
			cout << persons.at(5) << endl;
		}catch(exception& e){
			cout << "caught exception: " << e.what() << endl;
		}

		persons[1].name = "boy2";
		cout << persons.at(1) << endl;

		//reference front();
		cout << persons.front() << endl;
		//reference back();
		cout << persons.back() << endl;

		//value_type* data() noexcept;
		Person* p = persons.data();
		for ( int i = 0; i < persons.size(); i++){
			(*(p+i)).age++;
			cout << *(p+i) << endl;
		}
	}

	{
		//modifiers
		//assign: Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly. 
		//push_back:Adds a new element at the end of the vector, after its current last element. 
		//pop_back: Removes the last element in the vector, effectively reducing the container size by one.
		//insert: inserting new elements before the element at the specified position
		//erase: Removes from the vector either a single element (position) or a range of elements ([first,last)).
		//swap: Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
		//clear: Removes all elements from the vector (which are destroyed), leaving the container with a size of 0
		//emplace: The container is extended by inserting a new element at position. This new element is constructed in place using args as the arguments for its construction.
		//emplace_back: Inserts a new element at the end of the vector, right after its current last element. This new element is constructed in place using args as the arguments for its constructor.
		cout << endl << "==== modifiers ====" << endl;

		//void assign (size_type n, const value_type& val);
		std::vector<Person> persons = babies;
		persons.assign(3,Person(15, "boy"));
		print_vector(persons);

		//template<class InputIterator> void assign (InputIterator first, InputIterator last);
		//[first,last)
		persons = babies;
		persons.assign(babies.begin(), babies.begin()+2);
		print_vector(persons);

		//void assign (initializer_list<value_type> il);
		persons = babies;
		persons.assign({Person(12,"girl12"),Person(13, "girl13")});
		print_vector(persons);

		//void push_back (const value_type& val);
		persons = babies;
		persons.push_back(Person(15, "boy15"));
		print_vector(persons);

		//void pop_back();
		persons = babies;
		persons.pop_back();
		print_vector(persons);

		//iterator insert (const_iterator position, const value_type& val);
		persons = babies;
		std::vector<Person>::iterator it = persons.insert(persons.begin(), Person(0,"baby0"));
		cout << *it << endl;
		print_vector(persons);

		//iterator insert (const_iterator position, size_type n, const value_type& val);
		persons = babies;
		it = persons.insert(persons.begin()+1, 3, Person(0,"baby0"));
		cout << *it << endl;
		print_vector(persons);

		//template <class InputIterator> iterator insert (const_iterator position, InputIterator first, InputIterator last);
		persons = babies;
		it = persons.insert(persons.begin()+1, babies.begin(),babies.end()-1);
		cout << *it << endl;
		print_vector(persons);

		//iterator insert (const_iterator position, initializer_list<value_type> il)
		persons = babies;
		it = persons.insert(persons.end(), {Person(6,"baby6")});
		cout << *it << endl;
		print_vector(persons);

		//iterator erase (const_iterator position);
		persons = babies;
		it = persons.erase(persons.begin());
		cout << *it << endl;
		print_vector(persons);

		//iterator erase (const_iterator first, const_iterator last);
		persons = babies;
		it = persons.erase(persons.begin(), persons.end());
		cout << "it is end(): " << (it == persons.end()) << endl;
		print_vector(persons);

		//void swap (vector& x);
		std::vector<Person> persons1 = babies;
		std::vector<Person> persons2 = {Person(15, "boy")};
		persons2.swap(persons1);
		print_vector(persons1);
		print_vector(persons2);

		//void clear();
		persons = babies;
		persons.clear();
		print_vector(persons);

		//template <class... Args> iterator emplace (const_iterator position, Args&&... args);
		//template <class... Args> void emplace_back (Args&&... args);
		persons = babies;
		it = persons.emplace(persons.begin(), 0, "baby0");
		persons.emplace_back(6, "baby6");
		cout << *it << endl;
		print_vector(persons);
	}

	{
		//allocator
		//get_allocator: Returns a copy of the allocator object associated with the vector.
		cout << endl << "==== allocator ====" << endl;
		//allocator_type get_allocator() 

		std::vector<Person> persons;
		Person* p = nullptr;

		p = persons.get_allocator().allocate(3);
		for (int i = 0; i < 3; i++){
			persons.get_allocator().construct(&p[i],i,"baby");
		}
		for(int i = 0; i < 3; i++){
			cout << p[i] << " ";
		}
		cout << endl;
		print_vector(persons);

		for(int i = 0; i < 3; i++){
			persons.get_allocator().destroy(&p[i]);
		}
		persons.get_allocator().deallocate(p,3);
	}
	cout << endl << "Bye STL Vector" << endl;
}