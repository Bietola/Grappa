#pragma once

#include <cstdlib>
#include <cassert>
#include <cmath>
#include <initializer_list>

#include <SFML/Graphics.hpp>


///---EVIL MACROS---
//macros (used together) that enable a base class function to return a derived type
//	NB: CRTP still needs to be implmented manually on derived types
#define IMPL_CLASS_BEGIN(CLASS_NAME) \
	template <class Derived> \
	struct CLASS_NAME ## Impl : public CLASS_NAME { \
		using CLASS_NAME::CLASS_NAME;

#define IMPL_CLASS_END };

#define IMPL_FUN(BASE, FUN_NAME) \
	template <typename... Args> \
	Derived& FUN_NAME(Args&&... args) { \
		return static_cast<Derived&>(BASE::FUN_NAME(std::forward<Args>(args)...)); \
	}


///---FUNCTION DECLARATIONS---
///"design helper" functions
//return an initializer list deduced from arguments (used in variadic templates)
template <typename T>
auto ilist(const std::initializer_list<T>& list) {
	return list;
}

///functions to get random numbers
//return a random number within a given range
int rrange(int min, int max);
int rrange(int max);
float rrangef(float min, float max);
float rrangef(float max);

///general arithmetic functions
//function that runs a callable object through a variadic list of any given type
template<typename Func, typename T>
T operate(Func opr, T op1);
template<typename Func, typename T, typename... Args>
T operate(Func opr, T op1, Args... args);

///vector operations
//get vector magnitude
template<typename T>
T getVectorMagnitude(const sf::Vector2<T>& vector);
//normalize vector
template<typename T>
sf::Vector2<T> normalizeVector(const sf::Vector2<T>& vector);
//set magnitude of given vector to given value
template<typename VT, typename ST>
sf::Vector2<VT> setVectorMagnitude(const sf::Vector2<VT>& vector, ST magnitude);
//print a vector to an output string
template<typename T>
std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& vector);

///rectangle operations
//add sf rectangles
template<typename T>
sf::Rect<T> operator+(const sf::Rect<T>& lhs, const sf::Rect<T>& rhs);
template <typename T>
sf::Rect<T>& operator+=(sf::Rect<T>& lhs, const sf::Rect<T>& rhs);
//subtract sf rectangles
template<typename T>
sf::Rect<T> operator-(const sf::Rect<T>& lhs, const sf::Rect<T>& rhs);
template <typename T>
sf::Rect<T>& operator-=(sf::Rect<T>& lhs, const sf::Rect<T>& rhs);

//print sf rectangle
template<typename T>
std::ostream& operator<<(std::ostream& stream, const sf::Rect<T>& rect);


///---TEMPLATE FUNCTION DEFINITIONS--
///vector operations
//multiply vectors
template<typename T>
auto operator*(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs) {
    return sf::Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
}
//divide vectors
template<typename T>
auto operator/(const sf::Vector2<T>& lhs, const sf::Vector2<T>& rhs) {
    return sf::Vector2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
}
//get vector magnitude
template<typename T>
T getVectorMagnitude(const sf::Vector2<T>& vector) {
    return std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}
//normalize vector
template<typename T>
sf::Vector2<T> normalizeVector(const sf::Vector2<T>& vector) {
    return vector / getVectorMagnitude(vector);
}
//set magnitude of given vector to given value
template<typename VT, typename ST>
sf::Vector2<VT> setVectorMagnitude(const sf::Vector2<VT>& vector, ST magnitude) {
    return normalizeVector(vector) * magnitude;
}
//multiply sf vector and scalar
template<typename VT, typename ST>
inline sf::Vector2<VT> operator*(const sf::Vector2<VT>& vect, const ST& scalar) {
    return sf::Vector2<VT>(vect.x * scalar, vect.y * scalar);
}
template<typename VT, typename ST>
inline sf::Vector2<VT>& operator*=(sf::Vector2<VT>& vect, const ST& scalar) {
    return vect = vect * scalar;
}
//print a vector to an output string
template<typename T>
std::ostream& operator<<(std::ostream& stream, const sf::Vector2<T>& vector){
    return stream << "V(" << vector.x << " " << vector.y << ")";
}

///rectangle operations
//add sf rectangles
template<typename T>
sf::Rect<T> operator+(const sf::Rect<T>& lhs, const sf::Rect<T>& rhs) {
    return sf::Rect<T>(lhs.left + rhs.left, lhs.top + rhs.top, lhs.width + rhs.width, lhs.height + rhs.height);
}
template<typename T>
sf::Rect<T>& operator+=(sf::Rect<T>& lhs, const sf::Rect<T>& rhs) {
	return lhs = lhs + rhs;
}
//subtract sf rectangles
template<typename T>
sf::Rect<T> operator-(const sf::Rect<T>& lhs, const sf::Rect<T>& rhs) {
    return sf::Rect<T>(lhs.left - rhs.left, lhs.top - rhs.top, lhs.width - rhs.width, lhs.height - rhs.height);
}
template<typename T>
sf::Rect<T>& operator-=(sf::Rect<T>& lhs, const sf::Rect<T>& rhs) {
	return lhs = lhs - rhs;
}
//print sf rectangle
template<typename T>
std::ostream& operator<<(std::ostream& stream, const sf::Rect<T>& rect) {
	return stream << "R(" << rect.left << " " << rect.top << " " << rect.width << " " << rect.height << ")"; 
}

