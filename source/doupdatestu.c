#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
  int status = 0;
  char sno[13]="\0";//学号
	char sname[11]="\0";//姓名
	char sex[4]="\0";
	char birth[13]="\0";
	char tel[12]="\0";
	char adress[51]="\0";
	char pno[6]="\0";
	char ssno[13]="\0";

	status = cgiFormString("sno",  sno, 13);
	//status为0获取成功
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sno error!\n");
		return 1;
	}

	status = cgiFormString("ssno",  ssno, 13);
	//status为0获取成功
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get ssno error!\n");
		return 1;
	}

	status = cgiFormString("sname",  sname, 11);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sname error!\n");
		return 1;
	}

	status = cgiFormString("sex",  sex, 4);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sex error!\n");
		return 1;
	}

	status = cgiFormString("birth",  birth, 13);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get birth error!\n");
		return 1;
	}

	status = cgiFormString("tel", tel, 12);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get tel error!\n");
		return 1;
	}

	status = cgiFormString("adress",  adress, 51);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get adress error!\n");
		return 1;
	}

	status = cgiFormString("pno",  pno, 6);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get pno error!\n");
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


	sprintf(sql, "update information set sno='%s',sname='%s',sex='%s',birth='%s',tel='%s',adress='%s',pno='%s' where sno = '%s'", sno,sname,sex,birth,tel,adress,pno,ssno);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
	sprintf(sql, "update lod set uid=%s where uid = '%s'", sno,ssno);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "update ok!\n");
	mysql_close(db);

	return 0;
}
