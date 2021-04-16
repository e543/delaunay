#pragma once
#define IL inline

template<typename F> struct Matrix44
{

	F m00, m01, m02, m03;
	F m10, m11, m12, m13;
	F m20, m21, m22, m23;
	F m30, m31, m32, m33;

	IL Matrix44()
	{
		m00 = 0;
		m01 = 0;
		m02 = 0;
		m03 = 0;
		m10 = 0;
		m11 = 0;
		m12 = 0;
		m13 = 0;
		m20 = 0;
		m21 = 0;
		m22 = 0;
		m23 = 0;
		m30 = 0;
		m31 = 0;
		m32 = 0;
		m33 = 0;
	}

	IL Matrix44(F v00, F v01, F v02, F v03,
		F v10, F v11, F v12, F v13,
		F v20, F v21, F v22, F v23,
		F v30, F v31, F v32, F v33)
	{
		m00 = v00;
		m01 = v01;
		m02 = v02;
		m03 = v03;
		m10 = v10;
		m11 = v11;
		m12 = v12;
		m13 = v13;
		m20 = v20;
		m21 = v21;
		m22 = v22;
		m23 = v23;
		m30 = v30;
		m31 = v31;
		m32 = v32;
		m33 = v33;
	}
	IL void SetIdentity()
	{
		m00 = 1;
		m01 = 0;
		m02 = 0;
		m03 = 0;
		m10 = 0;
		m11 = 1;
		m12 = 0;
		m13 = 0;
		m20 = 0;
		m21 = 0;
		m22 = 1;
		m23 = 0;
		m30 = 0;
		m31 = 0;
		m32 = 0;
		m33 = 1;
	}

	IL Matrix44& Transpose(const Matrix44& m)
	{
		m00 = m.m00;
		m01 = m.m10;
		m02 = m.m20;
		m03 = m.m30;
		m10 = m.m01;
		m11 = m.m11;
		m12 = m.m21;
		m13 = m.m31;
		m20 = m.m02;
		m21 = m.m12;
		m22 = m.m22;
		m23 = m.m32;
		m30 = m.m03;
		m31 = m.m13;
		m32 = m.m23;
		m33 = m.m33;
		return *this;
	}
	IL void Transpose()
	{
		Transpose(Matrix44(*this));
	}

	IL F DeterminantInvert(Matrix44* pInv = 0) const
	{
		F tmp[16];

		tmp[0] = m22 * m33;
		tmp[1] = m32 * m23;
		tmp[2] = m12 * m33;
		tmp[3] = m32 * m13;
		tmp[4] = m12 * m23;
		tmp[5] = m22 * m13;
		tmp[6] = m02 * m33;
		tmp[7] = m32 * m03;
		tmp[8] = m02 * m23;
		tmp[9] = m22 * m03;
		tmp[10] = m02 * m13;
		tmp[11] = m12 * m03;

		tmp[12] = tmp[0] * m11 + tmp[3] * m21 + tmp[4] * m31;
		tmp[12] -= tmp[1] * m11 + tmp[2] * m21 + tmp[5] * m31;
		tmp[13] = tmp[1] * m01 + tmp[6] * m21 + tmp[9] * m31;
		tmp[13] -= tmp[0] * m01 + tmp[7] * m21 + tmp[8] * m31;
		tmp[14] = tmp[2] * m01 + tmp[7] * m11 + tmp[10] * m31;
		tmp[14] -= tmp[3] * m01 + tmp[6] * m11 + tmp[11] * m31;
		tmp[15] = tmp[5] * m01 + tmp[8] * m11 + tmp[11] * m21;
		tmp[15] -= tmp[4] * m01 + tmp[9] * m11 + tmp[10] * m21;

		
		F det = (m00 * tmp[12] + m10 * tmp[13] + m20 * tmp[14] + m30 * tmp[15]);

		if (pInv)
		{
			F rdet = F(1) / det;

			pInv->m00 = tmp[12];
			pInv->m01 = tmp[13];
			pInv->m02 = tmp[14];
			pInv->m03 = tmp[15];
			pInv->m10 = tmp[1] * m10 + tmp[2] * m20 + tmp[5] * m30;
			pInv->m10 -= tmp[0] * m10 + tmp[3] * m20 + tmp[4] * m30;
			pInv->m11 = tmp[0] * m00 + tmp[7] * m20 + tmp[8] * m30;
			pInv->m11 -= tmp[1] * m00 + tmp[6] * m20 + tmp[9] * m30;
			pInv->m12 = tmp[3] * m00 + tmp[6] * m10 + tmp[11] * m30;
			pInv->m12 -= tmp[2] * m00 + tmp[7] * m10 + tmp[10] * m30;
			pInv->m13 = tmp[4] * m00 + tmp[9] * m10 + tmp[10] * m20;
			pInv->m13 -= tmp[5] * m00 + tmp[8] * m10 + tmp[11] * m20;

			
			tmp[0] = m20 * m31;
			tmp[1] = m30 * m21;
			tmp[2] = m10 * m31;
			tmp[3] = m30 * m11;
			tmp[4] = m10 * m21;
			tmp[5] = m20 * m11;
			tmp[6] = m00 * m31;
			tmp[7] = m30 * m01;
			tmp[8] = m00 * m21;
			tmp[9] = m20 * m01;
			tmp[10] = m00 * m11;
			tmp[11] = m10 * m01;

			
			pInv->m20 = tmp[0] * m13 + tmp[3] * m23 + tmp[4] * m33;
			pInv->m20 -= tmp[1] * m13 + tmp[2] * m23 + tmp[5] * m33;
			pInv->m21 = tmp[1] * m03 + tmp[6] * m23 + tmp[9] * m33;
			pInv->m21 -= tmp[0] * m03 + tmp[7] * m23 + tmp[8] * m33;
			pInv->m22 = tmp[2] * m03 + tmp[7] * m13 + tmp[10] * m33;
			pInv->m22 -= tmp[3] * m03 + tmp[6] * m13 + tmp[11] * m33;
			pInv->m23 = tmp[5] * m03 + tmp[8] * m13 + tmp[11] * m23;
			pInv->m23 -= tmp[4] * m03 + tmp[9] * m13 + tmp[10] * m23;
			pInv->m30 = tmp[2] * m22 + tmp[5] * m32 + tmp[1] * m12;
			pInv->m30 -= tmp[4] * m32 + tmp[0] * m12 + tmp[3] * m22;
			pInv->m31 = tmp[8] * m32 + tmp[0] * m02 + tmp[7] * m22;
			pInv->m31 -= tmp[6] * m22 + tmp[9] * m32 + tmp[1] * m02;
			pInv->m32 = tmp[6] * m12 + tmp[11] * m32 + tmp[3] * m02;
			pInv->m32 -= tmp[10] * m32 + tmp[2] * m02 + tmp[7] * m12;
			pInv->m33 = tmp[10] * m22 + tmp[4] * m02 + tmp[9] * m12;
			pInv->m33 -= tmp[8] * m12 + tmp[11] * m22 + tmp[5] * m02;

			
			pInv->m00 *= rdet;
			pInv->m01 *= rdet;
			pInv->m02 *= rdet;
			pInv->m03 *= rdet;
			pInv->m10 *= rdet;
			pInv->m11 *= rdet;
			pInv->m12 *= rdet;
			pInv->m13 *= rdet;
			pInv->m20 *= rdet;
			pInv->m21 *= rdet;
			pInv->m22 *= rdet;
			pInv->m23 *= rdet;
			pInv->m30 *= rdet;
			pInv->m31 *= rdet;
			pInv->m32 *= rdet;
			pInv->m33 *= rdet;
		}

		return det;
	}
	IL void Invert(const Matrix44<F>& m)
	{
		m.DeterminantInvert(this);
	}
	IL void Invert()
	{
		DeterminantInvert(this);
	}

	IL Matrix44<F> GetInverted() const
	{
		Matrix44<F> dst;
		DeterminantInvert(&dst);
		return dst;
	}

	IL F Determinant() const
	{
		return DeterminantInvert();
	}
};




