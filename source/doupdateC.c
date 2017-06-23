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
	char cname[32]="\0";
	char cpan[7]="\0";
	char num[4]="\0";
	char ceredit[4]="\0";
  char ccno[7]="\0";

	status = cgiFormString("cno",  cno, 7);
	//status为0获取成功
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}
  status = cgiFormString("ccno",  ccno, 7);
  //status为0获取成功
  if (status != cgiFormSuccess)
  {
    fprintf(cgiOut, "get ccno error!\n");
    return 1;
  }

	status = cgiFormString("cname",  cname, 32);
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
  //修改课程表
  if(strcmp(cpan,"null")==0){
		sprintf(sql, "update course set cno='%s',cname='%s',cpan=null,ceredit=%d,num=%d where cno='%s'", cno, cname, atoi(ceredit),atoi(num),ccno);
  }
  else{
    sprintf(sql, "update course set cno='%s',cname='%s',cpan='%s',ceredit=%d,num=%d where cno='%s'", cno, cname, cpan,atoi(ceredit),atoi(num),ccno);
  }
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
