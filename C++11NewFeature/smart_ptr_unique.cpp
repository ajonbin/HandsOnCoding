#include <iostream>
#include <memory>

using namespace std;

class Person{
public:
	std::string name;
public:
	Person(){
		cout << "default constructor " << endl;
		this->name = "noname";
	}

	Person(std::string name){
		cout << "constructor " << name << endl;
		this->name = name;
	}

	~Person(){
		cout << "~destructor " << name << endl;
	}

	void say_hello(){
		cout << "hello from " << name << endl;
	}
};

class Person_Deleter {  
public:
	Person_Deleter(){
		cout << "Person_Deleter created" << endl;
	}
	void operator()(Person* p) {
		cout << "Person_Deleter delete " << p->name << endl;
		delete p;
	}
};


int main(){
	cout << ">>>>>>>> Hello unique_ptr " << endl;
	{
		//construct and initialize
		cout << endl << ">>>>>> construct and initialize (build-in type)" << endl;
		std::unique_ptr<int> pi1(new int(33));
		std::unique_ptr<int> pi2;
		pi2.reset(new int(34));

		cout << "pi1 = " << *pi1 << endl;
		cout << "pi2 = " << *pi2 << endl;

		cout << "<<<<<< construct and initialize (build-in type) end" << endl;
	}
	{
		cout << endl << ">>>>>> construct and initialize (self-defined)" << endl;

		std::unique_ptr<Person> p_mike(new Person("Mike"));
		p_mike->say_hello();

		std::unique_ptr<Person> p_sb;
		p_sb.reset(new Person("John"));
		p_sb->say_hello();
		(*p_sb).say_hello();
		p_sb.reset(new Person("Sarah"));
		p_sb->say_hello();
		(*p_sb).say_hello();

		cout << "<<<<<< construct and initialize (self-defined) end" << endl;

	}
	{	
		//get: return the raw pointer stored
		cout << endl << ">>>>>> get() " << endl;
		std::unique_ptr<Person> p_sb(new Person("Mike"));
		Person* p_mike = p_sb.get();
		p_mike->say_hello();
		cout << "<<<<<< get() end" << endl;
	}
	{
		//copy vs move
		cout << endl << ">>>>>>>> copy vs move" << endl;
		std::unique_ptr<Person> p_mike(new Person("Mike"));

		//unique_ptr can't be copied
		//error: call to implicitly-deleted copy constructor of 'std::unique_ptr<Person>'
		//std::unique_ptr<Person> p_sb(p_mike);
		std::unique_ptr<Person> p_sb(std::move(p_mike));
		p_sb->say_hello();
		cout << boolalpha << "p_mike stores nullptr: " << (p_mike.get() == nullptr) << endl;
		cout << boolalpha << "p_mike is not empty: " << static_cast<bool>(p_mike) << endl;

		cout << boolalpha << "p_sb stores nullptr: " << (p_sb.get() == nullptr) << endl;
		cout << boolalpha << "p_sb is not empty: " << static_cast<bool>(p_sb) << endl;

		cout << "<<<<<<< copy vs move end" << endl;
	}
	
	{
		//custom deleter: lamda
		cout << endl << ">>>>>>>> custom deleter " << endl;
		auto person_deleter = [](Person* p){
			cout << "person_deleter deletes " << p->name << endl;
			delete p;
		};
		std::unique_ptr<Person, decltype(person_deleter)> p_jerry(new Person("Jerry"), person_deleter);
		p_jerry->say_hello();

		cout << "<<<<<<<< custom deleter end" << endl;
	}

	{
		//custom deleter: callable
		cout << endl << ">>>>>>>> custom deleter with callalbe object " << endl;

		std::unique_ptr<Person, Person_Deleter> p_tom(new Person("Tom"));
		std::unique_ptr<Person, Person_Deleter> p_snow(new Person("Snow"), Person_Deleter());
		std::unique_ptr<Person, Person_Deleter> p_tiffany(new Person("Tiffany"), p_snow.get_deleter());
		cout << "<<<<<<<< custom deleter with callalbe object end " << endl;
	}
	{
		//release: Releases ownership of its stored pointer, by returning its value and replacing it with a null pointer.
		cout << endl << ">>>>>>>> Release() " << endl;
		Person_Deleter deleter;
		std::unique_ptr<Person, Person_Deleter> p_mike(new Person("Mike"), deleter);
		Person* p = p_mike.release();
		if(!p_mike){
			cout << "p_mike is empty" << endl;
		}
		p->say_hello();
		p_mike.get_deleter()(p);
		cout << "<<<<<<<< Release end " << endl;

	}
	{
		//swap: exchange pointer and deleter, type must be same
		cout << endl << ">>>>>>>> swap()" << endl;

		std::unique_ptr<Person, Person_Deleter> p_mike(new Person("Mike"));
		std::unique_ptr<Person, Person_Deleter> p_sarah(new Person("Sarah"));

		p_mike.swap(p_sarah);

		p_mike->say_hello();
		p_sarah->say_hello();
	
		cout << "<<<<<<<< swap() end " << endl;
	}
	{
		//operator=()
		cout << endl << ">>>>>> operator=() " << endl;

		std::unique_ptr<Person, Person_Deleter> p_mike(new Person("Mike"));
		std::unique_ptr<Person, Person_Deleter> p_sarah(new Person("Sarah"));

		p_mike = std::move(p_sarah);

		cout << "<<<<<< operator=()  end" << endl;

	}
	{
		//array
		cout << endl << ">>>>>> T[] " << endl;
		//custom deleter
		auto person_deleter = [](Person p[]){
			cout << "person_deleter delete " << p[0].name << endl;
			delete[] p;
		};

		std::unique_ptr<Person[], decltype(person_deleter)> 
			p_persons(new Person[]{Person("Mike"),Person("Tiffany")},person_deleter);
		p_persons[0].say_hello();
		p_persons[1].say_hello();

		cout << "<<<<<< T[]  end" << endl;
	}

	cout << "<<<<<<<< Bye unique_ptr " << endl;
	
}