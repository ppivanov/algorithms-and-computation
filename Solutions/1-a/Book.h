#ifndef BOOK_H
#define BOOK_H

#include "Product.h"

class Book : public Product {
public:
	Book(double netPrice);
	~Book();

	virtual double getGrossPrice();
};

#endif // !BOOK_H
