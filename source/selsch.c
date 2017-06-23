#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"


int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	fprintf(cgiOut, "<head>\n<meta charset=\"utf-8\">\n<title>查询结果</title>\n<link href=\"https://cdn.bootcss.com/bootstrap/3.3.7/css/bootstrap.min.css\" rel=\"stylesheet\"> ");
	fprintf(cgiOut, "<style type=\"text/css\">\nbody {\n height: 100%%;\nbackground-color: lightblue;\n}\n </style>\n</head>");
	char pname[32] = "\0";
	int status = 0;

	status = cgiFormString("pname",  pname, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get pname error!\n");
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
	if (pname[0] == '*')
	{
		sprintf(sql, "select * from school where state='1'");
	}
	else
	{
		sprintf(sql, "select * from school where pname like '%%%s%%' and state='1'" , pname);
	}
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	MYSQL_RES *res;
	res = mysql_store_result(db);
	if (res == NULL)
	{
		fprintf(cgiOut,"mysql_store_result fail:%s\n", mysql_error(db));
		return -1;
	}

	fprintf(cgiOut, "<div class=\"container\" >");

	fprintf(cgiOut,"<table class=\"table table-striped table-bordered\"  style=\"background-color: #E1F5FE;\" ><tr>");
	int i = 0;

	unsigned int fields;
	fields = mysql_num_fields(res);

	MYSQL_FIELD *mysql_filed;
	mysql_filed = mysql_fetch_fields(res);
  fprintf(cgiOut, "<th>专业号</th>\n");
  fprintf(cgiOut, "<th>专业名称</th>\n");
  fprintf(cgiOut, "<th>所在院名称</th>\n");
	fprintf(cgiOut,"<th>操作</th></tr>\n");

	//访问每一条记录的值
	MYSQL_ROW  row;
	unsigned long  *len;
  char sql1[128] = "\0";

	while ((row = mysql_fetch_row(res)) != NULL)
	{
		fprintf(cgiOut,"<tr>");
		len = mysql_fetch_lengths(res);
		for (i = 0; i < fields-1 ; i++)
		{
					fprintf(cgiOut,"<td>%.*s</td>", (int)len[i], row[i]);
		}
		fprintf(cgiOut,"<td><a href=\"/cgi-bin/sx/updateSch.cgi?pno=%.*s\" >修改</a>\n<a href=\"/cgi-bin/sx/deleteSch.cgi?pno=%.*s\" >删除</a></td></tr>",(int)len[0], row[0],(int)len[0], row[0]);
	}
	fprintf(cgiOut,"</table></div>");



	//mysql_close(db);
	return 0;
}
