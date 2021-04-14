#include "RunHelper.h"
#undef max
#undef min

int main() {
	RunHelper rh;


	/*Vec3f 
		p1(-1, 0, 1), 
		p2(1, 1, -15),
		p3(-1, 2, 1),
		p4(1, 0, 1);

	Vec3f pd = projPointPlane(p1,p2,p3,p4);

	std::cout << "";*/
	/*Vec3f ccenter(1, 0, 0);
	float rad = 2;
	Vec3f pd(0, 0, 2);
	Vec3f p1, p2;

	LineCircleIntrPoints(p1, p2, ccenter, rad, pd);

	std::cout << std::fixed << p1.x << " " << p1.y << " " << p1.z << std::endl;
	std::cout << std::fixed << p2.x << " " << p2.y << " " << p2.z << std::endl;*/

	/*Vec3f a(1, 1, 0), b(0, 4, 0), c(0, 0, 0);
	Vec3f scenter = CalcCircleBarCenter(a,b,c);

	std::cout << std::endl;
	std::cout << std::fixed << scenter.x << " " << scenter.y << " "  << scenter.z << std::endl;*/
}


































	/*float v00 = 1, v01 = -4, v02 = -3, v03 = -4, v04 = -1,
		v10 = -1, v11 = 1, v12 = -1, v13 = -1, v14 = -1,
		v20 = 4, v21 = 2, v22 = 3, v23 = 4, v24 = 5,
		v30 = -3, v31 = 3, v32 = 3, v33 = 7, v34 = -1,
		v40 = -5, v41 = 4, v42 = -1, v43 = 6, v44 = -2;



		Matrix55 mtr(
			v00, v01, v02, v03, v04,
			v10, v11, v12, v13, v14,
			v20, v21, v22, v23, v24,
			v30, v31, v32, v33, v34,
			v40, v41, v42, v43, v44);

		auto det = mtr.Determinant();
		std::cout << det;*/
