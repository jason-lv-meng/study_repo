
#ifndef __HTTP_DOWNLOAD_DOMAIN
#define __HTTP_DOWNLOAD_DOMAIN

#include <string>
#include "curl/curl.h"

class HttpDownloadDomain
{
public:
	HttpDownloadDomain(bool* cancel);
	~HttpDownloadDomain();
	bool DownloadFile(std::string url,std::wstring path);
	bool *cancel_;

private:
	
	static size_t DownloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam);
	static int ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
	
};

#endif