// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <math.h>
//软渲染器参考：https://github.com/skywind3000/mini3d  
//mini3d笔记：https://zhuanlan.zhihu.com/p/74510058
//图形学流水线文章：https://positiveczp.github.io/%E7%BB%86%E8%AF%B4%E5%9B%BE%E5%BD%A2%E5%AD%A6%E6%B8%B2%E6%9F%93%E7%AE%A1%E7%BA%BF.pdf

/*
 *  1、最简单的渲染流水线:
 *	   分成CPU阶段和GPU阶段
 *      +--------------+     +-------------+
 *      |              |     |             |
 *      |     CPU      +----->     GPU     +
 *      |              |     |             |
 *      +--------------+     +-------------+
 *
 *	2、其中CPU阶段就是Application 应用阶段  GPU阶段包括了几何阶段和光栅化阶段
 *      +--------------+     +-----------------+  +----------------+   +----------------+
 *      |              |     |                 |  |                |   |                |
 *      |   应用阶段   +----->     几何阶段    +-->      光栅化    +--->     像素处理   |
 *      |              |     |                 |  |                |   |                |
 *      +--------------+     +-----------------+  +----------------+   +----------------+
 *
 *  3、几何阶段：
 *
 *		+--------------+     +-----------------+  +------------------+   +-------------+  +-------------+
 *      |              |     |                 |  |                  |   |             |  |             |
 *      |  顶点着色器  +-----> 曲面细分着色器  +-->   几何着色器     +--->    裁剪     |-->  屏幕投射   |
 *      |              |     |                 |  |                  |   |             |  |             |
 *      +--------------+     +-----------------+  +------------------+   +-------------+  +-------------+
 *
 *  4、光栅化阶段：
 *
 *		+--------------+     +--------------+  +------------------+
 *      |              |     |              |  |                  |
 *      |  三角形遍历  +----->  三角形设置  +-->   片元着色器     +
 *      |              |     |              |  |                  |
 *      +--------------+     +--------------+  +------------------+
 *
 *  5、像素处理阶段：
 *		深度测试ZTest
 *		颜色混合
 *      模板测试（模板缓冲）
 *
 *	【说明】：下面的代码根据上面的流水线来讲解和划分
*/




//===========================数学工具 Begin=============================
//插值函数   t为[0,1]之间 
template<typename T>
T Interp(T x1, T x2, T t) { return x1 + (x2 - x1) * t; }

//Clamp函数 Value
template<typename T>
T Clamp(T x, T min, T max) { return (x < min) ? min : ((x > max) ? max : x); }
//===========================数学工具 End===============================


//形状基类
class HShape
{
public:
	virtual void Draw() = 0;
};
class HTexture
{
public:

	//全局纹理（纹理应该跟Shape走 这里先放在这里了）
	int TextureW, TextureH;
	int Texture[256][256];
};
//渲染设备
class  HScreenDevice
{
public:
	//============单例 Begin============
	static HScreenDevice *DeviceInstance;
	static HScreenDevice *GetInstance()
	{
		if (DeviceInstance == NULL)
		{
			DeviceInstance = new HScreenDevice();
		}
		return DeviceInstance;
	}
	//============单例 End============

	//渲染的形状
	HShape *shape;
	HScreenDevice()
	{
		shape = NULL;
	};
	~HScreenDevice()
	{
	};
	//屏幕分辨率宽
	int ScreenWidth;
	//屏幕分辨率高
	int ScreenHeight;
	//屏幕缓冲
	unsigned char* FrameBuff;
	//深度缓冲 绘制过程ZTest ZWrite
	float* DepthBuff;


	void Init(int width, int height)
	{
		//1、屏幕像素分辨率
		ScreenWidth = width;
		ScreenHeight = height;


		//2、屏幕缓冲和深度缓冲 
		FrameBuff = (unsigned char*)malloc(ScreenWidth * ScreenHeight * 4);
		DepthBuff = (float*)malloc(ScreenWidth * ScreenHeight * 4);


		//3、初始化纹理
		TextureW = 256;
		TextureH = 256;
		int i, j;
		for (j = 0; j < TextureH; j++) {
			for (i = 0; i < TextureW; i++) {
				int x = i / 32, y = j / 32;
				Texture[j][i] = ((x + y) & 1) ? 0xffffffff : 0x3fbcefff;
			}
		}
	}

