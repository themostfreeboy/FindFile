#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <atltime.h>

struct data//�Զ������ݽṹ
{
	char filename[255];//�ļ���
	__time64_t time;//�ļ��޸�ʱ��
};


struct data mydata[100];
int n;//�ҵ�����Ҫ�����Ŀ

bool judge(char filename[255])//�ж��Ƿ�Ϊ�������ļ�
{
	if(strcmp(filename,"3.txt")==0)//3.txtΪ����ɸѡ���ļ���
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FindFile(char path[255])//�ݹ�����ļ�
{
	struct _finddata_t files;
    int File_Handle;
	char firstpath[255];
	strcpy(firstpath,path);
	strcat(firstpath,"\\*.*");
    File_Handle = _findfirst(firstpath,&files);
    if(File_Handle==-1)//�ļ�·��������
    {
        printf("error\n");
		return;
	}
	do
	{
		if (files.attrib & _A_SUBDIR)//��Ŀ¼
		{
			if( (strcmp(files.name,".") != 0 ) &&(strcmp(files.name,"..") != 0))//�����������ļ���
            {
                char newpath[255];
				strcpy(newpath,path);
				strcat(newpath,"\\");
				strcat(newpath,files.name);
                FindFile(newpath);
            }
		}
		else//����Ŀ¼
		{
			if(judge(files.name)==true)//Ϊ�����ҵ��ļ���
		    {
				strcpy(mydata[n].filename,files.name);//�ļ���
				mydata[n].time=files.time_write;//�ļ��޸�ʱ��
			    n++;
		    }
		}
	}while(_findnext(File_Handle,&files)==0);
    _findclose(File_Handle);
}

int cmp(const void *a,const void *b)//���űȽϹ���
{
	CTime t = CTime::GetCurrentTime();
    CTimeSpan span1=t-(CTime)((*(data*)a).time);//���㵱ǰϵͳʱ����ʱ��a�ļ��
	CTimeSpan span2=t-(CTime)((*(data*)b).time);//���㵱ǰϵͳʱ����ʱ��b�ļ��
	return span1<span2?1:-1;//�����޸�ʱ����������
}

int main()
{
	n=0;
	FindFile(".\\testdata");//.\testdataΪ����ɸѡ���ļ���·��
	qsort(mydata,n,sizeof(mydata[0]),cmp);
	for(int i=0;i<n;i++)
	{
		printf("�ļ�����%s\t",mydata[i].filename);
		printf("�޸�ʱ�䣺%s\n",ctime(&mydata[i].time));
	}
	system("pause");
    return 0;
}