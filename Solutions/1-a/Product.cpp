#include "Product.h"

const double VAT = 0.21;

Product::Product(double netPriceIn) : netPrice{ netPriceIn } {}

Product::~Product() = default;

double Product::getGrossPrice() {
	return (netPrice + netPrice * VAT);
}

double Product::getNetPrice() const {
	return netPrice;
}
