#pragma once

namespace vrt::math {

	template <class T>
	struct Vec2D
	{
		T x_;
		T y_;
	};

	template <class T>
	struct Vec3D
	{
		T x_;
		T y_;
		T z_;
	};

	template<class T>
	T distance(const Vec2D<T>& a, const Vec2D<T>& b);

	template<class T>
	T distance(const Vec3D<T>& a, const Vec3D<T>& b);
}