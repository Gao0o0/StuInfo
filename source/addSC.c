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
  fprintf(cgiOut, "<body>\n");
  fprintf(cgiOut, "<form class=\"form-horizontal\" method=\"get\" action=\"/cgi-bin/sx/doaddSC.cgi\">\n");
  fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"pno\" class=\"col-sm-2 control-label\">学生</label>\n<div class=\"col-sm-10\">\n");

  int ret;
  MYSQL *db;
  char sql[128] = "\0";
  char sql1[128] = "\0";
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


  	sprintf(sql, "select  sno,sname from information where state='1'");
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
      fprintf(cgiOut, "<select name=\"sno\">\n");
      while ((row = mysql_fetch_row(res)) != NULL)
      {
        fprintf(cgiOut,"<option ");
        fprintf(cgiOut, "value=\"%s\"> %s" ,row[0],row[1]);
        fprintf(cgiOut,"</option>");
      }
        fprintf(cgiOut, "</select>\n</div> \n</div>\n");
      fprintf(cgiOut, "<div class=\"form-group\">\n<label for=\"pno\" class=\"col-sm-2 control-label\">课程</label>\n<div class=\"col-sm-10\">\n");
      int ret1;
     sprintf(sql1, "select  cno,cname from course where state='1'");
      if ((ret1 = mysql_real_query(db, sql1, strlen(sql1) + 1)) != 0)
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
        fprintf(cgiOut, "<select name=\"cno\">\n");
        while ((row1 = mysql_fetch_row(res1)) != NULL)
        {
          fprintf(cgiOut,"<option ");
          fprintf(cgiOut, "value=\"%s\"> %s" ,row1[0],row1[1]);
          fprintf(cgiOut,"</option>");
        }
          fprintf(cgiOut,"</select>\n</div> \n</div>\n <div class=\"text-center\">\n <button  type=\"submit\" class=\"btn btn-success\">提交</button>\n <button type=\"reset\" class=\"btn btn-success\">重置</button> \n</div> \n</form> \n</body> \n</html>");

  return 0;
}
