//Pulled from person.h thats a skeleton for the person class
#include "Person.h"

#include <utility>

// [EXTERNAL-MODIFIED] Majority of code written by Kunj apart from the comments or some code completion by co pilot.
//To string function for the gender enum class. This is used to display the gender in a human-readable format.
std::string toString(Gender gender) {
    switch (gender) {
        case Gender::Female:         return "Female";
        case Gender::Male:           return "Male";
        case Gender::NonBinary:      return "Non-binary";
        case Gender::PreferNotToSay: return "Prefer not to say";
    }
    return "Unknown"; // Just in case a new gender is added to the enum class and not handled here.
}

// Parameters taken by value, then moved into the members:
// avoids an extra copy when the caller passes a temporary.
Person::Person(std::string firstName, std::string lastName,
               Date dateOfBirth, Gender gender)
    : firstName_(std::move(firstName)),
      lastName_(std::move(lastName)),
      dateOfBirth_(dateOfBirth),
      gender_(gender) {}


//All the getters made it short and still undertandable. Used & to return a reference to avoid unnecessary copying. Const avoids modifications.
const std::string& Person::firstName() const { return firstName_; }
const std::string& Person::lastName() const { return lastName_; }
const Date& Person::dateOfBirth() const { return dateOfBirth_; }
Gender Person::gender() const { return gender_; }

std::string Person::fullName() const { return firstName_ + " " + lastName_; }

//All setters 
void Person::setFirstName(std::string firstName) { firstName_ = std::move(firstName); }
void Person::setLastName(std::string lastName) { lastName_ = std::move(lastName); }
void Person::setDateOfBirth(Date dateOfBirth) { dateOfBirth_ = dateOfBirth; }
void Person::setGender(Gender gender) { gender_ = gender; }