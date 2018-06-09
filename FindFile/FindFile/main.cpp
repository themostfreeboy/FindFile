#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <atltime.h>

struct data//自定义数据结构
{
	char filename[255];//文件名
	__time64_t time;//文件修改时间
};


struct data mydata[100];
int n;//找到符合要求的数目

bool judge(char filename[255])//判断是否为待查找文件
{
	if(strcmp(filename,"3.txt")==0)//3.txt为测试筛选的文件名
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FindFile(char path[255])//递归查找文件
{
	struct _finddata_t files;
    int File_Handle;
	char firstpath[255];
	strcpy(firstpath,path);
	strcat(firstpath,"\\*.*");
    File_Handle = _findfirst(firstpath,&files);
    if(File_Handle==-1)//文件路径不存在
    {
        printf("error\n");
		return;
	}
	do
	{
		if (files.attrib & _A_SUBDIR)//子目录
		{
			if( (strcmp(files.name,".") != 0 ) &&(strcmp(files.name,"..") != 0))//继续遍历子文件夹
            {
                char newpath[255];
				strcpy(newpath,path);
				strcat(newpath,"\\");
				strcat(newpath,files.name);
                FindFile(newpath);
            }
		}
		else//非子目录
		{
			if(judge(files.name)==true)//为待查找的文件名
		    {
				strcpy(mydata[n].filename,files.name);//文件名
				mydata[n].time=files.time_write;//文件修改时间
			    n++;
		    }
		}
	}while(_findnext(File_Handle,&files)==0);
    _findclose(File_Handle);
}

int cmp(const void *a,const void *b)//快排比较规则
{
	CTime t = CTime::GetCurrentTime();
    CTimeSpan span1=t-(CTime)((*(data*)a).time);//计算当前系统时间与时间a的间隔
	CTimeSpan span2=t-(CTime)((*(data*)b).time);//计算当前系统时间与时间b的间隔
	return span1<span2?1:-1;//按照修改时间升序排列
}

int main()
{
	n=0;
	FindFile(".\\testdata");//.\testdata为测试筛选的文件夹路径
	qsort(mydata,n,sizeof(mydata[0]),cmp);
	for(int i=0;i<n;i++)
	{
		printf("文件名：%s\t",mydata[i].filename);
		printf("修改时间：%s\n",ctime(&mydata[i].time));
	}
	system("pause");
    return 0;
}