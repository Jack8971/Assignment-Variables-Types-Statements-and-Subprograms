
"""
person.py

This file defines the Person base class for the SAIT Enrollment
Management System.

It contains:
- Gender enum with all available gender options.
- Person dataclass with personal information.
- Getter and setter methods for personal information.
- A method to return the person's full name.
"""

from dataclasses import dataclass
from datetime import date
from enum import Enum


# Defines the gender choices available in the system.
class Gender(str, Enum):
    FEMALE = "Female"
    MALE = "Male"
    NON_BINARY = "Non-binary"
    PREFER_NOT_TO_SAY = "Prefer not to say"


# Stores personal information shared by all people.
@dataclass
class Person:
    first_name: str
    last_name: str
    date_of_birth: date
    gender: Gender

    # Returns the person's first name.
    def get_first_name(self) -> str:
        return self.first_name

    # Returns the person's last name.
    def get_last_name(self) -> str:
        return self.last_name

    # Returns the person's date of birth.
    def get_date_of_birth(self) -> date:
        return self.date_of_birth

    # Returns the person's gender.
    def get_gender(self) -> Gender:
        return self.gender

    # Updates the person's first name.
    def set_first_name(self, first_name: str) -> None:
        self.first_name = first_name

    # Updates the person's last name.
    def set_last_name(self, last_name: str) -> None:
        self.last_name = last_name

    # Updates the person's date of birth.
    def set_date_of_birth(self, date_of_birth: date) -> None:
        self.date_of_birth = date_of_birth

    # Updates the person's gender.
    def set_gender(self, gender: Gender) -> None:
        self.gender = gender

    # Returns the person's complete name.
    def full_name(self) -> str:
        return f"{self.first_name} {self.last_name}"
