#pragma once
#ifndef JARVIS_H
#define JARVIS_H
#include <vector>
#include <random>
//структура данных которая имитирует вектор в пространстве
struct vector2
{
	float x, y, z=0.0f;
	bool operator != (vector2 v1)
	{
		if (this->x == v1.x && this->y == v1.y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};
//функция определяет, с какой стороны от вектора AB находится точка C 
//(положительное возвращаемое значение соответствует левой стороне, отрицательное — правой).
inline bool isLeft(const  vector2& a, const  vector2& b, const  vector2& c)
{
	return (((b.x - a.x) * (c.y - b.y) -
		(c.x - b.x) * (b.y - a.y))>=0);
}

inline void jarvis(const std::vector<vector2> & source, std::vector<vector2>& result)
{
	if (source.empty())
	{
		return;
	}
	std::vector<vector2> src = source;
	typedef typename std::vector<vector2>::iterator PointIterator;
	PointIterator leftDownIt = src.begin();
	PointIterator it = leftDownIt + 1;
	vector2 currentPoint;
	vector2 leftDownPoint = *(leftDownIt);

	// нахождение левой нижней точки
	for (PointIterator end = src.end(); it != end; ++it)
	{
		currentPoint = *it;
		if (currentPoint.x < leftDownPoint.x)
		{
			leftDownPoint = currentPoint;
			leftDownIt = it;
		}
		else if (currentPoint.x == leftDownPoint.x
			&& currentPoint.y < leftDownPoint.y)
		{
			leftDownPoint = currentPoint;
			leftDownIt = it;
		}
	}
	// добовляем найденую точку в ответ
	src.erase(leftDownIt);
	result.push_back(leftDownPoint);

	currentPoint = leftDownPoint;

	vector2 nextPoint, tryPoint;
	PointIterator nextIt;
	do
	{
		nextPoint = leftDownPoint;
		nextIt = it;
		it = src.begin();
		for (PointIterator end = src.end(); it != end; ++it)
		{
			tryPoint = *it;
			if (isLeft(nextPoint,
				currentPoint,
				tryPoint))
			{
				nextPoint = tryPoint;
				nextIt = it;
			}
		}

		if (nextPoint != leftDownPoint)
		{
			src.erase(nextIt);
			result.push_back(nextPoint);
			currentPoint = nextPoint;
		}

	} while (nextPoint != leftDownPoint);



} 
inline void ranGen(int xn, int xk, std::vector<vector2> &points)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<>dis(xn,xk);
	for (int i = 0; i < points.size(); i++)
	{
		points[i].x =dis(gen);
		points[i].y = dis(gen);
	}
}
#endif