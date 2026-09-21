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
  std::cout << "\n"
            << "Student Manager\n"
            << "===============\n"
            << "add    <ticket_number> <last_name> <first_name> "
               "<subject_number> <average_grade>...\n"
            << "       Add a student with an average grade for each subject.\n"
            << "remove <ticket_number>\n"
            << "       Remove a student by ticket number.\n"
            << "list\n"
            << "       Print all students.\n"
            << "sort   first_name|last_name|ticket_number\n"
            << "       Sort students by the selected field.\n"
            << "sort   grade <subject_number>\n"
            << "       Sort students by a grade for the selected subject.\n"
            << "help\n"
            << "       Print this command reference.\n"
            << "exit\n"
            << "       Exit the program.\n\n";
}

// MARK: Parse command arguments
// --------------------------------------------------

Student ParseStudent(std::istringstream& input) {
  std::string ticket_number;
  std::string last_name;
  std::string first_name;
  std::map<std::size_t, double> subject_average_grades;

  std::size_t subject_number = 0;
  double average_grade = 0.0;

  input >> ticket_number >> last_name >> first_name;

  while (input >> subject_number) {
    if (subject_number == 0)
      throw std::invalid_argument(
          "[ParseStudent] Subject number must be positive");

    if (!(input >> average_grade))
      throw std::invalid_argument("[ParseStudent] Average grade is missing");

    const bool inserted =
        subject_average_grades.emplace(subject_number, average_grade).second;

    if (!inserted)
      throw std::invalid_argument("[ParseStudent] Duplicate subject number");
  }

  if (ticket_number.empty() || last_name.empty() || first_name.empty() ||
      subject_average_grades.empty())
    throw std::invalid_argument("[ParseStudent] Student data is incomplete");

  return Student(first_name, last_name, ticket_number, subject_average_grades);
}

// --------------------------------------------------

SortField ParseSortField(std::istringstream& input) {
  std::string field_name;

  input >> field_name;

  const auto sort_field_it = SORT_FIELDS.find(field_name);

  if (sort_field_it == SORT_FIELDS.end())
    throw std::invalid_argument("[ParseSortField] Unknown sort field");

  return sort_field_it->second;
}

// --------------------------------------------------

std::size_t ParseSubjectNumber(std::istringstream& input) {
  std::size_t subject_number = 0;

  input >> subject_number;

  if (subject_number == 0)
    throw std::invalid_argument(
        "[ParseSubjectNumber] Subject number must be positive");

  return subject_number;
}

// MARK: Handle commands
// --------------------------------------------------

void AddStudent(Manager& manager, std::istringstream& input) {
  manager.Add(ParseStudent(input));
  std::cout << "Student added.\n";
}

// --------------------------------------------------

void RemoveStudent(Manager& manager, std::istringstream& input) {
  std::string ticket_number;
  input >> ticket_number;

  if (ticket_number.empty())
    throw std::invalid_argument("[RemoveStudent] Ticket number is missing");

  manager.Remove(ticket_number);
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
          {"add", AddStudent},
          {"remove", RemoveStudent},
          {"sort", SortStudents},
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
      std::cout << "Unknown command." << command << "\n";

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
