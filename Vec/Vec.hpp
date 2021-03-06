#pragma once

#include <ostream>
#include "../Math/Math.hpp"

namespace F7
{

	template <typename T, int L>
	class Vec_T
	{
	public:
		using value_type = T;
		using self_type = Vec_T;
		static const int N = L;
		Vec_T() {}
		Vec_T(value_type e) { for (int i = 0; i < N; ++i) _v[i] = e; }
		Vec_T(const Vec_T& v) { for (int i = 0; i < N; ++i) _v[i] = v[i]; }

		inline bool isZero() const {
			for (int i = 0; i < N; ++i) 
				if (_v[i] != 0)
					return false;
			return true;
		}
		inline  bool valid() const {
			return _valid(value_type());
		}

		// type dependent function, T = float, double, long double
		inline void makeInvalid() {
			_makeInvalid(value_type());
		}

		inline value_type length2() const {
			value_type res{0};
			for (int i = 0; i < N; ++i) res += _v[i] * _v[i];
			return res;
		}
#pragma warning(push) // when value_type is int, this will have warning 4244
#pragma warning(disable:4244) 
		inline value_type length() const { return Math::sqrt(length2()); }
#pragma warning(pop)

		inline Vec_T& normalize() {
			value_type len = length();
			if (len > 0) {
				auto inv = 1.f / len;
#pragma warning(push) 
#pragma warning(disable:4244) 
				for (int i=0; i<N; ++i)
					_v[i] *= inv;
#pragma warning(pop) 
			}
			return *this;
		}
		inline Vec_T getNormalize() const 
		{
			Vec_T res = *this;
			value_type len = length();
			if (len > 0) {
				auto inv = 1.f / len;
#pragma warning(push) 
#pragma warning(disable:4244) 
				for (int i = 0; i < N; ++i)
					res[i] *= inv;
#pragma warning(pop) 
			}
			return res;
		}

		inline value_type* ptr() { return _v; }
		inline const value_type* ptr() const { return _v; }
		inline value_type* begin() { return _v; }
		inline value_type* end() { return _v + N; }
		inline const value_type* begin() const { return _v; }
		inline const value_type* end() const { return _v + N; }
		inline int size() const { return N; }

		void set(value_type e) { for (int i = 0; i < N; ++i) _v[i] = e; }

		inline operator value_type*() { return _v; }

		inline value_type& operator [](int id) { return _v[id]; }
		inline value_type operator [](int id) const { return _v[id]; }
		friend std::ostream& operator <<(std::ostream& os, const self_type& v) { for (int i = 0; i < N; ++i) { os << v[i] << " "; } return os; }
		
		inline self_type operator +(const self_type& v) const { self_type res; for (int i = 0; i < N; ++i) { res[i] = _v[i] + v[i]; } return res; }
		inline self_type& operator +=(const self_type& v) { for (int i = 0; i < N; ++i) { _v[i] += v[i]; } return *this; }

		inline self_type operator -(const self_type& v) const { self_type res; for (int i = 0; i < N; ++i) { res[i] = _v[i] - v[i]; } return res; }
		inline self_type& operator -=(const self_type& v) { for (int i = 0; i < N; ++i) { _v[i] -= v[i]; } return *this; }
		inline self_type operator -() const { self_type res; for (int i = 0; i < N; ++i) { res[i] = -_v[i]; } return res; }

		inline self_type operator * (value_type e) const { self_type res; for (int i = 0; i < N; ++i) { res[i] = _v[i] * e; } return res; }
		inline self_type& operator *= (value_type e) { for (int i = 0; i < N; ++i) { _v[i] += e; } return *this;  }
		inline value_type operator * (const self_type& v) const { value_type res{0}; for (int i = 0; i < N; ++i) { res *= _v[i] * v[i]; } return res; }

		inline self_type operator / (value_type e) const { self_type res; for (int i = 0; i < N; ++i) { res[i] = _v[i] / e; } return res; }
		inline self_type& operator /= (value_type e) { for (int i = 0; i < N; ++i) { _v[i] /= e; } return *this; }

		inline bool operator == (const self_type& v) const { for (int i = 0; i < N; ++i) { if (_v[i] != v[i]) return false; } return true; }
		inline bool operator != (const self_type& v) const { return !(operator==(v)); }


// 		inline Vec2_T<value_type> xy() { 
// 			if (size() >= 2)
// 				return Vec2_T<value_type>(_v[0], _v[1]);
// 			else
// 				return Vec2_T<value_type>();
// 		}
// 		inline Vec3_T<value_type> xyz() { 
// 			if (size() >= 3)
// 				return Vec3_T<value_type>(_v[0], _v[1], _v[2]);
// 			else
// 				return Vec3_T<value_type>();
// 		}

