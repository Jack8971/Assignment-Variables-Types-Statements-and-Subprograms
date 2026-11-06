// [EXTERNAL-MODIFIED] All the code was written by me but I had copilot to auto complete and add proper concise comments to the code
#ifndef PERSON_H
#define PERSON_H

#include <array>
#include <string>

#include "Date.h"

// Gender choices. 'enum class' is strongly typed: values never convert
// silently to int and must be written Gender::Female.
enum class Gender { Female, Male, NonBinary, PreferNotToSay };

// All choices in one fixed-size array, so menus can loop over them.
inline constexpr std::array<Gender, 4> kAllGenders = {
    Gender::Female, Gender::Male, Gender::NonBinary, Gender::PreferNotToSay};

// Display text for a Gender (e.g. Gender::NonBinary -> "Non-binary").
std::string toString(Gender gender);

// Abstract base class: holds what every person has in common.
// It cannot be instantiated because describe() is pure virtual.
class Person {
public:
    Person(std::string firstName, std::string lastName,
           Date dateOfBirth, Gender gender);

    // Virtual destructor: required so deleting a pointer to a derived class calls the derived destructor.
    virtual ~Person() = default;

    // Getters return const references: no copy, caller cannot modify.
    const std::string& firstName() const;
    const std::string& lastName() const;
    const Date& dateOfBirth() const;
    Gender gender() const;
    std::string fullName() const;

    // Setters (used by the modify operation). Validation is done by
    // InputValidation before these are called.
    void setFirstName(std::string firstName);
    void setLastName(std::string lastName);
    void setDateOfBirth(Date dateOfBirth);
    void setGender(Gender gender);

    // Pure virtual: every derived class MUST override it.
    // Which version runs is decided at run time (dynamic binding).
    virtual std::string describe() const = 0;

private:
    std::string firstName_;
    std::string lastName_;
    Date dateOfBirth_;
    Gender gender_;
};

#endif // PERSON_H