	int RreadTexture(float u, float v) {
		int x, y;
		u = u * TextureW;
		v = v * TextureH;
		x = (int)(u + 0.5f);
		y = (int)(v + 0.5f);
		x = Clamp(x, 0, TextureW - 1);
		y = Clamp(y, 0, TextureH - 1);
		return Texture[y][x];
	}
	//=====================================================================
	// 主绘制函数
	//=====================================================================
	void ClearScreen()
	{
		for (int i = 0; i < ScreenHeight; i++)
		{
			for (int j = 0; j < ScreenWidth; j++)
			{
				//R
				FrameBuff[(i * ScreenWidth + j) * 4] = 0x0;
				//G
				FrameBuff[(i * ScreenWidth + j) * 4 + 1] = 0x0;
				//B
				FrameBuff[(i * ScreenWidth + j) * 4 + 2] = 0x0;
				//A
				FrameBuff[(i * ScreenWidth + j) * 4 + 3] = 0x0;

				//Z buffer 清0
				DepthBuff[i * ScreenWidth + j] = 0.0f;
			}
		}
	}

	//=====================================================================
	// 主绘制函数
	//=====================================================================
	void Draw()
	{
		//1、清理屏幕缓冲
		ClearScreen();
		//2、绘制一个图形
		if (shape)
		{
			shape->Draw();
		}
	}



	//Test 测试把帧缓冲改成红色 测试下是否显示成红色
	void InitTestRed()
	{
		for (int i = 0; i < ScreenHeight; i++)
		{
			for (int j = 0; j < ScreenWidth; j++)
			{
				//R
				FrameBuff[(i * ScreenWidth + j) * 4] = 0xFF;
				//G
				FrameBuff[(i * ScreenWidth + j) * 4 + 1] = 0x0;
				//B
				FrameBuff[(i * ScreenWidth + j) * 4 + 2] = 0x0;
				//A
				FrameBuff[(i * ScreenWidth + j) * 4 + 3] = 0xFF;
			}
		}
	}
};
HScreenDevice* HScreenDevice::DeviceInstance = NULL;

//===========================几何阶段 Begin=============================
//H只是个前缀就跟OpenGL的GL一样
class HMatrix
{
public:
	HMatrix()
	{
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
		m[0][1] = m[0][2] = m[0][3] = 0.0f;
		m[1][0] = m[1][2] = m[1][3] = 0.0f;
		m[2][0] = m[2][1] = m[2][3] = 0.0f;
		m[3][0] = m[3][1] = m[3][2] = 0.0f;
	}
	/*  数据图示
	 *  m[0][0],m[1][0],m[2][0],m[3][0],
	 *  m[0][1],m[1][1],m[2][1],m[3][1],
	 *  m[0][2],m[1][2],m[2][2],m[3][2],
	 *  m[0][3],m[1][3],m[2][4],m[3][3],
	 */
	float m[4][4];
	//矩阵加法
	HMatrix Add(const HMatrix& mat)
	{
		HMatrix matRet;
		int i, j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				matRet.m[i][j] = m[i][j] + mat.m[i][j];
			}
		}
		return matRet;
	}
	//矩阵减法
	HMatrix Sub(const HMatrix& mat)
	{
		HMatrix matRet;
		int i, j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				matRet.m[i][j] = m[i][j] - mat.m[i][j];
			}
		}
		return matRet;
	}
	//矩阵乘法
	HMatrix Mul(const HMatrix& mat)
	{
		HMatrix matRet;
		int i, j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				matRet.m[i][j] = (m[i][0] * mat.m[0][j]) +
					(m[i][1] * mat.m[1][j]) +
					(m[i][2] * mat.m[2][j]) +
					(m[i][3] * mat.m[3][j]);
			}
		}
		return matRet;
	}
	//矩阵缩放
	HMatrix Scale(float f)
	{
		HMatrix matRet;
		int i, j;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				matRet.m[i][j] = m[i][j] * f;
			}
		}
		return matRet;
	}

	bool operator==(const HMatrix& mat)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m[i][j] != mat.m[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	bool operator!=(const HMatrix& mat)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m[i][j] != mat.m[i][j])
				{
					return true;
				}
			}
		}
		return false;
	}

	//补充单元测试
	bool UnitTest()
	{
		HMatrix mat1, mat2, mat3;
		mat1.m[0][0] = 0; mat1.m[1][0] = 0; mat1.m[2][0] = 0; mat1.m[3][0] = 0;
		mat1.m[0][1] = 0; mat1.m[1][1] = 0; mat1.m[2][1] = 0; mat1.m[3][1] = 0;
		mat1.m[0][2] = 0; mat1.m[1][2] = 0; mat1.m[2][2] = 0; mat1.m[3][2] = 0;
		mat1.m[0][3] = 0; mat1.m[1][3] = 0; mat1.m[2][3] = 0; mat1.m[3][3] = 0;

		if (mat1.Add(mat2) != mat3)
		{
			return false;
		}
		return true;
	}
};

//向量或者是点都是这个类便是
class HVector
{
public:
	HVector()
	{
		w = 1;
	}
	HVector(float xp, float yp, float zp, float wp) : x(xp), y(yp), z(zp), w(wp)
	{

	}


	//表示向量时w无用
	float x, y, z, w;

