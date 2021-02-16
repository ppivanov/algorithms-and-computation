#include "Book.h"

Book::Book(double netPriceIn) : Product{ netPriceIn } {}
Book::~Book() = default;

double Book::getGrossPrice() {
	return getNetPrice();
}
