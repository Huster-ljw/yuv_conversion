#ifndef _YUV_TYPE_CONVERSION_
#define _YUV_TYPE_CONVERSION_

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
void I420toyv12(char *dst, char *src, int width, int height);
void yv12toI420(char *dst, char *src, int width, int height);
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
void I420tonv12(char *dst, char *src, int width, int height);
void nv12toI420(char *dst, char *src, int width, int height);

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
void yv12tonv12(char *dst_final, char *dst, char *src, int width, int height);
void nv12toyv12(char *dst_final, char *dst_tmp, char *src, int width, int height);

/*
	YUV4:2:2 ---> YUV4:2:0  
		Y不变，将U和V信号值在行(垂直方向)在进行一次隔行抽样。 
	YUV4:2:0 ---> YUV4:2:2  
		Y不变，将U和V信号值的每一行分别拷贝一份形成连续两行数据。
		
	YUV422:
	YV16
		Y Y Y Y Y Y Y Y
		Y Y Y Y Y Y Y Y
		V V V V V V V V
		U U U U U U U U
		
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
void yv16toyv12(char *dst, char *src, int width, int height);
void yv12toyv16(char *dst, char *src, int width, int height);

/*
	YUV422:
	YV16
		Y Y Y Y Y Y Y Y
		Y Y Y Y Y Y Y Y
		U U U U U U U U
		V V V V V V V V
	
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
void yv16toI420(char *dst_final, char *dst, char *src, int width, int height);
void I420toyv16(char *dst, char *src, int width, int height);

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
void yv16tonv12(char *dst, char *src, int width, int height);
void nv12toyv16(char *dst_final, char *dst, char *src, int width, int height);



#endif