	//向量长度
	float Length() { return sqrt(x * x + y * y + z * z); }

	//向量加法
	HVector Add(const HVector& vec)
	{
		HVector vecRet;
		vecRet.w = 1;
		vecRet.x = x + vec.x;
		vecRet.y = y + vec.y;
		vecRet.z = z + vec.z;
		return vecRet;
	}

	//向量减法
	HVector Sub(const HVector& vec)
	{
		HVector vecRet;
		vecRet.w = 1;
		vecRet.x = x - vec.x;
		vecRet.y = y - vec.y;
		vecRet.z = z - vec.z;
		return vecRet;
	}

	//向量点乘 返回是值 A x B = |A||B|Cos 
	float DotProduct(const HVector& vec)
	{
		return  x * vec.x + y * vec.y + z * vec.z;
	}

	//向量叉乘 返回向量 右手螺旋决定方向
	HVector CrossProduct(const HVector& vec)
	{
		HVector vecRet;
		float m1, m2, m3;
		m1 = y * vec.z - z * vec.y;
		m2 = z * vec.x - x * vec.z;
		m3 = x * vec.y - y * vec.x;
		vecRet.x = m1;
		vecRet.y = m2;
		vecRet.z = m3;
		vecRet.w = 1.0f;
		return vecRet;
	}

	//向量插值
	HVector InterpVec(const HVector& vec, float t)
	{
		HVector vecRet;
		vecRet.x = Interp(x, vec.x, t);
		vecRet.y = Interp(y, vec.y, t);
		vecRet.z = Interp(z, vec.z, t);
		vecRet.w = 1.0;
		return vecRet;
	}

	//向量归一
	HVector Normalize()
	{
		HVector vecRet;
		float len = Length();
		if (len != 0.0f)
		{
			vecRet.x = x / len;
			vecRet.y = y / len;
			vecRet.z = z / len;
		}
		return vecRet;
	}

	//向量乘矩阵
	HVector MulMat(const HMatrix& mat)
	{
		HVector vec;
		float X = x, Y = y, Z = z, W = w;
		vec.x = X * mat.m[0][0] + Y * mat.m[1][0] + Z * mat.m[2][0] + W * mat.m[3][0];
		vec.y = X * mat.m[0][1] + Y * mat.m[1][1] + Z * mat.m[2][1] + W * mat.m[3][1];
		vec.z = X * mat.m[0][2] + Y * mat.m[1][2] + Z * mat.m[2][2] + W * mat.m[3][2];
		vec.w = X * mat.m[0][3] + Y * mat.m[1][3] + Z * mat.m[2][3] + W * mat.m[3][3];
		return vec;
	}

	//检查齐次裁剪坐标 cvv canonical view volume
	bool CheckInCVV()
	{
		int check = 0;
		if (z < 0.0f) check |= 1;
		if (z > w) check |= 2;
		if (x < -w) check |= 4;
		if (x > w) check |= 8;
		if (y < -w) check |= 16;
		if (y > w) check |= 32;
		return check == 0;
	}


};

//获取单位矩阵
static HMatrix GetIdentityMat() {
	HMatrix matRet;
	matRet.m[0][0] = matRet.m[1][1] = matRet.m[2][2] = matRet.m[3][3] = 1.0f;
	matRet.m[0][1] = matRet.m[0][2] = matRet.m[0][3] = 0.0f;
	matRet.m[1][0] = matRet.m[1][2] = matRet.m[1][3] = 0.0f;
	matRet.m[2][0] = matRet.m[2][1] = matRet.m[2][3] = 0.0f;
	matRet.m[3][0] = matRet.m[3][1] = matRet.m[3][2] = 0.0f;
	return matRet;
}

//获取0矩阵
static HMatrix GetZeroMat() {
	HMatrix matRet;
	matRet.m[0][0] = matRet.m[0][1] = matRet.m[0][2] = matRet.m[0][3] = 0.0f;
	matRet.m[1][0] = matRet.m[1][1] = matRet.m[1][2] = matRet.m[1][3] = 0.0f;
	matRet.m[2][0] = matRet.m[2][1] = matRet.m[2][2] = matRet.m[2][3] = 0.0f;
	matRet.m[3][0] = matRet.m[3][1] = matRet.m[3][2] = matRet.m[3][3] = 0.0f;
	return matRet;
}

//获取平移矩阵
static HMatrix GetTranslateMat(float x, float y, float z) {
	HMatrix matRet;
	matRet = GetIdentityMat();
	matRet.m[3][0] = x;
	matRet.m[3][1] = y;
	matRet.m[3][2] = z;
	return matRet;
}

//获取缩放矩阵
static HMatrix GetScaleMat(float x, float y, float z) {
	HMatrix matRet;
	matRet = GetIdentityMat();
	matRet.m[0][0] = x;
	matRet.m[1][1] = y;
	matRet.m[2][2] = z;
	return matRet;
}

