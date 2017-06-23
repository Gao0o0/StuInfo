#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"


int cgiMain()
{
  fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
  fprintf(cgiOut, "<head>\n<meta charset=\"utf-8\">\n<title>修改</title>\n<link href=\"https://cdn.bootcss.com/bootstrap/3.3.7/css/bootstrap.min.css\" rel=\"stylesheet\"> ");
  fprintf(cgiOut, "<style type=\"text/css\">body { height: 100%%;background-color: lightblue;}ul li {list-style: none;}.headermargin-bottom: 50px;}.operation>div {     padding: 15px;}.operation.row .text-center button { outline-style: none;}.forms li { display: none;}.forms li button { margin-right: 30px;}</style>\n\n</head>\n");
  char pno[6] = "\0";
	int status = 0;


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


	sprintf(sql, "select  * from school where pno = '%s' and state='1'", pno);
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
    MYSQL_ROW  row;
    row = mysql_fetch_row(res);
  fprintf(cgiOut, "<form class=\"form-horizontal\" method=\"get\" action=\"/cgi-bin/sx/doupdateSch.cgi?ppno=%s\">\n",pno);
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"stuId\" class=\"col-sm-2 control-label\">专业编号</label>\n");
  fprintf(cgiOut, "<div class=\"col-sm-10\"><input type=\"text\" name=\"pno\" class=\"form-control\" id=\"stuId\" value=\"%s\"\n >",row[0]);
  fprintf(cgiOut, "</div>\n</div>\n<div class=\"form-group\">\n<label for=\"name\" class=\"col-sm-2 control-label\">专业名称</label>\n<div class=\"col-sm-10\">\n");
  fprintf(cgiOut, "<input type=\"hidden\" name =\"ppno\" value=\"%s\"/>\n",pno );
  fprintf(cgiOut, "<input type=\"text\" name=\"pname\" class=\"form-control\" id=\"name\" value=\"%s\">\n</div>\n</div>\n",row[1]);
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"birth\" class=\"col-sm-2 control-label\">所在院名称</label>\n<div class=\"col-sm-10\">\n<input type=\"text\" name=\"dname\" class=\"form-control\" id=\"birth\" value=\"%s\">\n</div>\n</div>\n",row[2]);
  fprintf(cgiOut,"<div class=\"text-center\">\n <button  type=\"submit\" class=\"btn btn-success\">提交</button>\n <button type=\"reset\" class=\"btn btn-success\">重置</button> \n</div> \n</form> \n</body> \n</html>");
  return 0;
}
