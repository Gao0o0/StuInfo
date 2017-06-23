#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"


int cgiMain()
{
  fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
  fprintf(cgiOut, "<head>\n<meta charset=\"utf-8\">\n<title>修改</title>\n<link href=\"https://cdn.bootcss.com/bootstrap/3.3.7/css/bootstrap.min.css\" rel=\"stylesheet\"> ");
  fprintf(cgiOut, "<style type=\"text/css\">body { height: 100%%;background-color: lightblue;}ul li {list-style: none;}.headermargin-bottom: 50px;}.operation>div {     padding: 15px;}.operation.row .text-center button { outline-style: none;}.forms li { display: none;}.forms li button { margin-right: 30px;}</style>\n\n</head>\n");
/*  char sno[13] = "\0";
	int status = 0;


	status = cgiFormString("sno",  sno, 13);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sno error!\n");
		return 1;
	}
*/

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
  /*sprintf(sql, "select * from sessions");
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
  if(row==NULL)
  {
    fprintf(cgiOut, "未登陆，请先登录\n");
    return -1;
  }
  char sno[13]="\0";
  strcpy(sno,row[0]);
*/
  MYSQL_RES *res;
  MYSQL_ROW  row;
  char sno[13]="\0";
  strcpy(sno,"414105010128");
	sprintf(sql, "select  * from information where sno = '%s'", sno);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

  	res = mysql_store_result(db);
  	if (res == NULL)
  	{
  		fprintf(cgiOut,"mysql_store_result fail:%s\n", mysql_error(db));
  		return -1;
  	}
    row = mysql_fetch_row(res);
  fprintf(cgiOut, "<form class=\"form-horizontal\" method=\"get\" action=\"/cgi-bin/sx/doupdatestu.cgi?ssno=%s\">\n",sno);
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"stuId\" class=\"col-sm-2 control-label\">学号</label>\n");
  fprintf(cgiOut, "<div class=\"col-sm-10\"><input type=\"text\" readonly=\"readonly\" name=\"sno\" class=\"form-control\" id=\"stuId\" value=\"%s\"\n >",row[0]);
  fprintf(cgiOut, "</div>\n</div>\n<div class=\"form-group\">\n<label for=\"name\" class=\"col-sm-2 control-label\">姓名</label>\n<div class=\"col-sm-10\">\n");
fprintf(cgiOut, "<input type=\"text\" name=\"sname\" class=\"form-control\" id=\"name\" value=\"%s\">\n</div>\n</div>\n",row[1]);

fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"sex\" class=\"col-sm-2 control-label\">性别</label>\n<div class=\"col-sm-10\">\n<input type=\"text\" readonly=\"readonly\" name=\"sex\" id=\"sex\" value=\"%s\"></div>\n</div>\n",row[2]);
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"birth\" class=\"col-sm-2 control-label\">出生年月</label>\n<div class=\"col-sm-10\">\n<input type=\"text\" name=\"birth\" class=\"form-control\" id=\"birth\" value=\"%s\">\n</div>\n</div>\n",row[3]);
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"tel\" class=\"col-sm-2 control-label\">联系方式</label>\n<div class=\"col-sm-10\">\n<input type=\"text\" name=\"tel\" class=\"form-control\" id=\"tel\" value=\"%s\">\n</div>\n</div>\n",row[4]);
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"adress\" class=\"col-sm-2 control-label\">家庭籍贯</label>\n<div class=\"col-sm-10\">\n<input type=\"text\" name=\"adress\" class=\"form-control\" id=\"adress\" value=\"%s\">\n</div>\n</div>\n",row[5]);
  fprintf(cgiOut, "<input type=\"hidden\" name =\"ssno\" value=\"%s\"/>\n",sno );
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"pno\" class=\"col-sm-2 control-label\">专业</label>\n<div class=\"col-sm-10\">\n");
  char sql1[128] = "\0";

  sprintf(sql1,"select pname from school where pno='%s'",row[6]);
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
  row1 = mysql_fetch_row(res1);
  fprintf(cgiOut, "<input type=\"text\" name=\"pnoo\"  readonly=\"readonly\"  class=\"form-control\" id=\"adress\" value=\"%s\">\n</div>\n</div>\n",row1[0]);
  fprintf(cgiOut,"<input type=\"hidden\" name=\"pno\" value=\"%s\" />",row[6]);
  fprintf(cgiOut,"</div> \n</div>\n <div class=\"text-center\">\n <button  type=\"submit\" class=\"btn btn-success\">修改</button>\n</div> \n</form> \n</body> \n</html>");
  return 0;
}