//获取旋转矩阵 X轴旋转
// https://blog.csdn.net/csxiaoshui/article/details/65446125
static HMatrix GetRotateMatX(float x) {
	HMatrix matRet = GetIdentityMat();//单位矩阵
	float SinValue = (float)sin(x);
	float CosValue = (float)cos(x);

	matRet.m[0][0] = 1; matRet.m[1][0] = 0;			matRet.m[2][0] = 0;			matRet.m[3][0] = 0;
	matRet.m[0][1] = 0; matRet.m[1][1] = CosValue;	matRet.m[2][1] = -SinValue; matRet.m[3][1] = 0;
	matRet.m[0][2] = 0; matRet.m[1][2] = SinValue;	matRet.m[2][2] = CosValue;	matRet.m[3][2] = 0;
	matRet.m[0][3] = 0; matRet.m[1][3] = 0;			matRet.m[2][3] = 0;			matRet.m[3][3] = 1;

	return matRet;
}

//获取旋转矩阵 Y轴旋转
// https://blog.csdn.net/csxiaoshui/article/details/65446125
static HMatrix GetRotateMatY(float y) {
	HMatrix matRet = GetIdentityMat();//单位矩阵
	float SinValue = (float)sin(y);
	float CosValue = (float)cos(y);

	matRet.m[0][0] = CosValue;	matRet.m[1][0] = 0; matRet.m[2][0] = SinValue;	matRet.m[3][0] = 0;
	matRet.m[0][1] = 0;			matRet.m[1][1] = 1;	matRet.m[2][1] = 0;			matRet.m[3][1] = 0;
	matRet.m[0][2] = -SinValue;	matRet.m[1][2] = 0;	matRet.m[2][2] = CosValue;	matRet.m[3][2] = 0;
	matRet.m[0][3] = 0;			matRet.m[1][3] = 0;	matRet.m[2][3] = 0;			matRet.m[3][3] = 1;

	return matRet;
}

//获取旋转矩阵 Z轴旋转
// https://blog.csdn.net/csxiaoshui/article/details/65446125
static HMatrix GetRotateMatZ(float z) {
	HMatrix matRet = GetIdentityMat();//单位矩阵
	float SinValue = (float)sin(z);
	float CosValue = (float)cos(z);

	matRet.m[0][0] = CosValue; matRet.m[1][0] = -SinValue; matRet.m[2][0] = 0;	matRet.m[3][0] = 0;
	matRet.m[0][1] = SinValue; matRet.m[1][1] = CosValue;  matRet.m[2][1] = 0;	matRet.m[3][1] = 0;
	matRet.m[0][2] = 0;		   matRet.m[1][2] = 0;		   matRet.m[2][2] = 1;	matRet.m[3][2] = 0;
	matRet.m[0][3] = 0;		   matRet.m[1][3] = 0;		   matRet.m[2][3] = 0;	matRet.m[3][3] = 1;

	return matRet;
}

//获取旋转矩阵 XYZ轴旋转
static HMatrix GetRotateMat(float x, float y, float z)
{
	//X Y Z矩阵相乘 这里是为了好理解 但是这样做效率有浪费 6次三角函数 2次矩阵乘法
	HMatrix matRet = GetRotateMatX(x).Mul(GetRotateMatY(y)).Mul(GetRotateMatZ(z));
	return matRet;
}

//获取LookAt矩阵
//相机的位置 相机的看着那个位置（决定相机方向） 相机上方位置
// see:https://zhuanlan.zhihu.com/p/66384929
// Rx Ry Rz 0
// Ux Uy Uz 0
// Dx Dy Dz 0
// 0  0  0  1 相机空间是左手系 
static HMatrix GetLookAtMat(HVector& camera, HVector& at, HVector& up)
{
	HMatrix matRet;
	HVector CameraXAxis, CameraYAxis, CameraZAxis;
	CameraZAxis = at.Sub(camera);
	CameraZAxis = CameraZAxis.Normalize();
	CameraYAxis = up.Normalize();
	CameraXAxis = CameraZAxis.CrossProduct(CameraYAxis);
	CameraXAxis = CameraXAxis.Normalize();

	matRet.m[0][0] = CameraXAxis.x;
	matRet.m[1][0] = CameraXAxis.y;
	matRet.m[2][0] = CameraXAxis.z;
	matRet.m[3][0] = -CameraXAxis.DotProduct(camera);

	matRet.m[0][1] = CameraYAxis.x;
	matRet.m[1][1] = CameraYAxis.y;
	matRet.m[2][1] = CameraYAxis.z;
	matRet.m[3][1] = -CameraYAxis.DotProduct(camera);

	matRet.m[0][2] = CameraZAxis.x;
	matRet.m[1][2] = CameraZAxis.y;
	matRet.m[2][2] = CameraZAxis.z;
	matRet.m[3][2] = -CameraZAxis.DotProduct(camera);

	matRet.m[0][3] = matRet.m[1][3] = matRet.m[2][3] = 0.0f;
	matRet.m[3][3] = 1.0f;
	return matRet;
}

