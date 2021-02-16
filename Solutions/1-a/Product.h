#ifndef PRODUCT_H
#define PRODUCT_H

class Product {
public:
	Product(double netPrice);
	~Product();

	virtual double getGrossPrice();
	double getNetPrice() const;
private:
	double netPrice;
};

#endif // !PRODUCT_H
