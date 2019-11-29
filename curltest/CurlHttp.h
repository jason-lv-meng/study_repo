#ifndef CURLHTTP_H
#define CURLHTTP_H

#include <QObject>
#include <vector>
#include <curl/curl.h>
#include <curl/easy.h>


namespace _CURL_{

/**	* buf: 从服务器返回的buffer	* unit: buufer的单位	* bufSize: buffer的大小	* data: 保存从服务器返回的内容	* 注意这个函数会被调用多次	*/
static size_t write_data(void *buf, size_t unit, size_t bufSize, std::string * data)
{

    int size = unit * bufSize;
    char * tmp = (char*)malloc(size + 1);
    memcpy(tmp, buf, size);
    tmp[size] = '\0';
    data->append(tmp);
    free(tmp);
    return size;
}
//智能初始化curl库和释放curl库
class CurlIntelligence
{
public:
    CurlIntelligence()
    {
        curl_global_init(CURL_GLOBAL_ALL);
    }
    ~CurlIntelligence()
    {
        curl_global_cleanup();
    }
};
}
class CUrlHttp
{
public:
    CUrlHttp();
    ~CUrlHttp();
    static int Request(std::string strRequestType,		std::string strUrl,
                       std::string &strReport,				std::vector<std::string> vecHeader,
                       std::string strParam="", 		std::string strCookie="",
                       std::string strCaPath="",		int nTimeOut=0);

};

#endif // CURLHTTP_H
