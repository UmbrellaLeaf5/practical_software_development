#include "Manager.hpp"

#include <algorithm>
#include <stdexcept>

// MARK: Initialize manager
// --------------------------------------------------

Manager::Manager(std::ostream& output) : _output(output) {}

// MARK: Manage students
// --------------------------------------------------

void Manager::Add(const Student& student) {
  if (std::ranges::any_of(_students, [&student](const auto& item) {
        return item->TicketNumber() == student.TicketNumber();
      }))
    throw std::invalid_argument("[Manager::Add] Duplicate ticket number");

  _students.push_back(std::make_shared<Student>(student));
}

// --------------------------------------------------

void Manager::Remove(const std::string& ticket_number) {
  const std::shared_ptr<Student> student = FindStudent(ticket_number);

  for (const std::shared_ptr<Subject>& subject : _subjects)
    if (subject->HasStudent(student)) subject->RemoveStudent(student);

  std::erase_if(_students, [&ticket_number](const auto& item) {
    return item->TicketNumber() == ticket_number;
  });
}

// MARK: Print student list
// --------------------------------------------------

void Manager::PrintAll() const {
  if (_students.empty()) {
    _output << "Student list is empty.\n";

    return;
  }

  for (const std::shared_ptr<Student>& student : _students)
    _output << *student << '\n';
}

// MARK: Sort student list
// --------------------------------------------------

void Manager::SortBy(SortField field) {
  std::ranges::sort(_students, [field](const auto& lhs, const auto& rhs) {
    switch (field) {
      case SortField::FirstName:
        return lhs->FirstName() < rhs->FirstName();

      case SortField::LastName:
        return lhs->LastName() < rhs->LastName();

      case SortField::TicketNumber:
        return lhs->TicketNumber() < rhs->TicketNumber();

      case SortField::Grade:
        throw std::invalid_argument("[Manager::SortBy] Grade requires subject");
    }

    throw std::logic_error("[Manager::SortBy] Unknown sort field");
  });
}

// MARK: Sort student list by grade
// --------------------------------------------------

void Manager::SortByGrade(std::size_t subject_number) {
  if (std::ranges::any_of(_students, [subject_number](const auto& student) {
        return !student->HasSubject(subject_number);
      }))
    throw std::invalid_argument(
        "[Manager::SortByGrade] Subject grade is missing");

  std::ranges::sort(_students,
                    [subject_number](const auto& lhs, const auto& rhs) {
                      return lhs->SubjectAverageGrades().at(subject_number) <
                             rhs->SubjectAverageGrades().at(subject_number);
                    });
}

// MARK: Manage subjects
// --------------------------------------------------

void Manager::AddSubject(std::size_t subject_number) {
  if (std::ranges::any_of(_subjects, [subject_number](const auto& subject) {
        return subject->Number() == subject_number;
      }))
    throw std::invalid_argument(
        "[Manager::AddSubject] Duplicate subject number");

  _subjects.push_back(std::make_shared<Subject>(subject_number));
}

// --------------------------------------------------

void Manager::RemoveSubject(std::size_t subject_number) {
  const std::shared_ptr<Subject> subject = FindSubject(subject_number);

  for (const std::weak_ptr<Student>& weak_student : subject->Students()) {
    const std::shared_ptr<Student> student = weak_student.lock();

    if (student != nullptr) student->RemoveSubject(subject_number);
  }

  std::erase_if(_subjects, [subject_number](const auto& item) {
    return item->Number() == subject_number;
  });
}

// MARK: Print subject list
// --------------------------------------------------

void Manager::PrintAllSubjects() const {
  if (_subjects.empty()) {
    _output << "Subject list is empty.\n";

    return;
  }

  for (const std::shared_ptr<Subject>& subject : _subjects)
    PrintSubject(subject->Number());
}

// --------------------------------------------------

void Manager::PrintSubject(std::size_t subject_number) const {
  const std::shared_ptr<Subject> subject = FindSubject(subject_number);
  _output << "Subject " << subject->Number() << ":\n";

  for (const std::weak_ptr<Student>& weak_student : subject->Students()) {
    const std::shared_ptr<Student> student = weak_student.lock();

    if (student != nullptr) _output << "  " << *student << '\n';
  }
}

// MARK: Manage student subjects
// --------------------------------------------------

void Manager::AttachStudent(const std::string& ticket_number,
                            std::size_t subject_number, double average_grade) {
  const std::shared_ptr<Student> student = FindStudent(ticket_number);
  const std::shared_ptr<Subject> subject = FindSubject(subject_number);

  if (student->HasSubject(subject_number))
    throw std::invalid_argument(
        "[Manager::AttachStudent] Student already attached");

  subject->AddStudent(student);
  student->AddSubject(subject_number, average_grade);
}

// --------------------------------------------------

void Manager::DetachStudent(const std::string& ticket_number,
                            std::size_t subject_number) {
  const std::shared_ptr<Student> student = FindStudent(ticket_number);
  const std::shared_ptr<Subject> subject = FindSubject(subject_number);

  subject->RemoveStudent(student);
  student->RemoveSubject(subject_number);
}

// MARK: Private helpers
// --------------------------------------------------

std::shared_ptr<Student> Manager::FindStudent(
    const std::string& ticket_number) const {
  const auto student =
      std::ranges::find_if(_students, [&ticket_number](const auto& item) {
        return item->TicketNumber() == ticket_number;
      });

  if (student == _students.end())
    throw std::invalid_argument("[Manager::FindStudent] Student not found");

  return *student;
}

// --------------------------------------------------

std::shared_ptr<Subject> Manager::FindSubject(
    std::size_t subject_number) const {
  const auto subject =
      std::ranges::find_if(_subjects, [subject_number](const auto& item) {
        return item->Number() == subject_number;
      });

  if (subject == _subjects.end())
    throw std::invalid_argument("[Manager::FindSubject] Subject not found");

  return *subject;
}
