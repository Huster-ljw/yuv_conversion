#include "yuv_type_conversion.h"
#include <string.h>

/*
	I420	
		Y Y Y Y
		Y Y Y Y
		U U 
		V V
    
	YV12
		Y Y Y Y
		Y Y Y Y
		V V 
		U U

*/

void I420toyv12(char *dst, char *src, int width, int height)
{
	int wh = width * height;
	
	long long cnt = 0;
	
	memcpy(dst, src, wh);
	
	cnt += wh;
	
	for(int i = 0; i < height / 2; ++i)
	{
		for(int j = 0; j < width / 2; ++j)
		{
			dst[cnt++] = src[wh + width  * height / 4 + i * width / 2 + j];
		}
		
	}

	for(int i = 0; i < height / 2; ++i)
	{
		for(int j = 0; j < width / 2; ++j)
		{
			dst[cnt++] = src[wh + i * width / 2 + j];
		}	
	}

}

void yv12toI420(char *dst, char *src, int width, int height)
{
	I420toyv12(dst, src, width, height);
}

/*
	I420	
		Y Y Y Y
		Y Y Y Y
		U U 
		V V
		
	NV12
		Y Y Y Y
		Y Y Y Y
		U V 
		U V

*/
void I420tonv12(char *dst, char *src, int width, int height)
{
	int wh = width * height;
	
	long long cnt = 0;
	
	//Y保持不变
	memcpy(dst, src, wh);

	cnt += wh;
	
	for(int i = 0; i < width / 2; ++i)
	{
		for(int j = 0; j < height / 2; ++j)
		{
			dst[cnt++] = src[wh + i * height / 2 + j];
			dst[cnt++] = src[wh + width * height / 4 + i * height / 2 +j];
		}
	}
}

void nv12toI420(char *dst, char *src, int width, int height)
{
	int wh = width * height;

	long long cnt = 0;

	//Y保持不变
	memcpy(dst, src, wh);

	cnt += wh;


	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width / 2; j += 2)
		{
			dst[cnt++] = src[wh + i * width / 2 + j];
		}

	}

	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width / 2; j += 2)
		{
			dst[cnt++] = src[wh + i * width / 2 + 1 + j];
		}
	}

}


/*
	YV12
		Y Y Y Y
		Y Y Y Y
		V V 
		U U
		
	NV12
		Y Y Y Y
		Y Y Y Y
		U V 
		U V
*/
void yv12tonv12(char *dst_final, char *dst, char *src, int width, int height)
{	
	yv12toI420(dst, src, width, height);
	I420tonv12(dst_final, dst, width, height);

}

void nv12toyv12(char *dst_final, char *dst_tmp, char *src, int width, int height)
{
	nv12toI420(dst_tmp, src, width, height);
	I420toyv12(dst_final, dst_tmp, width, height);

}



/*
	YUV4:2:2 ---> YUV4:2:0  
		Y不变，将U和V信号值在行(垂直方向)在进行一次隔行抽样。 
	YUV4:2:0 ---> YUV4:2:2  
		Y不变，将U和V信号值的每一行分别拷贝一份形成连续两行数据。
		
	YUV422:
	YV16
		Y Y Y Y Y Y Y Y
		Y Y Y Y Y Y Y Y
		U U U U U U U U
		V V V V V V V V
		
	YUV420:
	YV12
		Y Y Y Y
		Y Y Y Y
		Y Y Y Y
		Y Y Y Y
		V V 
		V V
		U U
		U U
*/
void yv16toyv12(char *dst, char *src, int width, int height)
{
	int wh = width * height;

	long long cnt = 0;
	
	/*
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			dst[cnt++] = src[i * width + j];
		}
	}
	*/
	
	memcpy(dst, src, wh);
	
	cnt += wh;
	
	//保存U，如果是奇数行则跳过
	for(int i = 0; i < height / 2; ++i)
	{
		if(i%2 != 0)
		{
			continue;
		}
		for(int j = 0; j < width; ++j)
		{
			dst[cnt++] = src[wh + width * height / 2 + i * width + j];
		}
	}

	//保存V，如果是奇数则跳过
	for(int i = 0; i < height / 2; ++i)
	{
		if(i%2 != 0)
		{
			continue;
		}
		for(int j = 0; j < width; ++j)
		{
			dst[cnt++] = src[wh + i * width + j];
		}
	}
	
	
}

