#pragma once

#include <cstddef>
#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

#include "SortField.hpp"
#include "Student.hpp"
#include "Subject.hpp"

/**
 * @brief Управляет списками студентов, предметов и их привязками.
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
   * @brief Удаляет студента и все его привязки к предметам.
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

  /**
   * @brief Добавляет предмет с уникальным номером.
   * @param subject_number номер добавляемого предмета
   * @throw std::invalid_argument если предмет уже существует
   */
  void AddSubject(std::size_t subject_number);

  /**
   * @brief Удаляет предмет и все привязки к нему.
   * @param subject_number номер удаляемого предмета
   * @throw std::invalid_argument если предмет не найден
   */
  void RemoveSubject(std::size_t subject_number);

  /**
   * @brief Выводит все предметы.
   */
  void PrintAllSubjects() const;

  /**
   * @brief Выводит предмет и привязанных к нему студентов.
   * @param subject_number номер предмета
   * @throw std::invalid_argument если предмет не найден
   */
  void PrintSubject(std::size_t subject_number) const;

  /**
   * @brief Привязывает студента к предмету с указанной средней оценкой.
   * @param ticket_number номер студенческого билета
   * @param subject_number номер предмета
   * @param average_grade средняя оценка
   */
  void AttachStudent(const std::string& ticket_number,
                     std::size_t subject_number, double average_grade);

  /**
   * @brief Удаляет привязку студента к предмету.
   * @param ticket_number номер студенческого билета
   * @param subject_number номер предмета
   */
  void DetachStudent(const std::string& ticket_number,
                     std::size_t subject_number);

 private:
  /**
   * @brief Находит студента по номеру билета.
   * @param ticket_number номер студенческого билета
   * @return найденный студент
   * @throw std::invalid_argument если студент не найден
   */
  std::shared_ptr<Student> FindStudent(const std::string& ticket_number) const;

  /**
   * @brief Находит предмет по номеру.
   * @param subject_number номер предмета
   * @return найденный предмет
   * @throw std::invalid_argument если предмет не найден
   */
  std::shared_ptr<Subject> FindSubject(std::size_t subject_number) const;

  std::ostream& _output;
  std::vector<std::shared_ptr<Student>> _students;
  std::vector<std::shared_ptr<Subject>> _subjects;
};
