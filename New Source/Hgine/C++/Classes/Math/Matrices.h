

#pragma once

#include "../../../Includes.h"

namespace sur
{
	struct Mat2x2
	{
		f32 m[2][2] = { 0.f };

		Mat2x2() = default;

		// { a | b }
		// { c | d }
		Mat2x2(f32 a, f32 b, f32 c, f32 d)
		{
			m[0][0] = a;
			m[1][0] = b;
			m[0][1] = c;
			m[1][1] = d;
		}

		Mat2x2(const Mat2x2& other)
		{
			m[0][0] = other.m[0][0];
			m[1][0] = other.m[1][0];
			m[0][1] = other.m[0][1];
			m[1][1] = other.m[1][1];
		}

		Vec2f multiplyWithVector(const Vec2f& other)
		{
			return
			{
				(m[0][0] * other.x + m[1][0] * other.y),
				(m[0][1] * other.x + m[1][1] * other.y)
			};
		}

		void multiplyWithMatrix(const Mat2x2& other)
		{
			Mat2x2 res;
			for (int c = 0; c < 2; c++)
			{
				for (int r = 0; r < 2; r++)
				{
					res.m[c][r] = m[0][r] * other.m[c][0] +
						m[1][r] * other.m[c][1];
				}
			}
			*this = res;
		}

		void toIdentity()
		{
			m[0][0] = 1.f;
			m[1][0] = 0.f;
			m[0][1] = 0.f;
			m[1][1] = 1.f;
		}

		// { a | b }
		// { c | d }
		void operator()(f32 a, f32 b, f32 c, f32 d)
		{
			m[0][0] = a;
			m[1][0] = b;
			m[0][1] = c;
			m[1][1] = d;
		}

		friend std::ostream& operator<<(std::ostream& os, const Mat2x2& mat)
		{
			os <<  "{ " << mat.m[0][0] << " " << mat.m[1][0] << " }"
				<< "\n"
				<< "{ " << mat.m[0][1] << " " << mat.m[1][1] << " }";
			return os;
		}
	};

	struct Mat3x3
	{
		f32 m[3][3] = { 0.f };

		Mat3x3() = default;

		// { a | b | c }
		// { d | e | f }
		// { g | h | i }
		Mat3x3(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h, f32 i) 
		{
			m[0][0] = a;
			m[1][0] = b;
			m[2][0] = c;
			m[0][1] = d;
			m[1][1] = e;
			m[2][1] = f;
			m[0][2] = g;
			m[1][2] = h;
			m[2][2] = i;
		} 

		Mat3x3(const Mat3x3& other) 
		{
			m[0][0] = other.m[0][0];
			m[1][0] = other.m[1][0];
			m[2][0] = other.m[2][0];
			m[0][1] = other.m[0][1];
			m[1][1] = other.m[1][1];
			m[2][1] = other.m[2][1];
			m[0][2] = other.m[0][2];
			m[1][2] = other.m[1][2];
			m[2][2] = other.m[2][2];
		}

		// { a | b | c }
		// { d | e | f }
		// { g | h | i }
		void operator()(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h, f32 i)
		{
			m[0][0] = a;
			m[1][0] = b;
			m[2][0] = c;
			m[0][1] = d;
			m[1][1] = e;
			m[2][1] = f;
			m[0][2] = g;
			m[1][2] = h;
			m[2][2] = i;
		}

		Vec3f multiplyWithVector(const Vec3f& vec)
		{
			return
			{
				m[0][0] * vec.x + m[1][0] * vec.y + m[2][0] * vec.z,
				m[0][1] * vec.x + m[1][1] * vec.y + m[2][1] * vec.z,
				m[0][2] * vec.x + m[1][2] * vec.y + m[2][2] * vec.z
			};
		}

		Vec2f Forward2D(const Vec2f& vec) 
		{
			return
			{
				m[0][0] * vec.x + m[1][0] * vec.y + m[2][0],
				m[0][1] * vec.x + m[1][1] * vec.y + m[2][1]
			};
		}

