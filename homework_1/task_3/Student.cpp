#include "Student.hpp"

#include <ostream>

// MARK: Initialize student
// --------------------------------------------------

Student::Student(const std::string& first_name, const std::string& last_name,
                 const std::string& ticket_number,
                 const std::map<std::size_t, double>& subject_average_grades)
    : _first_name(first_name),
      _last_name(last_name),
      _ticket_number(ticket_number),
      _subject_average_grades(subject_average_grades) {}

// MARK: Get student data
// --------------------------------------------------

const std::string& Student::FirstName() const { return _first_name; }

// --------------------------------------------------

const std::string& Student::LastName() const { return _last_name; }

// --------------------------------------------------

const std::string& Student::TicketNumber() const { return _ticket_number; }

// --------------------------------------------------

const std::map<std::size_t, double>& Student::SubjectAverageGrades() const {
  return _subject_average_grades;
}

// MARK: Print student data
// --------------------------------------------------

std::ostream& operator<<(std::ostream& output, const Student& student) {
  output << student.LastName() << ' ' << student.FirstName()
         << ", ticket number " << student.TicketNumber()
         << ", subject average grades:";

  for (const auto& [subject_number, average_grade] :
       student.SubjectAverageGrades()) {
    output << " " << subject_number << '=' << average_grade;
  }

  return output;
}
