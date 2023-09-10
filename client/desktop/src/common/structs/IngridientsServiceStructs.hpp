#pragma once

#include "common/enums/IngridientsServiceEnums.hpp"

struct Ingredient
{
  std::string name;
  float quantity;
  QuantityUnit quantityUnit;
  float price;
  PriceUnit priceUnit;
};
