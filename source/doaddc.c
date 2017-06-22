#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	int status = 0;
	char cno[7]="\0";
	char cname[21]="\0";
	char cpan[7]="\0";
	char num[4]="\0";
	char ceredit[4]="\0";

	status = cgiFormString("cno",  cno, 7);
	//status为0获取成功
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}

	status = cgiFormString("cname",  cname, 21);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cname error!\n");
		return 1;
	}

	status = cgiFormString("cpan",  cpan, 7);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cpan error!\n");
		return 1;
	}

	status = cgiFormString("num",  num, 4);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get num error!\n");
		return 1;
	}
	status = cgiFormString("ceredit",  ceredit, 4);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get ceredit error!\n");
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



	strcpy(sql, "CREATE TABLE course(cno char(6) PRIMARY KEY,cname char(20) UNIQUE NOT NULL,cpan char(6),ceredit SMALLINT CHECK(ceredit>0 and ceredit<10) ,  num SMALLINT DEFAULT 50 CHECK(num >=0) ,state char(1) DEFAULT 1 CHECK(state in ('0','1')),  FOREIGN KEY(cpan) REFERENCES course(cno) )character set utf8");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}
	if(strcmp(cpan,"null")==0){
		sprintf(sql, "insert into course values('%s', '%s', null,%d,%d,'1')", cno, cname, atoi(ceredit),atoi(num));
	}
	else{
		sprintf(sql, "insert into course values('%s', '%s', '%s',%d,%d,'1')", cno, cname, cpan,atoi(ceredit),atoi(num));
	}

	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
	fprintf(cgiOut, "<h3>add student ok!</h3>");
	mysql_close(db);
	return 0;
}
