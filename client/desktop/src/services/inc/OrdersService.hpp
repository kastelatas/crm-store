#pragma once

#include "iostream"
#include <string>

#include "common/defines/inc/Api.hpp"
#include "common/structs/OrdersServiceStructs.hpp"

class OrdersService
{
public:
  OrdersService(std::string endPoint, Api &api);

  ~OrdersService();

public:
  std::string getOrders(std::string params);
  Order getOneOrder(int id);
  void createOrder(Order dish);
  Order updateOrder(Order dish);
  void deleteOrder(int id);

private:
  std::string mEndPorint;
  Api &mApi;
};