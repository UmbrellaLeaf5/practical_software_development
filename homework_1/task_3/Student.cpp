#include "Student.hpp"

#include <ostream>
#include <stdexcept>

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

// MARK: Manage student subjects
// --------------------------------------------------

bool Student::HasSubject(std::size_t subject_number) const {
  return _subject_average_grades.contains(subject_number);
}

// --------------------------------------------------

void Student::AddSubject(std::size_t subject_number, double average_grade) {
  if (!_subject_average_grades.emplace(subject_number, average_grade).second)
    throw std::invalid_argument(
        "[Student::AddSubject] Duplicate subject number");
}

// --------------------------------------------------

void Student::RemoveSubject(std::size_t subject_number) {
  if (_subject_average_grades.erase(subject_number) == 0)
    throw std::invalid_argument("[Student::RemoveSubject] Subject not found");
}

// MARK: Print student data
// --------------------------------------------------

std::ostream& operator<<(std::ostream& output, const Student& student) {
  output << student.LastName() << ' ' << student.FirstName()
         << ", ticket number " << student.TicketNumber();

  if (student.SubjectAverageGrades().empty()) {
    output << ", no subject attachments";

    return output;
  }

  output << ", subject average grades:";

  for (const auto& [subject_number, average_grade] :
       student.SubjectAverageGrades())
    output << " " << subject_number << '=' << average_grade;

  return output;
}
