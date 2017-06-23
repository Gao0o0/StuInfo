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
	char sno[13]="\0";
	status = cgiFormString("cno",  cno, 7);
	//status为0获取成功
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}

	status = cgiFormString("sno", sno, 13);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sno error!\n");
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



	strcpy(sql, "CREATE TABLE score( \nsno char(12), \ncno char(6),\n grade SMALLINT CHECK(grade >=0 and grade <=100),\nPRIMARY KEY (sno,cno), \n FOREIGN KEY(sno) REFERENCES information(sno)\non delete cascade \n on update cascade, state char(1) DEFAULT 1 CHECK(state in ('0','1')) \n FOREIGN KEY(cno) REFERENCES course(cno)	on delete cascade \n on update cascade )character set utf8");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}
		sprintf(sql, "insert into score values('%s', '%s',null,'1')", sno,cno);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
	fprintf(cgiOut, "<h3>add ok!</h3>");
	mysql_close(db);
	return 0;
}
