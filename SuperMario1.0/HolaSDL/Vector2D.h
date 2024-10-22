#ifndef Vector2D_h
#define Vector2D_h

template <class T>
class Vector2D
{
	
private:
	T x, y;


public:
	// Constructoras
	Vector2D::Vector2D() {}
	Vector2D::Vector2D(T x, T y)
		: x(x), y(y) {}

	// Getters
	T getX() { return x; }
	T getY() { return y; }
	// Setters
	void setX(T newX) { x = newX; }
	void setY(T newY) { y = newY; }

	// Operador +
	Vector2D operator+(const Vector2D& v) const
	{
		Vector2D suma;

		suma.x = x + v.x;
		suma.y = y + v.y;

		return suma;
	}

	// Operador -
	Vector2D operator-(const Vector2D& v) const
	{
		Vector2D resta;

		resta.x = x - v.x;
		resta.y = y - v.y;

		return resta;
	}

	// Operador producto escalar *
	Vector2D operator*(int i) const
	{
		Vector2D escalar;

		escalar.x = x * i;
		escalar.y = y * i;

		return escalar;
	}

	// Operador producto vector-escalar *
	T operator*(const Vector2D& i) const
	{
		return i.x * x + i.y * y;
	}

	// Operador salida consola <<
	friend std::ostream& operator<<(std::ostream& pos, const Vector2D& v)
	{
		pos << "(" << v.x << "," << v.y << ")";
		return pos;
	}
};

template <class T = int> 

// Using Point2D
using Point2D = Vector2D<T>;

#endif