#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>
#include <time.h>
using namespace std;

class AlcoholicDrink;
class Tobacco;
class Food;

class Tax{
	double alcoTax;
	double tobaccoTax;
	double foodTax;
public:
	Tax() : alcoTax(0.2), tobaccoTax(0.3), foodTax(0.1) {}
	double getPriceAfterTax(AlcoholicDrink& item);
	double getPriceAfterTax(Tobacco& item);
	double getPriceAfterTax(Food& item);
};

class AlcoholicDrink{
	double price;
public:
	AlcoholicDrink(double price) : price(price) {}
	double getNetPrice(){ return price; }
	double getPrice(Tax& tax);
};

class Tobacco{
	double price;
public:
	Tobacco(double price) : price(price) {}
	double getNetPrice(){ return price; }
	double getPrice(Tax& tax);
};

class Food{
	double price;
public:
	Food(double price) : price(price) {}
	double getNetPrice(){ return price; }
	double getPrice(Tax& tax);
};

double Tax::getPriceAfterTax(AlcoholicDrink& item){
	return item.getNetPrice() * (1 + tobaccoTax);
}

double Tax::getPriceAfterTax(Tobacco& item){
	return item.getNetPrice() * (1 + tobaccoTax);
}

double Tax::getPriceAfterTax(Food& item){
	return item.getNetPrice() * (1 + foodTax);
}

double AlcoholicDrink::getPrice(Tax& tax){
	return tax.getPriceAfterTax(*this);
}

double Tobacco::getPrice(Tax& tax){
	return tax.getPriceAfterTax(*this);
}

double Food::getPrice(Tax& tax){
	return tax.getPriceAfterTax(*this);
}


int main(int argc, char* argv[])
{
	Catch::Session().run(argc, argv);
	system("PAUSE");
	return 0;
}

TEST_CASE("Main"){
	Tax tax;
	srand(time(NULL));

	SECTION("Alco") {
		for (int i = 0; i < 5; i++){
			double alcoPrice = 50 + rand() % 100;
			AlcoholicDrink alco(alcoPrice);
			CHECK(alco.getNetPrice() == Approx(alcoPrice).epsilon(0.1));
			CHECK(alco.getPrice(tax) == Approx(alcoPrice * 1.2).epsilon(0.1));
		}
	}

	SECTION("Tobacco") {
		for (int i = 0; i < 5; i++){
			double tobaccoPrice = 20 + rand() % 100;
			Tobacco cigarettes(tobaccoPrice);
			CHECK(cigarettes.getNetPrice() == Approx(tobaccoPrice).epsilon(0.1));
			CHECK(cigarettes.getPrice(tax) == Approx(tobaccoPrice * 1.3).epsilon(0.1));
		}
	}

	SECTION("Food") {
		for (int i = 0; i < 5; i++){
			double foodPrice = 30 + rand() % 100;
			Food food(foodPrice);
			CHECK(food.getNetPrice() == Approx(foodPrice).epsilon(0.1));
			CHECK(food.getPrice(tax) == Approx(foodPrice * 1.1).epsilon(0.1));
		}
	}
}
