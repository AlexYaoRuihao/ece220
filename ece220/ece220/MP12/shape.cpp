#include "shape.hpp"
#include <math.h>
#include <vector>
#include<string>

using namespace std;

/*
  Intro Paragraph: For this MP, we utilized C++ classes and inheritance
  methods to implement the basic functionalities. Basically we have a base
  class called Shape and four derived class which are Rectangle, Circle, Sphere
  and RectPrism. We need to use polymorphism to define each class's corresponding
  constructor functions and get functions. In addition, we need to overload
  the operators by using our own methods
*/



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
Shape::Shape(string name)//base class's constructor
{
  name_ = name;
}

string Shape::getName()
{
  return name_;
}



//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Rectangle::Rectangle(double width, double length):Shape("Rectangle")
{//Rectangle class's constructor
  width_ = width;
  length_ = length;
}

double Rectangle::getArea()const
{
  return width_*length_;
}

double Rectangle::getVolume()const
{
  return 0;
}

Rectangle Rectangle::operator + (const Rectangle& rec){
  //Rectangle c(0,0);
  Rectangle c;//we can use the default constructor to instantiate an object
  c.width_ = getWidth() + rec.width_;
  c.length_ = getLength() + rec.length_;
  return c;
}

Rectangle Rectangle::operator - (const Rectangle& rec){
  //Rectangle c(0,0);
  Rectangle c;
  c.width_ = getWidth() - rec.width_;
  if(c.width_ < 0)
  {
    c.width_ = 0;
  }

  c.length_ = getLength() - rec.length_;
  if(c.length_ < 0)
  {
    c.length_ = 0;
  }

  return c;
}

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle")
{
  radius_ = radius;
}

double Circle::getArea()const
{
  return M_PI*radius_*radius_;
}

double Circle::getVolume()const
{
  return 0;
}

Circle Circle::operator + (const Circle& cir)
{
  Circle d(0);//Here, we must use the parameterized constructor to instantiate the object
  d.radius_ = getRadius() + cir.radius_;
  return d;
}

Circle Circle::operator - (const Circle& cir)
{
  Circle d(0);
  d.radius_ = getRadius() - cir.radius_;
  if(d.radius_ < 0)
  {
    d.radius_ = 0;
  }
  return d;
}

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Sphere::Sphere(double radius):Shape("Sphere")
{
  radius_ = radius;
}

double Sphere::getVolume()const{
  return (4.0/3.0)*radius_*radius_*radius_*M_PI;
}

double Sphere::getArea()const{
  return 4*M_PI*radius_*radius_;
}

Sphere Sphere::operator + (const Sphere& sph)
{
  Sphere c(0);//we must use the parameterized constructor here to instantiate an object
  c.radius_ = getRadius() + sph.radius_;
  return c;
}

Sphere Sphere::operator - (const Sphere& sph)
{
  Sphere c(0);
  c.radius_ = getRadius() - sph.radius_;
  if(c.radius_ < 0)
  {
    c.radius_ = 0;
  }
  return c;
}


double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism")
{
  length_ = length;
  width_ = width;
  height_ = height;
}

double RectPrism::getVolume() const{
  return length_*width_*height_;
}

double RectPrism::getArea() const{
  return 2*(length_*width_ + length_*height_ + width_*height_);
}

RectPrism RectPrism::operator + (const RectPrism& rectp)
{
  RectPrism c(0,0,0);//we must use the parameterized constructor to instantiate an object
  c.length_ = getLength() + rectp.length_;
  c.width_ = getWidth() + rectp.width_;
  c.height_ = getHeight() + rectp.height_;
  return c;
}

RectPrism RectPrism::operator - (const RectPrism& rectp)
{
  RectPrism c(0,0,0);
  c.length_ = getLength() - rectp.length_;
  if(c.length_ < 0)
  {
    c.length_ = 0;
  }

  c.width_ = getWidth() - rectp.width_;
  if(c.width_ < 0)
  {
    c.width_ = 0;
  }

  c.height_ = getHeight() - rectp.height_;
  if(c.height_ < 0)
  {
    c.height_ = 0;
  }

  return c;
}



double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
  int number_of_objects;
  ifstream ifs ("test1.txt", std::ifstream::in);
  ifs>>number_of_objects;//get number_of_objects

  std::vector<Shape*> v(number_of_objects);//declare a vector of shape* objects

  double a,b,c;//declare double types variables to hold values from the input stream

  string name;
  for(int i = 0; i < number_of_objects; i++)
  {
    ifs>>name;
    if(name == "Circle")
    {
      ifs>>a;
      v[i] = new Circle(a);
    }
    else if(name == "Rectangle")
    {
      ifs>>a>>b;
      v[i] = new Rectangle(a,b);
    }
    else if(name == "Sphere")
    {
      ifs>>a;
      v[i] = new Sphere(a);
    }
    else if(name == "RectPrism")
    {
      ifs>>a>>b>>c;
      v[i] = new RectPrism(a,b,c);
    }
  }

  ifs.close();

  return v;
	//return vector<Shape*>(0, NULL); // please remeber to modify this line to return the correct value
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
  //set shape[0]'s Area as max_area and replace it if we find bigger areas
  //same algorithm applies to volume
  max_area = shapes[0]->getArea();

  for(int i = 1; i < shapes.size(); i++)
  {
    if(shapes[i]->getArea() > max_area)
    {
      max_area = shapes[i]->getArea();
    }
  }
	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
  max_volume = shapes[0]->getVolume();

  for(int i = 1; i < shapes.size(); i++)
  {
    if(shapes[i]->getVolume() > max_volume)
    {
      max_volume = shapes[i]->getVolume();
    }
  }

	return max_volume;
}
