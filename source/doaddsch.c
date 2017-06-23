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

	status = cgiFormString("pno",  pno, 6);
	//status为0获取成功
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get pno error!\n");
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


	int ret;
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



	strcpy(sql, "CREATE TABLE school(    pno char(5) PRIMARY KEY,    pname char(64) UNIQUE NOT NULL,     dname char(64) NOT NULL,    state char(1) DEFAULT 1 CHECK(state in ('0','1')))character set utf8)");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}
sprintf(sql, "insert into school values('%s', '%s','%s','1')", pno, pname, dname);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
	fprintf(cgiOut, "<h3>add Major ok!</h3>");
	mysql_close(db);
	return 0;
}
