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
  char sno[13] = "\0";
	int status = 0;


	status = cgiFormString("sno",  sno, 13);
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


	sprintf(sql, "select  * from information where sno = '%s' and state='1'", sno);
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
  fprintf(cgiOut, "<form class=\"form-horizontal\" method=\"get\" action=\"/cgi-bin/sx/doupdatestu.cgi?ssno=%s\">\n",sno);
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"stuId\" class=\"col-sm-2 control-label\">学号</label>\n");
  fprintf(cgiOut, "<div class=\"col-sm-10\"><input type=\"text\" name=\"sno\" class=\"form-control\" id=\"stuId\" value=\"%s\"\n >",row[0]);
  fprintf(cgiOut, "</div>\n</div>\n<div class=\"form-group\">\n<label for=\"name\" class=\"col-sm-2 control-label\">姓名</label>\n<div class=\"col-sm-10\">\n");
fprintf(cgiOut, "<input type=\"text\" name=\"sname\" class=\"form-control\" id=\"name\" value=\"%s\">\n</div>\n</div>\n",row[1]);

fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"sex\" class=\"col-sm-2 control-label\">性别</label>\n<div class=\"col-sm-10\">\n<input type=\"radio\" name=\"sex\" id=\"sex\" value=\"男\"");
  if(strcmp(row[2],"男")==0)
    fprintf(cgiOut, " checked=\"chexked\"");
  fprintf(cgiOut, "/>男\n<input type=\"radio\" name=\"sex\" id=\"sex\" value=\"女\" style=\"  margin-left: 60px;\"");
  if(strcmp(row[2],"女")==0)
    fprintf(cgiOut, " checked=\"chexked\"");
  fprintf(cgiOut, "/>女\n</div>\n</div>\n");
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"birth\" class=\"col-sm-2 control-label\">出生年月</label>\n<div class=\"col-sm-10\">\n<input type=\"text\" name=\"birth\" class=\"form-control\" id=\"birth\" value=\"%s\">\n</div>\n</div>\n",row[3]);
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"tel\" class=\"col-sm-2 control-label\">联系方式</label>\n<div class=\"col-sm-10\">\n<input type=\"text\" name=\"tel\" class=\"form-control\" id=\"tel\" value=\"%s\">\n</div>\n</div>\n",row[4]);
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"adress\" class=\"col-sm-2 control-label\">家庭籍贯</label>\n<div class=\"col-sm-10\">\n<input type=\"text\" name=\"adress\" class=\"form-control\" id=\"adress\" value=\"%s\">\n</div>\n</div>\n",row[5]);
  fprintf(cgiOut, "<input type=\"hidden\" name =\"ssno\" value=\"%s\"/>\n",sno );
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"pno\" class=\"col-sm-2 control-label\">专业</label>\n<div class=\"col-sm-10\">\n");
  char sql1[128] = "\0";

  sprintf(sql1,"select pno,pname from school and state='1'");
  if ((ret = mysql_real_query(db, sql1, strlen(sql1) + 1)) != 0)
  {
    fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
    mysql_close(db);
    return -1;
  }

  MYSQL_RES *res1;
  res1 = mysql_store_result(db);
  if (res1 == NULL)
  {
    fprintf(cgiOut,"mysql_store_result fail:%s\n", mysql_error(db));
    return -1;
  }
  MYSQL_ROW  row1;
  unsigned long  *len1;
  fprintf(cgiOut, "<select name=\"pno\">\n");
  while ((row1 = mysql_fetch_row(res1)) != NULL)
  {
    fprintf(cgiOut,"<option ");
    len1= mysql_fetch_lengths(res1);
    fprintf(cgiOut, "value=\"%.*s\" ",(int)len1[0],row1[0]);
    if(strcmp(row[6],row1[0])==0)
      fprintf(cgiOut, "selected=\"selected\"");
    fprintf(cgiOut, "> %.*s" ,(int)len1[1],row1[1]);
    fprintf(cgiOut,"</option>");
  }
  fprintf(cgiOut, "</select>\n");

  fprintf(cgiOut,"</div> \n</div>\n <div class=\"text-center\">\n <button  type=\"submit\" class=\"btn btn-success\">提交</button>\n <button type=\"reset\" class=\"btn btn-success\">重置</button> \n</div> \n</form> \n</body> \n</html>");
  return 0;
}
