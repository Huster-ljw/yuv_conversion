#include "yuv_type_conversion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>

using namespace std;

//改变名字后缀
void replace_postfix(char *dst, char *src, char *postfix)
{
	char *tmp_dst = dst;
	char *tmp_src = src;
	char *tmp_postfix = postfix;

	int src_cnt = strlen(src) + 1;
	int postfix_cnt = strlen(postfix) + 1;

	//printf("scr_cnt is %d\n", src_cnt);

	int i = 0;
	while (src_cnt--)
	{
		if (src[i] == '.')
		{
			break;
		}
		//printf("src[%d] is %c\n", i, src[i]);
		*tmp_dst++ = *tmp_src++;
		++i;
	}
	int j = 0;
	while (postfix_cnt--)
	{
		//printf("postfix[%d] is %c\n", j, postfix[j]);
		*tmp_dst++ = *tmp_postfix++; 
		++j;
	}
	//*dst = '\0';

}

//#define FAKE_TRUE 1
//#define FAKE_FALSE 0

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

//static char *program_name = NULL;

struct param_t
{
    char filename_in[128];
    char filename_out[128];
    char type_in[128];
    char type_out[128];
    int width;
    int height;
    //int output_flag;

};

void yuv_conversion_usage_exit(int status, char *program_name)
{
    if(status != 0)
    {
        fprintf(stderr, "Try '%s --help' for more information\n", program_name);
    }
    else
    {
        printf("Usage: %s \t [OPTION] FILE\n", program_name);
        printf("-i    \t    input file\n");
        printf("-itype\t    intput file type(i420, nv12, yv12, yv16)\n");
        printf("-otype\t    output file type(i420, nv12, yv12, yv16)\n");
        printf("-w    \t    frame width\n");
        printf("-h    \t    frame height\n");
        printf("-o    \t    output file\n");
        printf("-H(--help)\tShow help information\n");
   
    }
    exit(status);
}

int parse_param(int argc, char *argv[], struct param_t *param)
{
    memset(param, 0, sizeof(struct param_t));

    for (int i = 1; i < argc; ++i)
    {
        if (0 == strcmp(argv[i], "-i"))
        {
            memcpy(param->filename_in, argv[i + 1], strlen(argv[i + 1]));
            ++i;
            continue;
        }
        if (0 == strcmp(argv[i], "-o"))
        {
            memcpy(param->filename_out, argv[i + 1], strlen(argv[i + 1]));
            //param.output_flag = FAKE_TRUE;
            //filename_out = filename_out_default;
            ++i;
            continue;
        }
        if (0 == strcmp(argv[i], "-w"))
        {
            param->width = atoi(argv[i + 1]);
            ++i;
            continue;
        }
        if (0 == strcmp(argv[i], "-h"))
        {
            param->height = atoi(argv[i + 1]);
            ++i;
            continue;
        }
        if (0 == strcmp(argv[i], "-itype"))
        {
            memcpy(param->type_in, argv[i + 1], strlen(argv[i + 1]));
            ++i;
            continue;
        }
        if (0 == strcmp(argv[i], "-otype"))
        {
            memcpy(param->type_out, argv[i + 1], strlen(argv[i + 1]));
            ++i;
            continue;
        }
        if (0 == strcmp(argv[i], "-H") || 0 == strcmp(argv[i], "--help"))
        {
            yuv_conversion_usage_exit(EXIT_SUCCESS, argv[0]);
        }
          
    }

    if (param->width == 0 || param->height == 0 || param->type_in[0] == '\0' 
            || param->type_out[0] == '\0' || param->filename_in[0] == '\0')
    {
        yuv_conversion_usage_exit(EXIT_FAILURE, argv[0]);
        return -1;
    }
    
    return 0;
}