void yv12toyv16(char *dst, char *src, int width, int height)
{
	int wh = width * height;

	long long cnt = 0;
	
	/*
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			dst[cnt++] = src[i * width + j];
		}
	}
	*/
	
	memcpy(dst, src, wh);
	
	cnt += wh;
	
	//保存U
	for(int i = 0; i < height / 2; ++i)
	{
		for(int j = 0; j < width / 2; ++j)
		{
			dst[cnt++] = src[wh + width * height / 4 + i * width / 2 + j];
		}
		
		for(int k = 0; k < width / 2; ++k)
		{
			dst[cnt++] = src[wh + width * height / 4 + i * width / 2 + k];
		}
	}
	
	//保存V
	for(int i = 0; i < height / 2; ++i)
	{
		for(int j = 0; j < width / 2; ++j)
		{
			dst[cnt++] = src[wh + i * width / 2 + j];
			
		}
		
		for(int k = 0; k < width / 2; ++k)
		{
			dst[cnt++] = src[wh + i * width / 2 + k];
		}
	}
 	
}

/*
	YUV422:
	YV16
		Y Y Y Y 
		Y Y Y Y
		Y Y Y Y 
		Y Y Y Y
		U U U U
		U U U U
		V V V V
		V V V V
	
	I420	
		Y Y Y Y
		Y Y Y Y
		Y Y Y Y
		Y Y Y Y
		U U 
		U U 
		V V 
		V V
	
*/


//已测试
void yv16toI420(char *dst_final, char *dst, char *src, int width, int height)
{
	yv16toyv12(dst, src, width, height);
	yv12toI420(dst_final, dst, width, height);
}


void I420toyv16(char *dst, char *src, int width, int height)
{
	int wh = width * height;
	long long cnt = 0;
	
	memcpy(dst, src, wh);
	
	cnt += wh;
	
	//保存U
	for(int i = 0; i < height / 2; ++i)
	{
		for(int j = 0; j < width / 2; ++j)
		{
			dst[cnt++] = src[wh + i * width / 2 + j];
		}
		
		for(int k = 0; k < width / 2; ++k)
		{
			dst[cnt++] = src[wh + i * width / 2 + k];
		}
		
	}
	
	//保存V
	for(int i = 0; i < height / 2; ++i)
	{
		for(int j = 0; j < width / 2; ++j)
		{
			dst[cnt++] = src[wh + width * height / 4 + i * width / 2 + j];
		}
		
		
		for(int k = 0; k < width / 2; ++k)
		{
			dst[cnt++] = src[wh + width * height / 4 + i * width / 2 + k];
		}
		
	}
}


/*
	YUV422:
	YV16
		Y Y Y Y 
		Y Y Y Y
		Y Y Y Y 
		Y Y Y Y
		U U U U 
		U U U U
		V V V V 
		V V V V
	
	YUV420:
	NV12
		Y Y Y Y
		Y Y Y Y
		Y Y Y Y
		Y Y Y Y
		U V 
		U V	
		U V 
		U V
		
*/

void yv16tonv12(char *dst, char *src, int width, int height)
{
	int wh = width * height;
	long long cnt = 0;
	
	memcpy(dst, src, wh);
	
	cnt += wh;
	
	for(int i = 0; i < height / 2; ++i)
	{
		if(i % 2 != 0)
			continue;
		
		for(int j = 0; j < width; ++j)
		{
			dst[cnt++] = src[wh + i * width + j];
			dst[cnt++] = src[wh + width * height / 2 + i * width + j];
			
		}		
	}
	
}


void nv12toyv16(char *dst_final, char *dst, char *src, int width, int height)
{
	nv12toI420(dst, src, width, height);
	I420toyv16(dst_final, dst, width, height);
}














