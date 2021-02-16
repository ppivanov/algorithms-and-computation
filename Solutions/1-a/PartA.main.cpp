// cpp-console-application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include "Product.h"
#include "Book.h"
#include "Software.h"

using namespace std;

void productSelection(int& choice);

void requestNetPriceInput(double& netPrice);

void printList(vector<Product*> products);

void compareProducts();

int main()
{
	vector<Product*> products(4);

	Book* book;
	Software* software;

	double netPrice = 0;
	int vectorIndex = 0;

	cout << "Enter the net price for the BOOK: ";
	requestNetPriceInput(netPrice);

	book = new Book(netPrice);
	products[vectorIndex] = book;
	++vectorIndex;

	cout << "Enter the net price for the SOFTWARE: ";
	requestNetPriceInput(netPrice);

	software = new Software(netPrice);
	products[vectorIndex] = software;
	++vectorIndex;

	cout << "Book price: " << book->getGrossPrice() << endl;
	cout << "Software price: " << software->getGrossPrice() << endl;

	while(vectorIndex < products.capacity()) {
		netPrice = 0;

		int choice = 0;
		
		productSelection(choice);

		if (choice != 1 && choice != 2) {
			continue;
		}

		cout << "Enter the price of the product: ";
		requestNetPriceInput(netPrice);

		if (choice == 1) {
			products[vectorIndex] = new Book(netPrice);
		}
		else if (choice == 2) {
			products[vectorIndex] = new Software(netPrice);
		}
		else {
			continue; // skips the increment
		}

		++vectorIndex;
	}

	printList(products);

	std::sort(products.begin(), products.end(), comapareProducts);
	cout << "Sorted list" << endl;

	printList(products);
}

void productSelection(int& choice) {
	cout << "Select type of product:\n1.Book\n2.Software" << endl;
	cin >> choice;
}

void requestNetPriceInput(double& netPrice) {
	cin >> netPrice;
}

void printList(const vector<Product*> products) {
	for (Product* prod_pointer : products)
	{
		cout << prod_pointer->getGrossPrice() << endl;
	}
	cout << endl;
}

void comapareProducts(Product* p1, Product* p2) {
	return p1->getGrossPrice() < p2->getGrossPrice();
}
