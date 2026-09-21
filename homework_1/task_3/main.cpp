#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Manager.hpp"

namespace {

// MARK: Print command reference
// --------------------------------------------------

void PrintHelp() {
  std::cout
      << "\n"
      << "Student Manager\n"
      << "===============\n"
      << "add             <ticket_number> <last_name> <first_name>\n"
      << "                Add a student.\n"
      << "remove          <ticket_number>\n"
      << "                Remove a student and all subject attachments.\n"
      << "list\n"
      << "                Print all students.\n"
      << "sort            first_name|last_name|ticket_number\n"
      << "                Sort students by the selected field.\n"
      << "sort            grade <subject_number>\n"
      << "                Sort students by a grade for the selected subject.\n"
      << "add subject     <subject_number>\n"
      << "                Add a subject.\n"
      << "remove subject  <subject_number>\n"
      << "                Remove a subject and all attachments to it.\n"
      << "subjects\n"
      << "                Print all subjects and their students.\n"
      << "subject         <subject_number>\n"
      << "                Print one subject and its students.\n"
      << "attach          <ticket_number> <subject_number> <average_grade>\n"
      << "                Attach a student to a subject.\n"
      << "detach          <ticket_number> <subject_number>\n"
      << "                Detach a student from a subject.\n"
      << "help\n"
      << "                Print this command reference.\n"
      << "exit\n"
      << "                Exit the program.\n\n";
}

// MARK: Parse command arguments
// --------------------------------------------------

Student ParseStudent(const std::string& ticket_number,
                     std::istringstream& input) {
  std::string last_name;
  std::string first_name;
  const std::map<std::size_t, double> subject_average_grades;

  input >> last_name >> first_name;

  if (ticket_number.empty() || last_name.empty() || first_name.empty()) {
    throw std::invalid_argument("[ParseStudent] Student data is incomplete");
  }

  return Student(first_name, last_name, ticket_number, subject_average_grades);
}

// --------------------------------------------------

std::string ParseTicketNumber(std::istringstream& input) {
  std::string ticket_number;
  input >> ticket_number;

  if (ticket_number.empty()) {
    throw std::invalid_argument("[ParseTicketNumber] Ticket number is missing");
  }

  return ticket_number;
}

// --------------------------------------------------

SortField ParseSortField(std::istringstream& input) {
  std::string field_name;
  input >> field_name;

  const auto sort_field_it = SORT_FIELDS.find(field_name);

  if (sort_field_it == SORT_FIELDS.end()) {
    throw std::invalid_argument("[ParseSortField] Unknown sort field");
  }

  return sort_field_it->second;
}

// --------------------------------------------------

std::size_t ParseSubjectNumber(std::istringstream& input) {
  std::size_t subject_number = 0;
  input >> subject_number;

  if (subject_number == 0) {
    throw std::invalid_argument(
        "[ParseSubjectNumber] Subject number must be positive");
  }

  return subject_number;
}

// --------------------------------------------------

double ParseAverageGrade(std::istringstream& input) {
  double average_grade = 0.0;

  if (!(input >> average_grade)) {
    throw std::invalid_argument("[ParseAverageGrade] Average grade is missing");
  }

  return average_grade;
}

// MARK: Handle commands
// --------------------------------------------------

void AddEntity(Manager& manager, std::istringstream& input) {
  std::string entity;
  input >> entity;

  if (entity == "subject") {
    manager.AddSubject(ParseSubjectNumber(input));
    std::cout << "Subject added.\n";

    return;
  }

  manager.Add(ParseStudent(entity, input));
  std::cout << "Student added.\n";
}

// --------------------------------------------------

void RemoveEntity(Manager& manager, std::istringstream& input) {
  const std::string entity = ParseTicketNumber(input);

  if (entity == "subject") {
    manager.RemoveSubject(ParseSubjectNumber(input));
    std::cout << "Subject removed.\n";

    return;
  }

  manager.Remove(entity);
  std::cout << "Student removed.\n";
}

// --------------------------------------------------

void SortStudents(Manager& manager, std::istringstream& input) {
  const SortField field = ParseSortField(input);

  if (field == SortField::Grade)
    manager.SortByGrade(ParseSubjectNumber(input));

  else
    manager.SortBy(field);

  std::cout << "Student list sorted.\n";
}

// --------------------------------------------------

void PrintSubject(Manager& manager, std::istringstream& input) {
  manager.PrintSubject(ParseSubjectNumber(input));
}

// --------------------------------------------------

void AttachStudent(Manager& manager, std::istringstream& input) {
  const std::string ticket_number = ParseTicketNumber(input);
  const std::size_t subject_number = ParseSubjectNumber(input);

  const double average_grade = ParseAverageGrade(input);

  manager.AttachStudent(ticket_number, subject_number, average_grade);
  std::cout << "Student attached.\n";
}

// --------------------------------------------------

void DetachStudent(Manager& manager, std::istringstream& input) {
  const std::string ticket_number = ParseTicketNumber(input);
  const std::size_t subject_number = ParseSubjectNumber(input);

  manager.DetachStudent(ticket_number, subject_number);
  std::cout << "Student detached.\n";
}

}  // namespace

// MARK: Program entry point
// --------------------------------------------------

int main() {
  Manager manager(std::cout);
  const std::unordered_map<std::string,
                           std::function<void(Manager&, std::istringstream&)>>
      command_map = {
          {"help", [](Manager&, std::istringstream&) { PrintHelp(); }},
          {"list",
           [](Manager& manager, std::istringstream&) { manager.PrintAll(); }},
          {"add", AddEntity},
          {"remove", RemoveEntity},
          {"sort", SortStudents},
          {"subjects", [](Manager& manager,
                          std::istringstream&) { manager.PrintAllSubjects(); }},
          {"subject", PrintSubject},
          {"attach", AttachStudent},
          {"detach", DetachStudent},
      };
  std::string line;

  PrintHelp();

  while (std::getline(std::cin, line)) {
    std::istringstream input(line);
    std::string command;

    input >> command;

    if (command.empty()) continue;
    if (command == "exit") break;

    const auto command_it = command_map.find(command);

    if (command_it == command_map.end()) {
      std::cout << "Unknown command: " << command << '\n';

      continue;
    }

    try {
      command_it->second(manager, input);
    }

    catch (const std::exception& exception) {
      std::cout << "Error: " << exception.what() << '\n';
    }
  }

  return 0;
}
