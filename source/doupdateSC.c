#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

  	char cno[7] = "\0";
    char sno[13] = "\0";
    char grade[4] = "\0";
  	int status = 0;


  	status = cgiFormString("cno",  cno,7);
  	if (status != cgiFormSuccess)
  	{
  		fprintf(cgiOut, "get cno error!\n");
  		return 1;
  	}
    status = cgiFormString("sno",  sno,13);
  	if (status != cgiFormSuccess)
  	{
  		fprintf(cgiOut, "get sno error!\n");
  		return 1;
  	}
    status = cgiFormString("grade",grade,7);
  	if (status != cgiFormSuccess)
  	{
  		fprintf(cgiOut, "get cno error!\n");
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
sprintf(sql, "update score set grade=%d where cno='%s' and sno='%s'",atoi(grade), cno,sno);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
	fprintf(cgiOut, "<h3>update ok!</h3>");
	mysql_close(db);
	return 0;
}
