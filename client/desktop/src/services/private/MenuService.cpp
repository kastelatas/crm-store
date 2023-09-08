#include "services/inc/MenuService.hpp"

MenuService::MenuService(std::string endPoint, Api &api)
    : mEndPorint(endPoint), mApi(api)
{
}

MenuService::~MenuService()
{
}

Menu MenuService::getMenu()
{
  Menu menu;

  return menu;
}

Dish MenuService::getOneDish(int id)
{
  Dish dish;

  return dish;
}

void MenuService::createDish(Dish dish)
{
}
