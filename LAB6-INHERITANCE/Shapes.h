#pragma once
#include<iostream>
#include <string>
#include <cmath>
using namespace std;

class Shape
{
public:
    const float PI = 3.14159f;
	float _length, _base, _height, _radius;
	string _square, _triangle, _circle, _triangularPyramid, _cylinder, _sphere;
	virtual void Scale(float scaleFactor) = 0;
	virtual void Display() const = 0;
	virtual ~Shape();
};

class Shape2D : virtual public Shape
{
public:
	virtual float Area() const = 0;
    virtual void ShowArea() const = 0;
	virtual string GetName2D() const = 0;
	bool operator>(const Shape2D &rhs) const;
	bool operator<(const Shape2D &rhs) const;
	bool operator==(const Shape2D &rhs) const;
	~Shape2D() override;
};

class Shape3D : virtual public Shape
{
public:
    virtual float Area() const = 0;
	virtual float Volume() const = 0;
    virtual void ShowVolume() const = 0;
	virtual string GetName3D() const = 0;
	bool operator>(const Shape3D &rhs) const;
	bool operator<(const Shape3D &rhs) const;
	bool operator==(const Shape3D &rhs) const;
	~Shape3D() override;
};

class Square : virtual public Shape2D
{
public:
	explicit Square(float length = 0.0, string square = "Square");
	float Area() const override;
	void ShowArea() const override;
	string GetName2D() const override;
	void Scale(float scaleFactor) override;
	void Display() const override;
    ~Square() override;
};


class Triangle : virtual public Shape2D
{
public:
	explicit Triangle(float base = 0.0, float height = 0.0, string triangle = "Triangle");
	float Area() const override;
	void ShowArea() const override;
	string GetName2D() const override;
	void Scale(float scaleFactor) override;
	void Display() const override;
    ~Triangle() override;
};


class Circle : virtual public Shape2D
{
public:
	explicit Circle(float radius = 0.0, string circle = "Circle");
	float Area() const override;
	void ShowArea() const override;
	string GetName2D() const override;
	void Scale(float scaleFactor) override;
	void Display() const override;
    ~Circle() override;
};


class TriangularPyramid : virtual public Shape3D
{
public:
	explicit TriangularPyramid(float height = 0.0, float base = 0.0, float height2 = 0.0, string triangularPyramid = "Triangular Pyramid");
    float Area() const override;
	float Volume() const override;
	void ShowVolume() const override;
	string GetName3D() const override;
	void Scale(float scaleFactor) override;
	void Display() const override;
    ~TriangularPyramid() override;
};


class Cylinder : virtual public Shape3D
{
public:
	explicit Cylinder(float height = 0.0, float radius = 0.0, string cylinder = "Cylinder");
    float Area() const override;
	float Volume() const override;
	void ShowVolume() const override;
	string GetName3D() const override;
	void Scale(float scaleFactor) override;
	void Display() const override;
    ~Cylinder() override;
};

class Sphere : virtual public Shape3D
{
public:
	explicit Sphere(float radius = 0.0, string sphere = "Sphere");
    float Area() const override;
	float Volume() const override;
	void ShowVolume() const override;
	string GetName3D() const override;
	void Scale(float scaleFactor) override;
	void Display() const override;
    ~Sphere() override;
};