//获取投影矩阵 乘以这个矩阵之后得到的是相机空间的坐标
static HMatrix GetPerspectiveMat(float fovy, float aspect, float zn, float zf)
{
	float fax = 1.0f / (float)tan(fovy * 0.5f);

	HMatrix matRet = GetZeroMat();
	matRet.m[0][0] = (float)(fax / aspect);
	matRet.m[1][1] = (float)(fax);
	matRet.m[2][2] = zf / (zf - zn);
	matRet.m[3][2] = -zn * zf / (zf - zn);
	matRet.m[2][3] = 1;
	return matRet;
}

//描述一个模型的空间坐标转换的过程的类
class HTransform
{
public:
	HTransform()
	{
		Init();
	}

	//Unity 里面就是 Position Rotation Scale来构建这个矩阵 后面这里可以拆分下更好理解
	// ModelMatrix，就是将模型坐标变换到WorldMatrix的Matrix，WorldMatrix = Mt * Mr * Ms  ModleMatrix =  Mt * Mr * Ms
	HMatrix ModleMat;
	// 世界坐标转到视锥体 转成相机坐标 View矩阵做转换
	HMatrix ViewMat;
	// 投影矩阵 视锥体坐标乘以这个投影矩阵 就得到屏幕坐标
	HMatrix ProjectionMat;
	//MVP 矩阵就是 ModleMat *  ViewMat * ProjectionMat
	HMatrix MVPMat;


	// 更新投影矩阵
	void UpdateMVPMat()
	{
		MVPMat = ModleMat.Mul(ViewMat).Mul(ProjectionMat);
	}

	void Init()
	{
		int ScreenWidth = HScreenDevice::GetInstance()->ScreenWidth;
		int ScreenHeight = HScreenDevice::GetInstance()->ScreenHeight;
		ModleMat = GetIdentityMat();
		HVector camera(5, 0, 0, 1);
		HVector at(0, 0, 0, 1);
		HVector up(0, 1, 0, 1);
		ViewMat = GetLookAtMat(
			camera,
			at,
			up
		);
		// fov = 90度 0.5pai
		ProjectionMat = GetPerspectiveMat(3.1415926f * 0.5f, (float)ScreenWidth / (float)ScreenHeight, 1.0f, 500.0f);
		UpdateMVPMat();
	}

	//坐标转换到屏幕坐标
	HVector MulMVPMat(HVector& Origin)
	{
		return Origin.MulMat(MVPMat);
	}

	//归一化 且屏幕坐标
	//宽->
	//高↓
	HVector HomogenizeToScreenCoord(HVector& Origin)
	{
		int ScreenWidth = HScreenDevice::GetInstance()->ScreenWidth;
		int ScreenHeight = HScreenDevice::GetInstance()->ScreenHeight;
		float rhw = 1.0f / Origin.w;
		HVector vecRet;
		vecRet.x = (Origin.x * rhw + 1.0f) * ScreenWidth * 0.5f;
		vecRet.y = (1.0f - Origin.y * rhw) * ScreenHeight * 0.5f;
		vecRet.z = Origin.z * rhw;
		vecRet.w = 1.0f;
		return vecRet;
	}
};
//===========================几何工具 End=============================



//===========================光栅化工具 Begin=============================
//颜色 RGBA
class HColor
{
public:
	float r, g, b, a;
};

//纹理坐标 uc
class HTexcoord
{
public:
	float u, v;
};

//顶点信息
class HVertex
{
public:
	HVector pos;
	HTexcoord uv;
	HColor color;
	float rhw;

	//屏幕坐标的三角形插值的时候要初始化 rhw 做透视校正用 真正取值的时候乘以w 
	void Initrhw()
	{
		rhw = 1.0f / pos.w;

		uv.u *= rhw;
		uv.v *= rhw;

		color.r *= rhw;
		color.g *= rhw;
		color.b *= rhw;
		color.a *= rhw;
	}

	//插值屏幕坐标的顶点信息
	HVertex InterpVertex(HVertex vertex, float t)
	{
		HVertex HVertexRet;
		HVertexRet.pos = pos.InterpVec(vertex.pos, t);
		HVertexRet.uv.u = Interp(uv.u, vertex.uv.u, t);
		HVertexRet.uv.v = Interp(uv.v, vertex.uv.v, t);
		HVertexRet.color.r = Interp(color.r, vertex.color.r, t);
		HVertexRet.color.g = Interp(color.g, vertex.color.g, t);
		HVertexRet.color.b = Interp(color.b, vertex.color.b, t);
		HVertexRet.rhw = Interp(rhw, vertex.rhw, t);
		return HVertexRet;
	}

