#pragma once

#include "iostream"
#include <string>

#include "common/defines/inc/Api.hpp"

class ClientsService
{
public:
  ClientsService(std::string endPoint, Api &api);
  ~ClientsService();

public:
private:
  std::string mEndPorint;
  Api &mApi;
};