	protected:
		inline void _makeInvalid(float) {
			for (int i = 0; i < N; ++i)
				_v[i] = FLT_MAX;
		}
		inline void _makeInvalid(double) {
			for (int i = 0; i < N; ++i)
				_v[i] = DBL_MAX;
		}
		inline void _makeInvalid(long double) {
			for (int i = 0; i < N; ++i)
				_v[i] = LDBL_MAX;
		}

		inline bool _valid(float) const {
			bool res = true;
			for (int i = 0; i < N; ++i)
				if (_v[i] == FLT_MAX) {
					res = false;
					break;
				}
			return res;
		}
		inline bool _valid(double) const {
			bool res = true;
			for (int i = 0; i < N; ++i)
				if (_v[i] == DBL_MAX) {
					res = false;
					break;
				}
			return res;
		}
		inline bool _valid(long double) const {
			bool res = true;
			for (int i = 0; i < N; ++i)
				if (_v[i] == LDBL_MAX) {
					res = false;
					break;
				}
			return res;
		}

	protected:
		T _v[N]{};
	};

	template <typename T>
	class Vec2_T: public Vec_T<T, 2>
	{
	public:
		using value_type = T;
		using base_type = Vec_T<T, 2>;
		using self_type = Vec2_T;
		static const int N = 2;
		using base_type::_v;

		Vec2_T() {}
		Vec2_T(value_type e): base_type(e){}
		Vec2_T(value_type e0, value_type e1) { _v[0] = e0, _v[1] = e1; }
		~Vec2_T() {}

		void set(value_type e0, value_type e1) { _v[0] = e0, _v[1] = e1; }

		inline self_type& normalize() {
			value_type len = base_type::length();
			if (len > 0) {
				auto inv = 1.f / len;
#pragma warning(push) 
#pragma warning(disable:4244) 
				for (int i = 0; i < N; ++i)
					_v[i] *= inv;
#pragma warning(pop) 
			}
			return *this;
		}
		inline self_type getNormalize() const
		{
			self_type res = *this;
			value_type len = base_type::length();
			if (len > 0) {
				auto inv = 1.f / len;
#pragma warning(push) 
#pragma warning(disable:4244) 
				for (int i = 0; i < N; ++i)
					res[i] *= inv;
#pragma warning(pop) 
			}
			return res;
		}

		value_type& x() { return _v[0]; }
		value_type& y() { return _v[1]; }
		value_type x() const { return _v[0]; }
		value_type y() const { return _v[1]; }
		Vec2_T xy() const { return *this; }

		value_type& s() { return _v[0]; }
		value_type& t() { return _v[1]; }
		value_type s() const { return _v[0]; }
		value_type t() const { return _v[1]; }
		void s(value_type e) { _v[0] = e; }
		void t(value_type e) { _v[1] = e; }
		Vec2_T st() const { return *this; }
		void st(value_type e0, value_type e1) { s(e0), t(e1); }

		inline self_type operator +(const self_type& v) const {
			self_type res;
			res[0] = _v[0] + v[0];
			res[1] = _v[1] + v[1];
			return res;
		}
		inline self_type& operator +=(const self_type& v) {
			_v[0] += v[0];
			_v[1] += v[1];
			return *this;
		}

		inline self_type operator -(const self_type& v) const {
			self_type res;
			res[0] = _v[0] - v[0];
			res[1] = _v[1] - v[1];
			return res;
		}
		inline self_type& operator -=(const self_type& v) {
			_v[0] -= v[0];
			_v[1] -= v[1];
			return *this;
		}
		inline self_type operator -() const {
			self_type res;
			res[0] = -_v[0];
			res[1] = -_v[1];
			return res;
		}

		inline self_type operator * (value_type e) const {
			self_type res;
			res[0] = _v[0] * e;
			res[1] = _v[1] * e;
			return res;
		}
		inline self_type& operator *= (value_type e) {
			_v[0] *= e;
			_v[1] *= e;
			return *this;
		}
		inline value_type operator * (const self_type& v) const {
			value_type res{ 0 };
			res += _v[0] * v[0];
			res += _v[1] * v[1];
			return res;
		}