	// Step 1/d 的步伐 
	HVertex Step(HVertex vertex, float d)
	{
		HVertex HVertexRet;
		if (d == 0.0f)
		{
			HVertexRet;
		}

		float inv = 1.0f / d;
		HVertexRet.pos.x = (vertex.pos.x - pos.x) * inv;
		HVertexRet.pos.y = (vertex.pos.y - pos.y) * inv;
		HVertexRet.pos.z = (vertex.pos.z - pos.z) * inv;
		HVertexRet.pos.w = (vertex.pos.w - pos.w) * inv;
		HVertexRet.uv.u = (vertex.uv.u - uv.u) * inv;
		HVertexRet.uv.v = (vertex.uv.v - uv.v) * inv;
		HVertexRet.color.r = (vertex.color.r - color.r) * inv;
		HVertexRet.color.g = (vertex.color.g - color.g) * inv;
		HVertexRet.color.b = (vertex.color.b - color.b) * inv;
		HVertexRet.rhw = (vertex.rhw - rhw) * inv;

		return HVertexRet;
	}

	//顶点加法
	HVertex Add(HVertex vertex)
	{
		HVertex HVertexRet;
		HVertexRet.pos.x = pos.x + vertex.pos.x;
		HVertexRet.pos.y = pos.y + vertex.pos.y;
		HVertexRet.pos.z = pos.z + vertex.pos.z;
		HVertexRet.pos.w = pos.w + vertex.pos.w;
		HVertexRet.rhw = rhw + vertex.rhw;
		HVertexRet.uv.u = uv.u + vertex.uv.u;
		HVertexRet.uv.v = uv.v + vertex.uv.v;
		HVertexRet.color.r = color.r + vertex.color.r;
		HVertexRet.color.g = color.g + vertex.color.g;
		HVertexRet.color.b = color.b + vertex.color.b;

		return HVertexRet;
	}
};

//边 线段
class HEdge
{
public:
	HVertex v1, v2;
	HVertex v;//临时变量
};

//梯形 有个理论是 所有的三角形都可以拆分成一个平底三角形和平顶三角形
class HTrapezoid
{
public:
	float top, bottom;
	HEdge left, right;
	//根据Y坐标 计算出左右两条边纵坐标等于Y的 顶点
	void CalculateLRVertex(float y)
	{
		float s1 = left.v2.pos.y - left.v1.pos.y;
		float s2 = right.v2.pos.y - right.v1.pos.y;
		float t1 = (y - left.v1.pos.y) / s1;
		float t2 = (y - right.v1.pos.y) / s2;
		left.v = left.v1.InterpVertex(left.v2, t1);
		right.v = right.v1.InterpVertex(right.v2, t1);
	}
	void EdgeInterp(float y) {
		float s1 = left.v2.pos.y - left.v1.pos.y;
		float s2 = right.v2.pos.y - right.v1.pos.y;
		float t1 = (y - left.v1.pos.y) / s1;
		float t2 = (y - right.v1.pos.y) / s2;

		/*
		 *  根据y值左边两个点left v1 v2 插值得到left v  同理right
		 *       /--------\
		 *      /          \
		 *     y------------y
		 *    /              \
		 *   /----------------\
		 *
		 */

		 //根据Y坐标 得到左右两边的点
		left.v = left.v1.InterpVertex(left.v2, t1);
		right.v = right.v1.InterpVertex(right.v2, t2);
	}



};

//光栅化的时候 三角形遍历的时候去生成图元的过程 用扫描线
class HScanline
{
public:
	HVertex v, step;
	float x, y, width;
};

