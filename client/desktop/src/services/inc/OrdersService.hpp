#pragma once

#include "iostream"
#include <string>

#include "common/defines/inc/Api.hpp"

class OrdersService
{
public:
  OrdersService(std::string endPoint, Api &api);

  ~OrdersService();

public:
private:
  std::string mEndPorint;
  Api &mApi;
};