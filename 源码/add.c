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

	status = cgiFormString("sno",  sno, 13);
	//status为0获取成功
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sno error!\n");
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
	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

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



	strcpy(sql, "CREATE TABLE information (sno char(12) PRIMARY KEY,sname char(10) NOT NULL,sex CHAR(2) CHECK (sex IN('男','女')),birth date NOT NULL,tel CHAR(11) UNIQUE NOT NULL,adress varchar(50) NOT NULL,pno char(5),FOREIGN KEY (pno) REFERENCES school(pno))character set utf8");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	/*创建表information,如果ret=0,创建表成功，如果ret=1,已经有表，如果ret非0且非1则表示创建失败被。*/
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}
	sprintf(sql, "insert into information values('%s', '%s', '%s','%s','%s','%s','%s','1')", sno, sname, sex,birth,tel,adress,pno);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
	sprintf(sql,"insert into lod(uid) values('%s')",sno);
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
