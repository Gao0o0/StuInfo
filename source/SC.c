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
	char sname[11] = "\0";
  char cname[7] = "\0";
	int status = 0;

	status = cgiFormString("sname",  sname, 11);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sname error!\n");
		return 1;
	}
  status = cgiFormString("cname",  cname, 7);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cname error!\n");
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

	strcpy(sql, "create view SC(学号,姓名,课程号,课程名称,成绩)as select\ninformation.sno,information.sname,course.cno,course.cname,score.grade\nfrom course,information,score\nwhere course.cno=score.cno and information.sno=score.sno and score.state='1'");
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

	if (sname[0] == '*' && cname[0]=='*')
	{
		sprintf(sql, "select * from SC");
	}
	else if(sname[0]=='*' && cname[0]!='*')
	{
		sprintf(sql, "select * from SC where 姓名 like '%%%s%%'", sname);
	}
  else if(sname[0]!='*' && cname[0]=='*')
  {
    sprintf(sql, "select * from SC where 课程名称 like '%%%s%%'", cname);
  }
  else
  {
    sprintf(sql, "select * from SC where 课程名称 like '%%%s%%' and 姓名 like '%%%s%%'", cname,sname);
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
	for (i = 0; i < fields ; i++)
	{
		fprintf(cgiOut, "<th>%s</th>", mysql_filed[i].name);
	}
	fprintf(cgiOut,"<th>操作</th></tr>");

	//访问每一条记录的值
	MYSQL_ROW  row;
	unsigned long  *len;

	while ((row = mysql_fetch_row(res)) != NULL)
	{
		fprintf(cgiOut,"<tr>");
		len = mysql_fetch_lengths(res);
		for (i = 0; i < fields ; i++)
		{
			fprintf(cgiOut,"<td>%.*s</td>", (int)len[i], row[i]);
		}
		fprintf(cgiOut, "<td>" );
		if(row[4]==NULL){
			fprintf(cgiOut,"<a href=\"/cgi-bin/sx/updateSC.cgi?sno=%.*s&cno=%s\" >提交成绩</a>\n",(int)len[0], row[0],row[2]);
		}
		fprintf(cgiOut, "<a href=\"/cgi-bin/sx/deleteSC.cgi?sno=%.*s&cno=%s\" >删除</a></td></tr>",(int)len[0], row[0],row[2]);
	}
	fprintf(cgiOut,"</table></div>");



	mysql_close(db);
	return 0;
}
