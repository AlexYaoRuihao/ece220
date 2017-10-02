#include "shape.hpp"
#include <math.h>
#include <fstream>
#include <string>
#include <vector>



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable
Shape::Shape(string name)
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
{
	width_ = width;
	length_ = length;
}

double Rectangle::getArea()
{
      return width_*length_;
}

double Rectangle::getVolume()
{
	return 0;
}

Rectangle Rectangle::operator +(const Rectangle& rec)
{
	double nl,nw;	
	nl = getLength() + rec.length_;
	nw = getWidth()+rec.width_;
	return Rectangle(nw, nl);
}

Rectangle Rectangle::operator -(const Rectangle& rec)
{
	double nl,nw;	
	nl = length_ - rec.length_;
	nw = width_-rec.width_;
	if(nl<0){nl=0;}
	if(nw<0){nw=0;}
	return Rectangle(nw, nl);
}





double Rectangle::getWidth(){return width_;}
double Rectangle::getLength(){return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle")
{
	radius_ = radius;
}
 double Circle::getArea()
 {
 	return M_PI*pow(radius_,2);
 }

double Circle::getVolume()
{
	return 0;
}

Circle Circle::operator +(const Circle& cir)
{
	double newRad;
	newRad = getRadius() + cir.radius_;
	return Circle(newRad);
}

Circle Circle::operator -(const Circle& cir)
{
	double newRad;
	if(getRadius()-cir.radius_ > 0)
	{
		newRad = getRadius()-cir.radius_;
	}
	else
	{
		newRad = 0;
	}
	return Circle(newRad);
}

double Circle::getRadius(){return radius_;}



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Sphere::Sphere(double radius):Shape("Sphere")
{
	radius_ = radius;
}

double Sphere::getArea()
{
    return 4*M_PI*pow(radius_,2);
}

double Sphere::getVolume()
{
     return (4.0 / 3.0)*M_PI*pow(radius_,3);
}

Sphere Sphere::operator +(const Sphere& sph)
{
	double newRad;
	newRad = getRadius() + sph.radius_;
	return Sphere(newRad);
}

Sphere Sphere::operator -(const Sphere& sph)
{
	double newRad;
	if(getRadius()-sph.radius_ > 0)
	{
		newRad = getRadius()-sph.radius_;
	}
	else
	{
		newRad = 0;
	}
	return Sphere(newRad);
}

double Sphere::getRadius(){return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism"){
	width_=width;
	length_=length;
	height_=height;
}
RectPrism RectPrism::operator + (const RectPrism& rectp){
	double n_l, n_w, n_h;
	n_l=getLength()+rectp.length_;
	n_h=getHeight()+rectp.height_;
	n_w=getWidth()+rectp.width_;
	return RectPrism(n_w, n_l, n_h);
}
RectPrism RectPrism::operator - (const RectPrism& rectp){
	double n_l, n_w, n_h;
	n_l=getLength()-rectp.length_;
	n_h=getHeight()-rectp.height_;
	n_w=getWidth()-rectp.width_;
	if(n_l<0){n_l=0;}
	if(n_h<0){n_h=0;}
	if(n_w<0){n_w=0;}
	return RectPrism(n_w, n_l, n_h);

}
double RectPrism::getVolume(){return length_*width_*height_;}
double RectPrism::getArea(){return 2*(length_*width_+length_*height_+width_*height_);}
double RectPrism::getWidth(){return width_;}
double RectPrism::getHeight(){return height_;}
double RectPrism::getLength(){return length_;}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
	std::ifstream infile(file_name);
	int n;
	infile >> n;
	string name;
	std::vector<Shape*> v(n);//set up vector
	double a, b, c;
	for (int i=0; i<n; i++){
		infile >> name;
		if(name == "Rectangle"){
			infile >> a >> b;
			v[i]=new Rectangle(a, b);
		}
		if(name == "Circle"){
			infile >> a;
			v[i]=new Circle(a);
		}
		if(name == "Sphere"){
			infile >> a;
			v[i]=new Sphere(a);
		}
		if(name == "RectPrism"){
			infile >> a >> b >> c;
			v[i]=new RectPrism(a,b,c);
		}
	}

	infile.close();

	return v; // please remeber to modify this line to return the correct value
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = shapes[0]->getArea();
	//@@Insert your code here
	for (int i=1; i<shapes.size(); i++){
		if(shapes[i]->getArea()>max_area){
			max_area=shapes[i]->getArea();
		}
	}
	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = shapes[0]->getVolume();
	//@@Insert your code here
	for (int i=1; i<shapes.size(); i++){
		if (shapes[i]->getVolume()>max_volume){
			max_volume=shapes[i]->getVolume();
		}
	}

	return max_volume;
}