		inline self_type operator / (value_type e) const {
			self_type res;
			res[0] = _v[0] / e;
			res[1] = _v[1] / e;
			return res;
		}
		inline self_type& operator /= (value_type e) {
			_v[0] /= e;
			_v[1] /= e;
			return *this;
		}

		//inline bool operator == (const self_type& v) const { for (int i = 0; i < N; ++i) { if (_v[i] != v[i]) return false; } return true; }
		//inline bool operator != (const self_type& v) const { return !(operator==(v)); }
	};


	template <typename T>
	class Vec3_T : public Vec_T<T, 3>
	{
	public:
		using value_type = T;
		using base_type = Vec_T<T, 3>;
		using self_type = Vec3_T;
		static const int N = 3;
		using base_type::_v;

		Vec3_T() {}
		Vec3_T(value_type e) : base_type(e) {}
		Vec3_T(const Vec3_T& v) {
			_v[0] = v[0]; 
			_v[1] = v[1];
			_v[2] = v[2];
		}
		Vec3_T(const base_type& v) : base_type(v) {}
		Vec3_T(value_type e0, value_type e1, value_type e2) { _v[0] = e0, _v[1] = e1, _v[2] = e2; }
		Vec3_T(Vec2_T<value_type> v, value_type e = 0) { _v[0] = v[0], _v[1] = v[1], _v[2] = e; }
		Vec3_T(value_type e, Vec2_T<value_type> v) { _v[0] = e, _v[1] = v[0], _v[2] = v[1]; }
		~Vec3_T() {}

		inline void set(value_type e0, value_type e1, value_type e2) { _v[0] = e0, _v[1] = e1, _v[2] = e2; }
		inline void set(Vec2_T<value_type> v, value_type e = 0) { _v[0] = v[0], _v[1] = v[1], _v[2] = e; }
		inline void set(value_type e, Vec2_T<value_type> v) { _v[0] = e, _v[1] = v[0], _v[2] = v[1]; }
	
		inline self_type& normalize() {
			value_type len = base_type::length();
			if (len > 0) {
				auto inv = 1.f / len;
#pragma warning(push) 
#pragma warning(disable:4244) 
				for (int i = 0; i < N; ++i)
					_v[i] *= inv;
#pragma warning(pop) 
			}
			return *this;
		}
		inline self_type getNormalize() const
		{
			self_type res = *this;
			value_type len = base_type::length();
			if (len > 0) {
				auto inv = 1.f / len;
#pragma warning(push) 
#pragma warning(disable:4244) 
				for (int i = 0; i < N; ++i)
					res[i] *= inv;
#pragma warning(pop) 
			}
			return res;
		}

		inline value_type& x() { return _v[0]; }
		inline value_type& y() { return _v[1]; }
		inline value_type& z() { return _v[2]; }
		inline value_type x() const { return _v[0]; }
		inline value_type y() const { return _v[1]; }
		inline value_type z() const { return _v[2]; }

		inline Vec2_T<value_type> xy() { return Vec2_T<value_type>(_v[0], _v[1]); }
		inline Vec3_T<value_type> xyz() { return *this; }

		inline value_type s() const { return _v[0]; }
		inline value_type t() const { return _v[1]; }
		inline value_type p() const { return _v[2]; }
		inline value_type& s() { return _v[0]; }
		inline value_type& t() { return _v[1]; }
		inline value_type& p() { return _v[2]; }
		inline Vec2_T<value_type> st() { return Vec2_T<value_type>(_v[0], _v[1]); }
		inline Vec3_T<value_type> stp() { return *this; }


		inline operator Vec2_T<value_type>() { return xy(); }

		inline self_type operator +(const self_type& v) const { 
			self_type res; 
			res[0] = _v[0] + v[0];
			res[1] = _v[1] + v[1];
			res[2] = _v[2] + v[2];
			return res; 
		}
		inline self_type& operator +=(const self_type& v) { 
			_v[0] += v[0];
			_v[1] += v[1];
			_v[2] += v[2];
			return *this; 
		}

		inline self_type operator -(const self_type& v) const { 
			self_type res; 
			res[0] = _v[0] - v[0];
			res[1] = _v[1] - v[1];
			res[2] = _v[2] - v[2];
			return res; 
		}
		inline self_type& operator -=(const self_type& v) { 
			_v[0] -= v[0];
			_v[1] -= v[1];
			_v[2] -= v[2];
			return *this; 
		}
		inline self_type operator -() const { 
			self_type res; 
			res[0] = -_v[0];
			res[1] = -_v[1];
			res[2] = -_v[2];
			return res; 
		}

