#include <iostream>
#include <string>

#include "common/defines/inc/Api.hpp"
#include "services/inc/MenuService.hpp"
#include "services/inc/IngridientsService.hpp"
#include "services/inc/ClientsService.hpp"
#include "services/inc/OrdersService.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  Api &api = Api("http://localhost:8080");

  MenuService &menuService = MenuService("/menu", api);
  OrdersService &ordersService = OrdersService("/orders", api);
  ClientsService &clientsService = ClientsService("/clients", api);
  IngridientsService &ingridientsService = IngridientsService("/ingridients", api);

  return 0;
}