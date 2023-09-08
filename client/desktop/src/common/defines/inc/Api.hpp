#pragma once

#include "iostream"
#include <string>

class Api
{
public:
  Api(const std::string &baseUrl);

  ~Api();

public:
  std::string get(const std::string &url);
  std::string post(const std::string &url, const std::string &data);
  std::string remove(const std::string &url, const std::string &id);
  std::string put(const std::string &url, const std::string &data);

private:
  std::string mBaseUrl;
};