		inline self_type operator * (value_type e) const { 
			self_type res; 
			res[0] = _v[0] * e;
			res[1] = _v[1] * e;
			res[2] = _v[2] * e;
			return res; 
		}
		inline self_type& operator *= (value_type e) { 
			_v[0] *= e;
			_v[1] *= e;
			_v[2] *= e;
			return *this; 
		}
		inline value_type operator * (const self_type& v) const { 
			value_type res{ 0 }; 
			res += _v[0] * v[0];
			res += _v[1] * v[1];
			res += _v[2] * v[2];
			return res; 
		}

		inline self_type operator / (value_type e) const { 
			self_type res; 
			res[0] = _v[0] / e;
			res[1] = _v[1] / e;
			res[2] = _v[2] / e;
			return res; 
		}
		inline self_type& operator /= (value_type e) { 
			_v[0] /= e;
			_v[1] /= e;
			_v[2] /= e;
			return *this; 
		}

		//inline bool operator == (const self_type& v) const { for (int i = 0; i < N; ++i) { if (_v[i] != v[i]) return false; } return true; }
		//inline bool operator != (const self_type& v) const { return !(operator==(v)); }

		inline self_type operator ^ (const self_type& v) const { 
			return Vec3_T(
				_v[1] * v[2] - _v[2] * v[1], 
				_v[2] * v[0] - _v[0] * v[2], 
				_v[0] * v[1] - _v[1] * v[0]); 
		}
	};

	template <typename T>
	class Vec4_T : public Vec_T<T, 4>
	{
	public:
		using value_type = T;
		using base_type = Vec_T<T, 4>;
		using self_type = Vec4_T;
		static const int N = 4;
		using base_type::_v;

		Vec4_T() {}
		Vec4_T(const Vec4_T& v) {
			_v[0] = v[0];
			_v[1] = v[1];
			_v[2] = v[2];
			_v[3] = v[3];
		}
		Vec4_T(base_type v): base_type(v) {}
		Vec4_T(value_type e) : base_type(e) {}
		Vec4_T(value_type e0, value_type e1, value_type e2, value_type e3) { _v[0] = e0, _v[1] = e1, _v[2] = e2, _v[3] = e3; }
		Vec4_T(Vec3_T<value_type> vt3, value_type e3 = 0) { _v[0] = vt3[0], _v[1] = vt3[1], _v[2] = vt3[2], _v[3] = e3; }
		Vec4_T(value_type e0, Vec3_T<value_type> vt3) { _v[0] = e0, _v[1] = vt3[0], _v[2] = vt3[1], _v[3] = vt3[2]; }
		Vec4_T(Vec2_T<value_type> v0, Vec2_T<value_type> v1) { _v[0] = v0[0], _v[1] = v0[1], _v[2] = v1[0], _v[3] = v1[1]; }
		~Vec4_T() {}

		inline void set(value_type e0, value_type e1, value_type e2, value_type e3) { _v[0] = e0, _v[1] = e1, _v[2] = e2, _v[3] = e3; }
		inline void set(Vec3_T<value_type> vt3, value_type e3 = 0) { _v[0] = vt3[0], _v[1] = vt3[1], _v[2] = vt3[2], _v[3] = e3; }
		inline void set(value_type e0, Vec3_T<value_type> vt3) { _v[0] = e0, _v[1] = vt3[0], _v[2] = vt3[1], _v[3] = vt3[2]; }
		inline void set(Vec2_T<value_type> v0, Vec2_T<value_type> v1) { _v[0] = v0[0], _v[1] = v0[1], _v[2] = v1[0], _v[3] = v1[1]; }

		inline self_type& normalize() {
			value_type len = base_type::length();
			if (len > 0) {
				auto inv = 1.f / len;
#pragma warning(push) 
#pragma warning(disable:4244) 
				for (int i = 0; i < N; ++i)
					_v[i] *= inv;
#pragma warning(pop) 
			}
			return *this;
		}
		inline self_type getNormalize() const
		{
			self_type res = *this;
			value_type len = base_type::length();
			if (len > 0) {
				auto inv = 1.f / len;
#pragma warning(push) 
#pragma warning(disable:4244) 
				for (int i = 0; i < N; ++i)
					res[i] *= inv;
#pragma warning(pop) 
			}
			return res;
		}

