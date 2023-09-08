#include "common/enums/MenuServiceEnums.hpp"

struct Ingredient
{
  std::string name;
  float quantity;
  QuantityUnit quantityUnit;
  float price;
  PriceUnit priceUnit;
};
