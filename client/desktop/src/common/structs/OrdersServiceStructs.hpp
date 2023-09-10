#pragma once

#include "string"
#include "vector"

#include "common/enums/OrdersServiceEnums.hpp"

struct Order
{
  int id;
  std::string orderDate;
  float totalAmount;
  OrderStatus status;
};
