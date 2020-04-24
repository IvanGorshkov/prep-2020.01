//
// Created by Ivan Gorshkov on 22.04.2020.
//

#pragma once

#include <exception>
#include <string>

class GameException: public std::exception {
 public:
  explicit GameException(const std::string& msg)
      : m_msg(msg) {}

  const char* what() const noexcept override {
    return m_msg.c_str();
  }

 private:
  std::string m_msg;
};

class InvalidFileStream: public GameException {
 public:
  InvalidFileStream()
      : GameException("Error occurred while reading from stream") {}
};

