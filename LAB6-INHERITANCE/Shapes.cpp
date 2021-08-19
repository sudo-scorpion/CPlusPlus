#include<iostream>
#include <string>
#include <cmath>
#include "Shapes.h"

// Operator overloading definition begins here
bool Shape2D::operator>(const Shape2D &rhs) const {
    if (Area() > rhs.Area())
        return true;
    else
        return false;
}

bool Shape2D::operator<(const Shape2D &rhs) const {
    if (Area() < rhs.Area())
        return true;
    else
        return false;
}

bool Shape2D::operator==(const Shape2D &rhs) const {

    if (Area() == rhs.Area())
        return true;
    else
        return false;
}

bool Shape3D::operator>(const Shape3D &rhs) const {
    if (Volume() > rhs.Volume())
        return true;
    else
        return false;
}

bool Shape3D::operator<(const Shape3D &rhs) const {
    if (Volume() < rhs.Volume())
        return true;
    else
        return false;
}

bool Shape3D::operator==(const Shape3D &rhs) const {
    if (Volume() == rhs.Volume())
        return true;
    else
        return false;
}
// ends

// Square class definitions begins
Square::Square(float length, string square) {
    _length = length;
    _square = std::move(square);
}


float Square::Area() const {
    return powf(_length, 2.0);
}

void Square::Scale(float scaleFactor) {
    _length *= scaleFactor;
}

void Square::ShowArea() const {
    cout << "The area of the " + GetName2D() + " is : " << Area() << endl;
}

string Square::GetName2D() const {
    return _square;
}

void Square::Display() const {
    ShowArea();
    cout << "Length of a side: " << _length << endl;
}
// ends


// Triangle class definitions begin
Triangle::Triangle(float base, float height, string triangle) {
    _base = base;
    _height = height;
    _triangle = std::move(triangle);
}


float Triangle::Area() const {
    return float(1.0/2.0 * _base * _height);
}

void Triangle::Scale(float scaleFactor) {
    _base *= scaleFactor;
    _height *= scaleFactor;
}

void Triangle::ShowArea() const {
    cout << "The area of the " + GetName2D() + " is : " << Area() << endl;
}

string Triangle::GetName2D() const {
    return _triangle;
}

void Triangle::Display() const {
    ShowArea();
    cout << "Base: " << _base << endl;
    cout << "Height: " << _height << endl;
}
// ends


// Circle class definition begins
Circle::Circle(float radius, string circle) {
    _radius = radius;
    _circle = std::move(circle);
}

float Circle::Area() const {
    return PI * powf(_radius, 2.0);
}

void Circle::Scale(float scaleFactor) {
    _radius *= scaleFactor;
}

void Circle::ShowArea() const {
    cout << "The area of the " + GetName2D() + " is : " << Area() << endl;
}

string Circle::GetName2D() const {
    return _circle;
}

void Circle::Display() const {
    ShowArea();
    cout << "Radius: " << _radius << endl;
}
// ends


// TriangularPyramid class definition begin
float TriangularPyramid::Area() const {
    return float(1.0/2.0 * _base * _height);
}

TriangularPyramid::TriangularPyramid(float height, float base, float height2, string triangularPyramid) {
    _length = height;
    _base = base;
    _height = height2;
    _triangularPyramid = std::move(triangularPyramid);
}

float TriangularPyramid::Volume() const {
    return float(1.0/3.0 * Area() * _length);
}


string TriangularPyramid::GetName3D() const {
    return _triangularPyramid;
}

void TriangularPyramid::ShowVolume() const {
    cout << "The volume of the " + GetName3D() + " is : " << Volume() << endl;
}

void TriangularPyramid::Scale(float scaleFactor) {
    _length *= scaleFactor;
    _base *= scaleFactor;
    _height *= scaleFactor;
}

void TriangularPyramid::Display() const {
    ShowVolume();
    cout << "The height is: " << _length << endl;
    cout << "The area of the Triangle is: " << Area() << endl;
    cout << "Base: " << _base << endl;
    cout << "Height: " << _height << endl;
}
// ends


// cylinder class definition begins
Cylinder::Cylinder(float height, float radius, string cylinder) {
    _height = height;
    _radius = radius;
    _cylinder = std::move(cylinder);
}

float Cylinder::Area() const {
    return PI * powf(_radius, 2.0);
}

float Cylinder::Volume() const {
    return Area() * _height;
}

string Cylinder::GetName3D() const {
    return _cylinder;
}

void Cylinder::ShowVolume() const {
    cout << "The volume of the " + GetName3D() + " is : " << Volume() << endl;
}

void Cylinder::Scale(float scaleFactor) {
    _height *= scaleFactor;
    _radius *= scaleFactor;
}

void Cylinder::Display() const {
    ShowVolume();
    cout << "The height is: " << _height << endl;
    cout << "The area of the Circle is: " << Area() << endl;
    cout << "Radius: " << _radius << endl;
}
// ends


// Sphere class definition begins
Sphere::Sphere(float radius, string sphere) {
    _radius = radius;
    _sphere = std::move(sphere);
}

float Sphere::Area() const {
    return PI * powf(_radius, 2.0);
}

float Sphere::Volume() const {
    return float(4.0/3.0 * Area() * _radius);
}

string Sphere::GetName3D() const {
    return _sphere;
}

void Sphere::ShowVolume() const {
    cout << "The volume of the " + GetName3D() + " is : " << Volume() << endl;
}

void Sphere::Scale(float scaleFactor) {
    _radius *= scaleFactor;
}

void Sphere::Display() const {
    ShowVolume();
    cout << "The area of the Circle is: " << Area() << endl;
    cout << "Radius: " << _radius << endl;
}
// ends


// Destructor for all classes
Shape::~Shape() = default;

Shape2D::~Shape2D() = default;

Sphere::~Sphere() = default;

Circle::~Circle() = default;

Triangle::~Triangle() = default;

Shape3D::~Shape3D() = default;

Square::~Square() = default;

Cylinder::~Cylinder() = default;

TriangularPyramid::~TriangularPyramid() = default;
