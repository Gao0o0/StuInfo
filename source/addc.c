#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{
    fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
    int ret;
  	MYSQL *db;
  	char sql[128] = "\0";
    FILE *fd;
    fd = fopen("addc.html", "r");
      if(fd==NULL)
      {
        fprintf(cgiOut, "Cannot open file, addstu.html\n");
        return -1;
      }
     char ch;
      ch = fgetc(fd);

  	while(ch != EOF){
  		fprintf(cgiOut, "%c", ch);
  		ch = fgetc(fd);
    }
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
    sprintf(sql,"select cno,cname from course");
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
    unsigned long  *len;
    fprintf(cgiOut, "<select name=\"cpan\">\n");
  	while ((row = mysql_fetch_row(res)) != NULL)
  	{
  		fprintf(cgiOut,"<option ");
  		len = mysql_fetch_lengths(res);
      fprintf(cgiOut, "value=\"%.*s\" > %.*s",(int)len[0],row[0] ,(int)len[1],row[1]);
  		fprintf(cgiOut,"</option>\n");
  	}
    fprintf(cgiOut, "<option value=\"null\">无先修课</option>\n");
    fprintf(cgiOut, "</select>\n");

  	fprintf(cgiOut,"</div> \n</div>\n <div class=\"text-center\">\n <button  type=\"submit\" class=\"btn btn-success\">提交</button>\n <button type=\"reset\" class=\"btn btn-success\">重置</button> \n</div> \n</form> \n</body> \n</html>");
    return 0;
}