		inline value_type& x() { return _v[0]; }
		inline value_type& y() { return _v[1]; }
		inline value_type& z() { return _v[2]; }
		inline value_type& w() { return _v[3]; }
		inline value_type x() const { return _v[0]; }
		inline value_type y() const { return _v[1]; }
		inline value_type z() const { return _v[2]; }
		inline value_type w() const { return _v[3]; }
		inline Vec2_T<value_type> xy() { return Vec2_T<value_type>(_v[0], _v[1]); }
		inline Vec3_T<value_type> xyz() { return Vec3_T<value_type>(_v[0], _v[1], _v[2]); }
		inline Vec4_T<value_type> xyzw() { return *this; }


		inline value_type& s() { return _v[0]; }
		inline value_type& t() { return _v[1]; }
		inline value_type& p() { return _v[2]; }
		inline value_type& q() { return _v[3]; }
		inline value_type s() const { return _v[0]; }
		inline value_type t() const { return _v[1]; }
		inline value_type p() const { return _v[2]; }
		inline value_type q() const { return _v[3]; }
		inline Vec2_T<value_type> st() { return Vec2_T<value_type>(_v[0], _v[1]); }
		inline Vec3_T<value_type> stp() { return Vec3_T<value_type>(_v[0], _v[1], _v[2]); }
		inline Vec4_T<value_type> stpq() { return *this; }

		inline operator Vec2_T<value_type>() { return xy(); }
		inline operator Vec3_T<value_type>() { return xyz(); }

		inline self_type operator +(const self_type& v) const {
			self_type res;
			res[0] = _v[0] + v[0];
			res[1] = _v[1] + v[1];
			res[2] = _v[2] + v[2];
			res[3] = _v[3] + v[3];
			return res;
		}
		inline self_type& operator +=(const self_type& v) {
			_v[0] += v[0];
			_v[1] += v[1];
			_v[2] += v[2];
			_v[3] += v[3];
			return *this;
		}

		inline self_type operator -(const self_type& v) const {
			self_type res;
			res[0] = _v[0] - v[0];
			res[1] = _v[1] - v[1];
			res[2] = _v[2] - v[2];
			res[3] = _v[3] - v[3];
			return res;
		}
		inline self_type& operator -=(const self_type& v) {
			_v[0] -= v[0];
			_v[1] -= v[1];
			_v[2] -= v[2];
			_v[3] -= v[3];
			return *this;
		}
		inline self_type operator -() const {
			self_type res;
			res[0] = -_v[0];
			res[1] = -_v[1];
			res[2] = -_v[2];
			res[3] = -_v[3];
			return res;
		}

		inline self_type operator * (value_type e) const {
			self_type res;
			res[0] = _v[0] * e;
			res[1] = _v[1] * e;
			res[2] = _v[2] * e;
			res[3] = _v[3] * e;
			return res;
		}
		inline self_type& operator *= (value_type e) {
			_v[0] *= e;
			_v[1] *= e;
			_v[2] *= e;
			_v[3] *= e;
			return *this;
		}
		inline value_type operator * (const self_type& v) const {
			value_type res{ 0 };
			res += _v[0] * v[0];
			res += _v[1] * v[1];
			res += _v[2] * v[2];
			res += _v[3] * v[3];
			return res;
		}

		inline self_type operator / (value_type e) const {
			self_type res;
			res[0] = _v[0] / e;
			res[1] = _v[1] / e;
			res[2] = _v[2] / e;
			res[3] = _v[3] / e;
			return res;
		}
		inline self_type& operator /= (value_type e) {
			_v[0] /= e;
			_v[1] /= e;
			_v[2] /= e;
			_v[3] /= e;
			return *this;
		}

		//inline bool operator == (const self_type& v) const { for (int i = 0; i < N; ++i) { if (_v[i] != v[i]) return false; } return true; }
		//inline bool operator != (const self_type& v) const { return !(operator==(v)); }
	};

	class Color255;

 	template <typename T>
 	class Color_T: protected Vec4_T<T>
 	{
 	public:
		using value_type = T;
		using base_type = Vec4_T<T>;
		static const int N = 4;
		using base_type::_v;

