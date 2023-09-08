#include "services/inc/OrdersService.hpp"

OrdersService::OrdersService(std::string endPoint, Api &api)
    : mEndPorint(endPoint), mApi(api)
{
}

OrdersService::~OrdersService()
{
}
