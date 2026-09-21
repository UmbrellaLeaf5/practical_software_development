#include "Subject.hpp"

#include <algorithm>
#include <stdexcept>

#include "Student.hpp"

// MARK: Initialize subject
// --------------------------------------------------

Subject::Subject(std::size_t number) : _number(number) {}

// MARK: Get subject data
// --------------------------------------------------

std::size_t Subject::Number() const { return _number; }

// MARK: Manage subject students
// --------------------------------------------------

bool Subject::HasStudent(const std::shared_ptr<Student>& student) const {
  return std::ranges::any_of(_students, [&student](const auto& item) {
    const std::shared_ptr<Student> attached_student = item.lock();

    return attached_student != nullptr &&
           attached_student->TicketNumber() == student->TicketNumber();
  });
}

// --------------------------------------------------

void Subject::AddStudent(const std::shared_ptr<Student>& student) {
  if (HasStudent(student))
    throw std::invalid_argument(
        "[Subject::AddStudent] Student already attached");

  _students.push_back(student);
}

// --------------------------------------------------

void Subject::RemoveStudent(const std::shared_ptr<Student>& student) {
  const auto attached_student =
      std::ranges::find_if(_students, [&student](const auto& item) {
        const std::shared_ptr<Student> current_student = item.lock();

        return current_student != nullptr &&
               current_student->TicketNumber() == student->TicketNumber();
      });

  if (attached_student == _students.end())
    throw std::invalid_argument("[Subject::RemoveStudent] Student not found");

  _students.erase(attached_student);
}

// --------------------------------------------------

const std::vector<std::weak_ptr<Student>>& Subject::Students() const {
  return _students;
}
