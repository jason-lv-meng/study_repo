#include <QCoreApplication>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include<QDebug>

#include<curl/curl.h>
#include "CurlHttp.h"

#if  0
# 数据下载时使用
size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p) {
    FILE *fp = (FILE *)user_p;
    size_t return_size = fwrite(buffer, size, nmemb, fp);
    qDebug()<< (char *)buffer << endl;
    return return_size;
}
int curlTest2()
{
    qDebug() << "start";
    // 初始化libcurl
    CURLcode return_code;
    return_code = curl_global_init(CURL_GLOBAL_ALL);
    if (CURLE_OK != return_code) 	{
        qDebug() << "init libcurl failed." << endl;
        return -1;
    }

    // 获取easy handle
    CURL *easy_handle = curl_easy_init();
    if (NULL == easy_handle)
    {
        qDebug()  << "get a easy handle failed." << endl;
        curl_global_cleanup();
        return -1;
    }
    FILE *fp = fopen("d:/data.html", "ab+");
    // 设置easy handle属性
    curl_easy_setopt(easy_handle, CURLOPT_URL, "http://c.biancheng.net/cpp/html/314.html");
    curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, &process_data);
    curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, fp);

    // 执行数据请求
    curl_easy_perform(easy_handle);
    // 释放资源
    fclose(fp);
    curl_easy_cleanup(easy_handle);
    curl_global_cleanup();
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    int b=curlTest2();
    return a.exec();
}
#endif
#include <QFile>

void readFileContent(const QString &file, QByteArray &content)
{
    QFile filePackage(file);
    if (filePackage.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        content = filePackage.readAll();

    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string strReport;
    std::vector<std::string> vecHeader;

//    vecHeader.push_back("Content-Type:application/json;charset=UTF-8");
    vecHeader.push_back("Content-Type:multipart/form-data");
    vecHeader.push_back("token:325ded222bd5ccfec27167ef79474a8c");
//    std::string  serverURL = "http://test79.ubtrobot.com:9009/aimbot-api/sys/login";
    std::string  serverURL = "http://test79.ubtrobot.com:9009/aimbot-api/upload/img";
    QByteArray strParam ;
//      readFileContent("login.txt",strParam);
    readFileContent("upload.jpg",strParam);



    CUrlHttp http;
    http.Request("post",serverURL,strReport,vecHeader,strParam.toStdString());
    qDebug() << "strReport" << QString::fromStdString(strReport);
    return a.exec();
}
