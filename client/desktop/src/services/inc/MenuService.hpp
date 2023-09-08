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
  Menu getMenu();
  Dish getOneDish(int id);
  void createDish(Dish dish);

private:
  std::string mEndPorint;
  Api &mApi;
};