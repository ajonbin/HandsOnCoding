#include <iostream>
#include <array>

using namespace std;

template<class T>
void print_array(T& arr){
	for(auto& ele : arr){
		cout << ele << " ";
	}
	cout << endl;
}

class Person{
public:
	Person(){
		age = 0;
		name = "noname";
	}
	Person(int age, string name){
		this->age = age;
		this->name = name;
	}
	// Person(const Person& rs, int i =1){
	// 	cout << "Person's copy constructor" <<endl;
	// 	this->name = rs.name;
	// 	this->age = rs.age;
	// }
	// Person& operator=(const Person& rs){
	// 	cout << "Person's copy assignment" <<endl;
	// 	this->name = rs.name;
	// 	this->age = rs.age;
	// 	return *this;
	// }


public:
	int age;
	string name;
};

std::ostream& operator<<(std::ostream& os, const Person& person){
	cout << person.name << "-" << person.age;
	return os;
}

bool operator==(const Person& lhs, const Person& rhs){
	return ((lhs.age == rhs.age) && (lhs.name == rhs.name));
}

bool operator<(const Person& lhs, const Person& rhs){
	if (lhs.age < rhs.age){
		return true;
	}else if(lhs.age == rhs.age){
		return lhs.name < rhs.name;
	}else{
		return false;
	}
}


template<class T> 
void operate_on_array(T t){
	using ET = typename std::tuple_element<0, decltype(t)>::type;

	if (std::is_same<ET, int>::value){
		cout << "Special operation on int" << endl;
		int copy_ints[std::tuple_size<T>::value] = {0};

	}else{
		cout << "Not int, passing by" << endl;
	}
}

