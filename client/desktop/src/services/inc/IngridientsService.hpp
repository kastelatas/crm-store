#pragma once

#include "iostream"
#include <string>

#include "common/defines/inc/Api.hpp"
#include "common/structs/IngridientsServiceStructs.hpp"

class IngridientsService
{
public:
  IngridientsService(std::string endPoint, Api &api);

  ~IngridientsService();

public:
  std::string getIngridients(std::string params);
  Ingredient getOneIngridient(int id);
  void createIngridient(Ingredient dish);
  Ingredient updateIngridient(Ingredient dish);
  void deleteIngridient(int id);

private:
  std::string mEndPorint;
  Api &mApi;
};