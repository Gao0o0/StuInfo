#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	int status = 0;
	char pno[6]="\0";
	char pname[64]="\0";
	char dname[64]="\0";
  char ppno[6]="\0";

	status = cgiFormString("pno",  pno, 6);
	//status为0获取成功
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get pno error!\n");
		return 1;
	}
  status = cgiFormString("ppno",  ppno, 6);
	//status为0获取成功
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get ppno error!\n");
		return 1;
	}

	status = cgiFormString("pname",  pname, 64);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get pname error!\n");
		return 1;
	}

	status = cgiFormString("dname",  dname, 64);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get dname error!\n");
		return 1;
	}

	char sql[128] = "\0";
	MYSQL *db;

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
sprintf(sql, "update school set pno='%s',pname='%s',dname='%s' where pno='%s'", pno, pname, dname,ppno);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
	fprintf(cgiOut, "<h3>update Major ok!</h3>");
	mysql_close(db);
	return 0;
}
