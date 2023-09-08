#include "common/defines/inc/Api.hpp"

Api::Api(const std::string &baseUrl) : mBaseUrl(baseUrl)
{
}

Api::~Api()
{
}

std::string Api::get(const std::string &url)
{
  return "";
}

std::string Api::post(const std::string &url, const std::string &data)
{
  return "";
}

std::string Api::remove(const std::string &url, const std::string &id)
{
  return "";
}

std::string Api::put(const std::string &url, const std::string &data)
{
  return "";
}