		void multiplyWithMatrix(const Mat3x3& other)
		{
			Mat3x3 res;
			for (int c = 0; c < 3; c++)
			{
				for (int r = 0; r < 3; r++)
				{
					res.m[c][r] = m[0][r] * other.m[c][0] +
						m[1][r] * other.m[c][1] +
						m[2][r] * other.m[c][2];
				}
			}
			*this = res;
		}

		void toIdentity()
		{
			operator()(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
		}

		f32 determinant() {
			return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
				m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) +
				m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
		}

		void invert()
		{
			f32 idet = 1.f / determinant();

			Mat3x3 tmp(*this);
			m[0][0] = (tmp.m[1][1] * tmp.m[2][2] - tmp.m[1][2] * tmp.m[2][1]) * idet;
			m[1][0] = (tmp.m[2][0] * tmp.m[1][2] - tmp.m[1][0] * tmp.m[2][2]) * idet;
			m[2][0] = (tmp.m[1][0] * tmp.m[2][1] - tmp.m[2][0] * tmp.m[1][1]) * idet;
			m[0][1] = (tmp.m[2][1] * tmp.m[0][2] - tmp.m[0][1] * tmp.m[2][2]) * idet;
			m[1][1] = (tmp.m[0][0] * tmp.m[2][2] - tmp.m[2][0] * tmp.m[0][2]) * idet;
			m[2][1] = (tmp.m[0][1] * tmp.m[2][0] - tmp.m[0][0] * tmp.m[2][1]) * idet;
			m[0][2] = (tmp.m[0][1] * tmp.m[1][2] - tmp.m[0][2] * tmp.m[1][1]) * idet;
			m[1][2] = (tmp.m[0][2] * tmp.m[1][0] - tmp.m[0][0] * tmp.m[1][2]) * idet;
			m[2][2] = (tmp.m[0][0] * tmp.m[1][1] - tmp.m[0][1] * tmp.m[1][0]) * idet;
		}

		void rotate(i32 angle, bool ImC)
		{
			Mat3x3 tmp;
			tmp.m[0][0] = cosf(angle * PI / 180);  tmp.m[1][0] = sinf(angle * PI / 180); tmp.m[2][0] = 0.0f;
			tmp.m[0][1] = -sinf(angle * PI / 180); tmp.m[1][1] = cosf(angle * PI / 180); tmp.m[2][1] = 0.0f;
			tmp.m[0][2] = 0.0f;			 tmp.m[1][2] = 0.0f;		 tmp.m[2][2] = 1.0f;
			if (ImC) {
				tmp.multiplyWithMatrix(*this);
				*this = tmp;
			}
			else
				multiplyWithMatrix(tmp);
		}

		void translate(Vec2f offset, bool ImC)
		{
			Mat3x3 tmp;
			tmp.m[0][0] = 1.0f; tmp.m[1][0] = 0.0f; tmp.m[2][0] = offset.x;
			tmp.m[0][1] = 0.0f; tmp.m[1][1] = 1.0f; tmp.m[2][1] = offset.y;
			tmp.m[0][2] = 0.0f;	tmp.m[1][2] = 0.0f;	tmp.m[2][2] = 1.0f;
			if (ImC) {
				tmp.multiplyWithMatrix(*this);
				*this = tmp;
			}
			else
				multiplyWithMatrix(tmp);
		}

		friend std::ostream& operator<<(std::ostream& os, const Mat3x3& mat)
		{
			os << "{ " << mat.m[0][0] << " " << mat.m[1][0] << " " << mat.m[2][0] << " }"
				<< "\n"
				<< "{ " << mat.m[0][1] << " " << mat.m[1][1] << " " << mat.m[2][1] << " }"
				<< "\n"
				<< "{ " << mat.m[0][2] << " " << mat.m[1][2] << " " << mat.m[2][2] << " }";
			return os;
		}
	};
}
