#pragma once

#include "string"
#include "vector"

#include "common/structs/IngridientsServiceStructs.hpp"

struct Dish
{
  int id;
  std::string name;
  float cost;
  float price;
  std::vector<Ingredient> ingredients;
};

struct Menu
{
  int id;
  std::vector<Dish> dishs;
};
