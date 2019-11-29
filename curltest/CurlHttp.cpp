#include "CurlHttp.h"


_CURL_::CurlIntelligence g_curl;

CUrlHttp::CUrlHttp()
{
}
CUrlHttp::~CUrlHttp()
{
}
/* *
 * 	函数： *Request（请求函数） *
         参数： *
         strRequestType：请求类型（get，post） *
         strUrl:请求url地址 *
         strReport：回执信息 *
         strHeader:请求头 *
         strCookie：cookie信息 *
         strCaPath：ca转成pem证书路径 *
         strParam：请求参数（get的时候此参数填空） *
         nTimeOut:超时设置默认是0秒 是无限等待 *
         返回值： *
         0表示成功 非0表示错误代码
*/

int CUrlHttp::Request(std::string strRequestType, std::string strUrl,
                      std::string &strReport, std::vector<std::string> vecHeader,
                      std::string strParam/* ="" */, std::string strCookie/* ="" */,
                      std::string strCaPath/* ="" */, int nTimeOut/* =0 */)
{
    CURL * curl;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
    if ( strRequestType.compare("post")==0 || strRequestType.compare("POST") == 0 )
    {
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, "deac185eeafc6157938fe7c476cb9edf");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strParam.c_str());
    }
    else
    {
        curl_easy_setopt(curl, CURLOPT_POST, 0);//get请求
    }
    //设置http头
    curl_slist * headers = NULL;
    for ( int i=0; i<vecHeader.size(); i++ )
    {
        if (!vecHeader.at(i).empty())
        {
            headers = curl_slist_append(headers, vecHeader.at(i).c_str());
        }
    }
    if (headers != NULL)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    }
    //判断是否有证书
    if(strCaPath.empty())
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    }
    else
    {
        //缺省情况就是PEM，所以无需设置，另外支持DER
        //curl_easy_setopt(curl,CURLOPT_SSLCERTTYPE,"PEM");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_CAINFO, strCaPath.c_str());
    }
    std::string strReportHeader;//回执回来的头数据
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    //可以看到调试信息	//接受服务器的ssl证书而不管合不合法 （相当于命令行中的--insecure）
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    //curl_easy_setopt(curl,CURLOPT_HEADERFUNCTION,_CURL_::write_data);
    //curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &strReportHeader);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _CURL_::write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &strReport);
    if ( nTimeOut > 0  )
    {
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, nTimeOut);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, nTimeOut);
    }
    if (!strCookie.empty())
    {
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, strCookie.c_str());
    }
    CURLcode code = curl_easy_perform(curl);
    if ( headers != NULL )
    {
        curl_slist_free_all(headers);
    }
    curl_easy_cleanup(curl);
    //打印出来//
    std::string strReportData;//
    strReportData.append(strReportHeader);//
    strReportData.append(strReport);//
    printf("request:%s  url:%s report:%s\n", strRequestType.c_str(), strUrl.c_str(), strReportData.c_str());
    return code;
}

