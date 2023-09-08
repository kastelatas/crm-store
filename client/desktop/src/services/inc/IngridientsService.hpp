#pragma once

#include "iostream"
#include <string>

#include "common/defines/inc/Api.hpp"

class IngridientsService
{
public:
  IngridientsService(std::string endPoint, Api &api);

  ~IngridientsService();

public:
private:
  std::string mEndPorint;
  Api &mApi;
};