//屏幕三角形
class HTriangle
{
public:
	HTriangle() {}
	HVertex p1, p2, p3;
	int CalculateTrap(HTrapezoid* trapezoid)
	{
		HVertex p;
		float k, x;

		//顶点排序
		if (p1.pos.y > p2.pos.y) p = p1, p1 = p2, p2 = p;
		if (p1.pos.y > p3.pos.y) p = p1, p1 = p3, p3 = p;
		if (p2.pos.y > p3.pos.y) p = p2, p2 = p3, p3 = p;
		if (p1.pos.y == p2.pos.y && p1.pos.y == p3.pos.y) return 0;
		if (p1.pos.x == p2.pos.x && p1.pos.x == p3.pos.x) return 0;

		if (p1.pos.y == p2.pos.y) {	// triangle down
			if (p1.pos.x > p2.pos.x) p = p1, p1 = p2, p2 = p;
			trapezoid[0].top = p1.pos.y;
			trapezoid[0].bottom = p3.pos.y;
			trapezoid[0].left.v1 = p1;
			trapezoid[0].left.v2 = p3;
			trapezoid[0].right.v1 = p2;
			trapezoid[0].right.v2 = p3;
			return (trapezoid[0].top < trapezoid[0].bottom) ? 1 : 0;
		}

		if (p2.pos.y == p3.pos.y) {	// triangle up
			if (p2.pos.x > p3.pos.x) p = p2, p2 = p3, p3 = p;
			trapezoid[0].top = p1.pos.y;
			trapezoid[0].bottom = p3.pos.y;
			trapezoid[0].left.v1 = p1;
			trapezoid[0].left.v2 = p2;
			trapezoid[0].right.v1 = p1;
			trapezoid[0].right.v2 = p3;
			return (trapezoid[0].top < trapezoid[0].bottom) ? 1 : 0;
		}

		trapezoid[0].top = p1.pos.y;
		trapezoid[0].bottom = p2.pos.y;
		trapezoid[1].top = p2.pos.y;
		trapezoid[1].bottom = p3.pos.y;

		k = (p3.pos.y - p1.pos.y) / (p2.pos.y - p1.pos.y);
		x = p1.pos.x + (p2.pos.x - p1.pos.x) * k;

		if (x <= p3.pos.x) {		// triangle left
			trapezoid[0].left.v1 = p1;
			trapezoid[0].left.v2 = p2;
			trapezoid[0].right.v1 = p1;
			trapezoid[0].right.v2 = p3;
			trapezoid[1].left.v1 = p2;
			trapezoid[1].left.v2 = p3;
			trapezoid[1].right.v1 = p1;
			trapezoid[1].right.v2 = p3;
		}
		else {					// triangle right
			trapezoid[0].left.v1 = p1;
			trapezoid[0].left.v2 = p3;
			trapezoid[0].right.v1 = p1;
			trapezoid[0].right.v2 = p2;
			trapezoid[1].left.v1 = p1;
			trapezoid[1].left.v2 = p3;
			trapezoid[1].right.v1 = p2;
			trapezoid[1].right.v2 = p3;
		}
		return 2;
	}
};

//立方体
class HCube :public HShape
{
public:
	HCube() {};
	//坐标变换
	HTransform Transform;
	//mesh
	//8个顶点  前面4个顶点是正方体的前面  后面4个顶点是正方体的后面
	HVertex mesh[8] = {
		{ { -1, -1,  1, 1 }, { 0, 0 }, { 1.0f, 0.2f, 0.2f }, 1 },
		{ {  1, -1,  1, 1 }, { 0, 1 }, { 0.2f, 1.0f, 0.2f }, 1 },
		{ {  1,  1,  1, 1 }, { 1, 1 }, { 0.2f, 0.2f, 1.0f }, 1 },
		{ { -1,  1,  1, 1 }, { 1, 0 }, { 1.0f, 0.2f, 1.0f }, 1 },
		{ { -1, -1, -1, 1 }, { 0, 0 }, { 1.0f, 1.0f, 0.2f }, 1 },
		{ {  1, -1, -1, 1 }, { 0, 1 }, { 0.2f, 1.0f, 1.0f }, 1 },
		{ {  1,  1, -1, 1 }, { 1, 1 }, { 1.0f, 0.3f, 0.3f }, 1 },
		{ { -1,  1, -1, 1 }, { 1, 0 }, { 0.2f, 1.0f, 0.3f }, 1 },
	};
	// 根据左右两边的端点，初始化计算出扫描线的起点和步长
	HScanline GetScanline(HTrapezoid trap, int y) {
		HScanline scanlineRet;
		// 左右两点的 宽度
		float width = trap.right.v.pos.x - trap.left.v.pos.x;
		// 起点X 坐标
		scanlineRet.x = (int)(trap.left.v.pos.x + 0.5f);
		// 宽度
		scanlineRet.width = (int)(trap.right.v.pos.x + 0.5f) - scanlineRet.x;
		// y坐标
		scanlineRet.y = y;
		// 扫描起点
		scanlineRet.v = trap.left.v;
		// 
		if (trap.left.v.pos.x >= trap.right.v.pos.x) scanlineRet.width = 0;
		//计算步伐
		scanlineRet.step = trap.left.v.Step(trap.right.v, width);
		return scanlineRet;
	}


