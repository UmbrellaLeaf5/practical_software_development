#include "Manager.hpp"

#include <algorithm>
#include <ostream>
#include <stdexcept>

// MARK: Initialize manager
// --------------------------------------------------

Manager::Manager(std::ostream& output) : _output(output) {}

// MARK: Manage students
// --------------------------------------------------

void Manager::Add(const Student& student) {
  const auto duplicate = std::ranges::find(
      _students, student.TicketNumber(),
      [](const Student& item) { return item.TicketNumber(); });

  if (duplicate != _students.end())
    throw std::invalid_argument("[Manager::Add] Duplicate ticket number");

  _students.push_back(student);
}

// --------------------------------------------------

void Manager::Remove(const std::string& ticket_number) {
  const auto student = std::ranges::find(
      _students, ticket_number,
      [](const Student& item) { return item.TicketNumber(); });

  if (student == _students.end())
    throw std::invalid_argument("[Manager::Remove] Student not found");

  _students.erase(student);
}

// MARK: Print student list
// --------------------------------------------------

void Manager::PrintAll() const {
  if (_students.empty()) {
    _output << "Student list is empty.\n";

    return;
  }

  for (const Student& student : _students) _output << student << '\n';
}

// MARK: Sort student list
// --------------------------------------------------

void Manager::SortBy(SortField field) {
  std::ranges::sort(_students, [field](const Student& lhs, const Student& rhs) {
    switch (field) {
      case SortField::FirstName:
        return lhs.FirstName() < rhs.FirstName();

      case SortField::LastName:
        return lhs.LastName() < rhs.LastName();

      case SortField::TicketNumber:
        return lhs.TicketNumber() < rhs.TicketNumber();

      case SortField::Grade:
        throw std::invalid_argument("[Manager::SortBy] Grade requires subject");
    }

    throw std::logic_error("[Manager::SortBy] Unknown sort field");
  });
}

// MARK: Sort student list by grade
// --------------------------------------------------

void Manager::SortByGrade(std::size_t subject_number) {
  if (std::ranges::any_of(_students, [subject_number](const Student& student) {
        return !student.SubjectAverageGrades().contains(subject_number);
      })) {
    throw std::invalid_argument(
        "[Manager::SortByGrade] Subject grade is missing");
  }

  std::ranges::sort(_students,
                    [subject_number](const Student& lhs, const Student& rhs) {
                      return lhs.SubjectAverageGrades().at(subject_number) <
                             rhs.SubjectAverageGrades().at(subject_number);
                    });
}