int main(int argc, char *argv[])
{
	struct param_t param;
	
    printf("%s\n", argv[0]);

    char yuv_i[] = "i420";
    char yv12[] = "yv12";
    char nv12[] = "nv12";
    char yv16[] = "yv16"; 
	char postfix[] = "_out.yuv";
	//const int len = strlen(param.filename_in) + 6;
	
    //char filename_out_default[len] = "filename_default.yuv";
	//char *filename_out_default = (char*)malloc(strlen(param.filename_in) + strlen(postfix) + 1);
	
	//memcpy(filename_out_default, param.filename_in, strlen(param.filename_in) + 1);
	//strcat(filename_out_default, postfix);
    
    //param.output_flag = FAKE_FALSE;
    //strcpy(param.filename_out_default, "filename_default.yuv");


    if(parse_param(argc, argv, &param) < 0)
        exit(-1);

    if (param.filename_out[0] == '\0')
    {
	replace_postfix(param.filename_out, param.filename_in, postfix);
    	//memcpy(param.filename_out, filename_out_default, strlen(filename_out_default) + 1);
        printf("default name\n");
    }

    printf("filename_in is %s\n", param.filename_in);
    printf("filename_out is %s\n", param.filename_out);
    printf("yuv_type_in %s\n", param.type_in);
    printf("yuv_type_out %s\n", param.type_out);
    printf("width is %d\n", param.width);
    printf("height is %d\n", param.height);

   
    FILE *file = fopen(param.filename_in, "rb");
    FILE *file_out = fopen(param.filename_out, "wb");

    //FILE *temp_f = file;
    fseek(file, 0L, SEEK_END);	
    long long file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    long size_f = param.width * param.height * 3 / 2;
    long size_yv16 = param.width * param.height * 2;
        

    int cout_time;
    if(!strcmp(param.type_in, yv16))
    {
        cout_time = file_size / size_yv16;
    }
    else
    {
        cout_time = file_size / size_f;
    }
    printf("frame numbers:%d\n", cout_time);

    //long long file_index = size_f;
    char *dest_yuv = NULL;// = (char*)malloc(size_f);
    char *src_yuv = NULL;// = (char*)malloc(size_f);
    char *tmp_yuv = NULL;// = (char*)malloc(size_f);

/*
    char *dest_yv16 = (char*)malloc(size_yv16);
    char *src_yv16 = (char*)malloc(size_yv16);
    char *tmp_yv16 = (char*)malloc(size_yv16);
*/

    int count_num = 0;
    int read_num;

    while(1)
    {
        if(!strcmp(param.type_in, yv16))
        {
            if(src_yuv == NULL)
            {
                src_yuv = (char*)malloc(size_yv16);
            }
            
            if(dest_yuv == NULL)
            {
                dest_yuv = (char*)malloc(size_f);
            }
            
            if(tmp_yuv == NULL)
            {
                tmp_yuv = (char*)malloc(size_f);
            }

            memset(dest_yuv, 0, size_f);
            read_num = fread(src_yuv, size_yv16, 1, file);
            
            if (read_num != 1)
            {
                break;
            }
            //yv16 to yv12
            if (!strcmp(param.type_in, yv16) && !strcmp(param.type_out, yv12))
            {
                yv16toyv12(dest_yuv, src_yuv, param.width, param.height);
            }
			
			//yv16 to nv12
	    if (!strcmp(param.type_in, yv16) && !strcmp(param.type_out, nv12))
            {
                yv16tonv12(dest_yuv, src_yuv, param.width, param.height);
            }

            //yv16 to I420
            if (!strcmp(param.type_in, yv16) && !strcmp(param.type_out, yuv_i))
            {
                yv16toI420(dest_yuv, tmp_yuv, src_yuv, param.width, param.height);
            }

            ++count_num;

            //fseek(file_out, 0, SEEK_END);
            fwrite(dest_yuv, size_f, 1, file_out);

        }
        else if(!strcmp(param.type_out, yv16))
        {
            if (dest_yuv == NULL)
            {
                dest_yuv = (char*)malloc(size_yv16);
            }
            
            if (src_yuv == NULL)
            {
                src_yuv = (char*)malloc(size_f);
            }
			
			if (tmp_yuv == NULL)
            {
                tmp_yuv = (char*)malloc(size_f);
            }

            memset(dest_yuv, 0, size_yv16);
            read_num = fread(src_yuv, size_f, 1, file);
            
            if (read_num != 1)
            {
                break;
            }

            //yv12 to yv16
            if (!strcmp(param.type_in, yv12) && !strcmp(param.type_out, yv16))
            {                
                yv12toyv16(dest_yuv, src_yuv, param.width, param.height);
            }
            
			//i420 to yv16
			if (!strcmp(param.type_in, yuv_i) && !strcmp(param.type_out, yv16))
			{
				I420toyv16(dest_yuv, src_yuv, param.width, param.height);
			}
			
			//nv12 to yv16
			if (!strcmp(param.type_in, nv12) && !strcmp(param.type_out, yv16))
			{
				nv12toyv16(dest_yuv, tmp_yuv, src_yuv, param.width, param.height);
			}
            ++count_num;

            //fseek(file_out, 0, SEEK_END);
            fwrite(dest_yuv, size_yv16, 1, file_out);
        }
        else
        {
            if (src_yuv == NULL)
            {
                src_yuv = (char*)malloc(size_f);
            }
            
            if (dest_yuv == NULL)
            {
                dest_yuv = (char*)malloc(size_f);
            }
            
            if (tmp_yuv == NULL)
            {
                tmp_yuv = (char*)malloc(size_f);
            }
            
            memset(dest_yuv, 0, size_f);
            read_num = fread(src_yuv, size_f, 1, file);
            
            if (read_num != 1)
            {
                break;
            }
       
            //i420 to yv12
            if (!strcmp(param.type_in, yuv_i) && !strcmp(param.type_out, yv12))
            {
                I420toyv12(dest_yuv, src_yuv, param.width, param.height);
            }

            //yv12 to i420
            if (!strcmp(param.type_in, yv12) && !strcmp(param.type_out, yuv_i))
            {
                yv12toI420(dest_yuv, src_yuv, param.width, param.height);
            }

            //i420 to nv12
            if (!strcmp(param.type_in, yuv_i) && !strcmp(param.type_out, nv12))
            {
                I420tonv12(dest_yuv, src_yuv, param.width, param.height);
            }

            //nv12 to i420
            if (!strcmp(param.type_in, nv12)&& !strcmp(param.type_out, yuv_i))
            {
                nv12toI420(dest_yuv, src_yuv, param.width, param.height);
            }

            //yv12 to nv12
            if (!strcmp(param.type_in, yv12)&& !strcmp(param.type_out, nv12))
            {
                yv12tonv12(dest_yuv, tmp_yuv, src_yuv, param.width, param.height);
            }

            //nv12 to yv12
            if (!strcmp(param.type_in, nv12)&& !strcmp(param.type_out, yv12))
            {
                nv12toyv12(dest_yuv, tmp_yuv, src_yuv, param.width, param.height);
            }

            ++count_num;

            //fseek(file_out, 0, SEEK_END);
            fwrite(dest_yuv, size_f, 1, file_out);
        }
     
    }

    if(file != NULL)
    {
        fclose(file);   
    }
    
    if(file_out != NULL)
    {
        fclose(file_out);   
    }
    
    if(dest_yuv != NULL)
    {
        free(dest_yuv);
        dest_yuv = NULL;
    }
    
    if(src_yuv != NULL)
    {
        free(src_yuv);
        src_yuv = NULL;
    }

    if(tmp_yuv != NULL)
    {
        free(tmp_yuv);
        tmp_yuv = NULL;
    }


    printf("work is done\n");

    return 0;
}

