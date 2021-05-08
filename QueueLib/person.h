class Person {
private:
	std::string name;
public:
	// when class has constructor with parameters, it does not create a default constructor
	// thus it is needed to define one
	Person() = default;
	Person (std::string t_name);
	std::string getName() const;
	friend std::ostream& operator <<(std::ostream& output, Person& o);
};

Person::Person(std::string t_name) {
	name = t_name;
};

std::string Person::getName() const{
	return name;
};

std::ostream& operator <<(std::ostream& output, Person& o) {
	/* Returns stream with person's name */
	output << o.getName();
	return output;
}