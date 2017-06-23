#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"


int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
  fprintf(cgiOut, "<head>\n<meta charset=\"utf-8\">\n<title>查询结果</title>\n<link href=\"https://cdn.bootcss.com/bootstrap/3.3.7/css/bootstrap.min.css\" rel=\"stylesheet\"> \n</head>");
	fprintf(cgiOut, "<style type=\"text/css\">\nbody {\n height: 100%%;\nbackground-color: lightblue;\n}\n </style>");
	char uid[13] = "\0";
  char pwd[7]="\0"
	int status = 0;

	status = cgiFormString("uid",  uid, 11);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get name error!\n");
		return 1;
	}
  status = cgiFormString("pwd",  pwd, 11);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get name error!\n");
		return 1;
	}

	int ret;
	MYSQL *db;
	char sql[128] = "\0";
	//初始化
	db = mysql_init(NULL);
	mysql_options(db, MYSQL_SET_CHARSET_NAME, "utf8");
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
  sprintf(sql,"select perm from lod where uid='%s' and pwd='%s'",uid,pwd);
  MYSQL_ROW  row;
  row=mysql_fetch_row(res);
  if(row==NULL){
    fprintf(cgiOut, "<a href=\"header.html\">返回</a>", );
    return -1;
  }
  if(strcmp(row[0],"0")){
    fprintf(cgiOut, "欢迎管理员登陆，<a href=\"header.html\">退出</a>");
  }else{
    sprintf(sql, "insert into sessions values('%s')",uid );
    if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
    {
      fprintf(cgiOut, "%s\n", mysql_error(db));
      mysql_close(db);
      return -1;
    }
    fprintf(cgiOut, "%s,欢迎登陆，<a href=\"\">退出</a>",uid);
  }
