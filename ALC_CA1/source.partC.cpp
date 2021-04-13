// Pavel Ivanov x00149863

#include <iostream>

class Shape
{
public:
	Shape();
	~Shape();
	virtual void draw();
};

Shape::Shape() = default;
Shape::~Shape() = default;
void Shape::draw() {
	std::cout << "shape\n";
}

class Circle : public Shape
{
public:
	Circle();
	~Circle();
	void draw();
};

Circle::Circle() : Shape() {};
Circle::~Circle() = default;
void Circle::draw() {
	std::cout << "cirlce\n";
}

class Square : public Shape
{
public:
	Square();
	~Square();
	void draw();
};

Square::Square() : Shape() {};
Square::~Square() = default;
void Square::draw() {
	std::cout << "square\n";
}

class Triangle : public Shape
{
public:
	Triangle();
	~Triangle();
	void draw();
};

Triangle::Triangle() : Shape() {};
Triangle::~Triangle() = default;
void Triangle::draw() {
	std::cout << "triangle\n";
}

//int main() {
//
//	const int arr_size = 4;
//	Shape* arr[] = { new Shape(), new Circle(), new Square(), new Triangle() };
//
//	for (int i = 0; i < arr_size; i++)
//		arr[i]->draw();
//
//	return 0;
//}