	void DrawScanline(HScanline scanline)
	{
		HScreenDevice* ScreenDevice = HScreenDevice::GetInstance();
		uint32* framebuffer = (uint32*)ScreenDevice->FrameBuff;
		float *zbuffer = ScreenDevice->DepthBuff;

		int x = scanline.x;
		int y = scanline.y;
		int scanlineWidth = scanline.width;
		int ScreenWidth = ScreenDevice->ScreenWidth;
		int ScreenHeight = ScreenDevice->ScreenHeight;

		for (; scanlineWidth > 0; x++, scanlineWidth--) {
			if (x >= 0 && x < ScreenWidth) {
				float rhw = scanline.v.rhw;
				if (rhw >= zbuffer[x + y * ScreenWidth]) {
					float w = 1.0f / rhw;
					zbuffer[x + y * ScreenWidth] = rhw;

					float u = scanline.v.uv.u * w;
					float v = scanline.v.uv.v * w;

					uint32 color = ScreenDevice->RreadTexture(u, v);
					framebuffer[x + y * ScreenWidth] = color;
				}
			}
			scanline.v = scanline.v.Add(scanline.step);
			if (x >= ScreenWidth) break;
		}
	}
	// 主渲染函数
	void DrawTrap(HTrapezoid trap) {
		//HScanline scanline;
		int j, top, bottom;
		top = (int)(trap.top + 0.5f);
		bottom = (int)(trap.bottom + 0.5f);
		for (j = top; j < bottom; j++) {
			if (j >= 0 && j < 1024) {//todo
				//插值得到梯形的腰的两个点
				trap.EdgeInterp((float)j + 0.5f);
				//初始化扫描线
				HScanline scanline = GetScanline(trap, j);
				//绘制扫描线
				DrawScanline(scanline);
			}
		}
	}

	//画三角形 传入的
	void DrawTriangle(HTriangle Triangle)
	{
		HMatrix mat = GetRotateMat(0, 0.8, 0.8);
		Transform.ModleMat = mat;
		Transform.UpdateMVPMat();

		//三角形的坐标乘以MVP矩阵 得到投影坐标（相机空间）
		HVector ProjectP1 = Transform.MulMVPMat(Triangle.p1.pos);
		HVector ProjectP2 = Transform.MulMVPMat(Triangle.p2.pos);
		HVector ProjectP3 = Transform.MulMVPMat(Triangle.p3.pos);
		float w1 = ProjectP1.w;
		float w2 = ProjectP2.w;
		float w3 = ProjectP3.w;
		//裁剪
		if (ProjectP1.CheckInCVV() == false)return;
		if (ProjectP2.CheckInCVV() == false)return;
		if (ProjectP3.CheckInCVV() == false)return;

		//归一化 且得到屏幕坐标
		ProjectP1 = Transform.HomogenizeToScreenCoord(ProjectP1);
		ProjectP2 = Transform.HomogenizeToScreenCoord(ProjectP2);
		ProjectP3 = Transform.HomogenizeToScreenCoord(ProjectP3);

		//三角形坐标转换成屏幕坐标
		Triangle.p1.pos = ProjectP1;
		Triangle.p2.pos = ProjectP2;
		Triangle.p3.pos = ProjectP3;
		Triangle.p1.pos.w = w1;
		Triangle.p2.pos.w = w2;
		Triangle.p3.pos.w = w3;

		//插值初始化
		Triangle.p1.Initrhw();
		Triangle.p2.Initrhw();
		Triangle.p3.Initrhw();

		// 拆分三角形为0-2个梯形，并且返回可用梯形数量
		HTrapezoid traps[2];
		int n = Triangle.CalculateTrap(traps);

		//梯形扫描
		if (n >= 1) DrawTrap(traps[0]);
		if (n >= 2) DrawTrap(traps[1]);
	}

	//画面
	void DrawPlane(int p1_index, int p2_index, int p3_index, int p4_index)
	{
		HVertex p1 = mesh[p1_index];
		HVertex p2 = mesh[p2_index];
		HVertex p3 = mesh[p3_index];
		HVertex p4 = mesh[p4_index];

		//纹理绘制到这个面上面
		p1.uv.u = 0;
		p1.uv.v = 0;

		p2.uv.u = 0;
		p2.uv.v = 1;

		p3.uv.u = 1;
		p3.uv.v = 1;

		p4.uv.u = 1;
		p4.uv.v = 0;
		HTriangle T1;
		T1.p1 = p1;
		T1.p2 = p2;
		T1.p3 = p3;

		HTriangle T2;
		T2.p1 = p3;
		T2.p2 = p4;
		T2.p3 = p1;
		DrawTriangle(T1);
		DrawTriangle(T2);
	}

	//画立方体
	void DrawBox()
	{
		DrawPlane(0, 1, 2, 3);//front
		DrawPlane(7, 6, 5, 4);//behind
		DrawPlane(0, 4, 5, 1);//bottom
		DrawPlane(1, 5, 6, 2);//right
		DrawPlane(2, 6, 7, 3);//top
		DrawPlane(3, 7, 4, 0);//left
	}

	void Draw()
	{
		DrawBox();
	}

};
//===========================光栅化工具 End=============================

//=====实例代码
//1、初始化加一个立方体 HScreenDevice::GetInstance()->shape = new HCube();
//2、绘制				HScreenDevice::GetInstance()->Draw();