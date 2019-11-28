// test_gg.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "http_download_domain.h"

int _tmain(int argc, _TCHAR* argv[])
{
	bool i = 0;
    HttpDownloadDomain hdd(&i);
	hdd.DownloadFile("http://img.ptcms.csdn.net/article/201506/25/558bbe1baed6e.jpg",L"C:\\Users\\apple\\Downloads\\558bbe1baed6e.jpg");
    system("pause");
	return 0;
}


