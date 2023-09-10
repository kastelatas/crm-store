#pragma once

#include "iostream"
#include <string>

#include "common/defines/inc/Api.hpp"
#include "common/structs/MenuServiceStructs.hpp"

class MenuService
{
public:
  MenuService(std::string endPoint, Api &api);

  ~MenuService();

public:
  Menu getMenu(std::string params);
  Dish getOneDish(int id);
  void createDish(Dish dish);
  Dish updateDish(Dish dish);
  void deleteDish(int id);

private:
  std::string mEndPorint;
  Api &mApi;
};