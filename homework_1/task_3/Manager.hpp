#pragma once

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

#include "SortField.hpp"
#include "Student.hpp"

/**
 * @brief Управляет списком студентов.
 */
class Manager {
 public:
  /**
   * @brief Создаёт менеджер, выводящий сообщения в указанный поток.
   * @param output поток для сообщений
   */
  explicit Manager(std::ostream& output);

  /**
   * @brief Добавляет студента, если номер его билета уникален.
   * @param student добавляемый студент
   * @throw std::invalid_argument если номер билета уже существует
   */
  void Add(const Student& student);

  /**
   * @brief Удаляет студента по номеру билета.
   * @param ticket_number номер студенческого билета
   * @throw std::invalid_argument если студент не найден
   */
  void Remove(const std::string& ticket_number);

  /**
   * @brief Выводит всех студентов из списка.
   */
  void PrintAll() const;

  /**
   * @brief Сортирует студентов по указанному полю.
   * @param field поле сортировки
   * @throw std::invalid_argument если передана сортировка по оценке
   */
  void SortBy(SortField field);

  /**
   * @brief Сортирует студентов по оценке за указанный предмет.
   * @param subject_number номер предмета
   * @throw std::invalid_argument если оценка за указанный предмет отсутствует
   */
  void SortByGrade(std::size_t subject_number);

 private:
  std::ostream& _output;
  std::vector<Student> _students;
};
