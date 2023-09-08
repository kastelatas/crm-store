#include "services/inc/ClientsService.hpp"

ClientsService::ClientsService(std::string endPoint, Api &api)
    : mEndPorint(endPoint), mApi(api)
{
}

ClientsService::~ClientsService()
{
}