int main(void){
	cout << "!!!!Hello STL Array!!!!" << endl;
	const int array_size = 5;
	{
		cout << endl << "====Init array====" << endl;
		//constuctor for number array
		std::array<int, array_size> numbers1;
		print_array(numbers1);

		std::array<int, array_size> numbers2 = {1,2,3,4,5};
		print_array(numbers2);

		std::array<int, array_size> numbers3{1,};
		print_array(numbers3);

		std::array<int, array_size> numbers4;
		print_array(numbers4);
		numbers4.fill(10);
		print_array(numbers4);

		//constuctor for person array
		std::array<Person, array_size> persons1;
		print_array(persons1);

		std::array<Person, array_size> persons2{Person(11, "John"),Person(22,"Mike")};
		print_array(persons2);

		std::array<Person, array_size> persons3;
		print_array(persons3);
		persons3.fill(Person(11, "Mike"));
		print_array(persons3);
	}

	std::array<Person, array_size> babies{
		Person(1, "baby1"),
		Person(2, "baby2"),
		Person(3, "baby3"),
		Person(4, "baby4"),
		Person(5, "baby5"),		
	};

	{
		//	iterators: begin/end, rbegin/rend, cbegin/cend, crbegin/crend
		//	begin: Returns an iterator pointing to the first element in the array container.
		//	end: Returns an iterator pointing to the past-the-end element in the array container.
		//	rbegin: Returns a reverse iterator pointing to the last element in the array container.
		//	rend: Returns a reverse iterator pointing to the theoretical element preceding the first element in the array (which is considered its reverse end).
		cout << endl << "====iterators====" << endl;
		std::array<Person, array_size> persons = babies;

		for(std::array<Person,array_size>::iterator it = persons.begin(); it != persons.end(); it++){
			cout << *it << endl;
		}

		for(std::array<Person,array_size>::reverse_iterator it = persons.rbegin(); it != persons.rend(); it++){
			cout << *it << endl;
		}
	}
	{
		std::array<Person, array_size> persons = babies;

		//capacity:
		cout << endl << "====capacity====" << endl;

		// size: Returns the number of elements in the array container.
		// max_size: Returns the maximum number of elements that the array container can hold.
		// empty: Returns a bool value indicating whether the array container is empty, i.e. whether its size is 0.
		cout << "size is " << persons.size() << endl;
		cout << "max size is " << persons.max_size() << endl;
		cout << boolalpha << "is empty " << persons.empty() << endl << noboolalpha;
	}

	{
		//access: [], at, data();
		cout << endl << "====access====" << endl;
		std::array<Person, array_size> persons = babies;

		// [n], Returns a reference to the element at position n in the array container.
		// at(n): Returns a reference to the element at position n in the array.
		// front: Returns a reference to the first element in the array container.
		// end: Returns a reference to the last element in the array container
		// data: Returns a pointer to the first element in the array object.

		cout << persons[1] << endl;
		cout << persons.at(1) << endl;

		cout << persons[5] << endl;
		try{
			cout << persons.at(5) << endl;
		}catch(exception& e){
			cout << "caught exception: " << e.what() << endl;
		}

		persons[1].name = "boy2";
		cout << persons.at(1) << endl;

		cout << persons.front() << endl;
		cout << persons.back() << endl;

		Person* p = persons.data();
		for ( int i = 0; i < array_size; i++){
			cout << *(p+i) << endl;
		}
	}

	//modifier:
	// fill: Sets val as the value for all the elements in the array object.
	// swap: Exchanges the content of the array by the content of x, which is another array object of the same type (including the same size).
	{

		cout << endl << "====== modifier ======" << endl;
		std::array<Person, 5> persons1;
		persons1.fill(Person(10, "John"));

		cout << boolalpha << (persons1[0] == persons1[1]) <<endl<<noboolalpha;

		std::array<Person, 5> persons2;
		persons2.fill(Person(11, "Max"));

		cout << "==== before swap =====" << endl;
		print_array(persons1);
		print_array(persons2);

		persons1.swap(persons2);

		cout << "==== after swap =====" << endl;
		print_array(persons1);
		print_array(persons2);
	}

	// Non member functions:
	// std::get(array) Returns a reference to the Ith element of array arr.
	// rational operators, == >= <=: Performs the appropriate comparison operation between the array containers lhs and rhs.
	{

		cout << endl << "==== No member functions ==== " << endl;
		std::array<Person, array_size> persons = babies;

		//std::get
		Person& p = std::get<2>(persons);
		cout << p << endl;

		//rational operators
		Person mike{11, "Ethan"};
		Person john{20, "John"};
		Person sarah{25, "Sarah"};
		std::array<Person, 2> persons1{mike, john};
		std::array<Person, 2> persons2{mike, john};
		std::array<Person, 2> persons3{mike, sarah};

		cout << boolalpha;
		cout << "person1 == person2 is " << (persons1 == persons2) << endl;
		cout << "person1 <= person2 is " << (persons1 <= persons2) << endl;
		cout << "person1 > person2 is " << (persons1 > persons2) << endl;

		cout << "person1 == person3 is " << (persons1 == persons3) << endl;
		cout << "person1 <= person3 is " << (persons1 <= persons3) << endl;
		cout << "person1 > person3 is " << (persons1 > persons3) << endl;
		cout << noboolalpha;

	}

	{
		cout << endl << "==== tuple ==== " << endl;
		std::array<Person,5> person1;
		person1.fill(Person(20, "David"));

		cout << boolalpha;

		using T0 = std::tuple_element<0, decltype(person1)>::type;
		using T1 = std::tuple_element<1,decltype(person1)>::type;

		cout << std::is_same<T0,T1>::value << endl;
		cout << std::is_same<T0,Person>::value << endl;

		//tuple_size
		cout << std::tuple_size<std::array<Person,5>>::value << endl;


		operate_on_array(person1);
		std::array<int,3> numbers{};
		operate_on_array(numbers);

	}

	{
		std::array<int, 0> numbers;
		cout << numbers.size() << endl;
		// cout << numbers[0] << endl;
	}

	cout << endl << "!!!! Goodbye STL Array !!!!" << endl;
}