		Color_T(): Vec4_T<value_type>(Vec3_T<value_type>(0), 1) {}
		Color_T(value_type e0, value_type e1, value_type e2, value_type e3): Vec4_T<value_type>(e0, e1, e2, e3) {}
		Color_T(value_type e, value_type alpha = 1): Vec4_T<value_type>(Vec3_T<value_type>(e), alpha) {}
		Color_T(Vec3_T<value_type> v, value_type alpha = 1) : Vec4_T<value_type>(v, alpha) {}
		Color_T(Vec4_T<value_type> v) : Vec4_T<value_type>(v) {}
 		~Color_T() {}
		/** @brief: make value in [0,1] */
		inline Color_T& normalize() {
			for (auto& e : Vec4_T<value_type>::_v) if (e > 1) e = 1; else if (e < 0) e = 0;
			return *this;
		}
		inline Color255 to255();

 
 		inline value_type& r() { return Vec4_T<value_type>::_v[0]; }
 		inline value_type& g() { return Vec4_T<value_type>::_v[1]; }
 		inline value_type& b() { return Vec4_T<value_type>::_v[2]; }
 		inline value_type& a() { return Vec4_T<value_type>::_v[3]; }
 		inline value_type r() const { return Vec4_T<value_type>::_v[0]; }
 		inline value_type g() const { return Vec4_T<value_type>::_v[1]; }
 		inline value_type b() const { return Vec4_T<value_type>::_v[2]; }
 		inline value_type a() const { return Vec4_T<value_type>::_v[3]; }
 		inline void r(value_type e) { Vec4_T<value_type>::_v[0] = e; }
 		inline void g(value_type e) { Vec4_T<value_type>::_v[1] = e; }
 		inline void b(value_type e) { Vec4_T<value_type>::_v[2] = e; }
 		inline void a(value_type e) { Vec4_T<value_type>::_v[3] = e; }
		
		inline Vec3_T<value_type> rgb() { return Vec3_T<value_type>(Vec4_T<value_type>::_v[0], Vec4_T<value_type>::_v[1], Vec4_T<value_type>::_v[2]); }
		inline Color_T rgba() { return *this; }
		inline void rgb(value_type e0, value_type e1, value_type e2) { Vec4_T<value_type>::_v[0] = e0, Vec4_T<value_type>::_v[1] = e1, Vec4_T<value_type>::_v[2] = e2; }
		inline void rgba(value_type e0, value_type e1, value_type e2, value_type e3) { 
			Vec4_T<value_type>::_v[0] = e0, Vec4_T<value_type>::_v[1] = e1, Vec4_T<value_type>::_v[2] = e2, Vec4_T<value_type>::_v[3] = e3; 
		}
 	};

 	class Color255 : public Vec4_T<int>
 	{
 	public:
		Color255() : Vec4_T<value_type>(Vec3_T<value_type>(0), 255) {}
		Color255(value_type e0, value_type e1, value_type e2, value_type e3) : Vec4_T(e0, e1, e2, e3) {}
		Color255(value_type e, value_type alpha = 255) : Vec4_T<value_type>(Vec3_T<value_type>(e), alpha) {}
		Color255(Vec3_T<value_type> v, value_type alpha = 255) : Vec4_T<value_type>(v, alpha) {}
		Color255(Vec4_T<value_type> v) : Vec4_T<value_type>(v) {}
		~Color255() {}
		inline Color255& normalize255() {
			for (auto& e : Vec4_T<value_type>::_v) if (e > 255) e = 255; else if (e < 0) e = 0;
			return *this;
		}
		inline Color_T<float> normalize() {
			return Color_T<float>(_v[0] / 255.f, _v[1] / 255.f, _v[2] / 255.f, _v[3] / 255.f);
		}
 		
 
 		inline value_type& r() { return _v[0]; }
 		inline value_type& g() { return _v[1]; }
 		inline value_type& b() { return _v[2]; }
 		inline value_type& a() { return _v[3]; }
 		inline value_type r() const { return _v[0]; }
 		inline value_type g() const { return _v[1]; }
 		inline value_type b() const { return _v[2]; }
 		inline value_type a() const { return _v[3]; }
 		inline void r(value_type e) { _v[0] = e; }
 		inline void g(value_type e) { _v[1] = e; }
 		inline void b(value_type e) { _v[2] = e; }
 		inline void a(value_type e) { _v[3] = e; }
		inline Color255 rgba() { return *this; }
		inline void rgb(value_type e0, value_type e1, value_type e2) { _v[0] = e0, _v[1] = e1, _v[2] = e2; }
		inline void rgba(value_type e0, value_type e1, value_type e2, value_type e3) { _v[0] = e0, _v[1] = e1, _v[2] = e2, _v[3] = e3; }
 	};

	template <typename T>
	Color255 F7::Color_T<T>::to255()
	{
		return Color255(
			int(Vec4_T<value_type>::_v[0] * 255),
			int(Vec4_T<value_type>::_v[1] * 255),
			int(Vec4_T<value_type>::_v[2] * 255),
			int(Vec4_T<value_type>::_v[3] * 255));
	}
}