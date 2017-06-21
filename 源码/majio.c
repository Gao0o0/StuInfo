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
    fd = fopen("addstu.html", "r");
      if(fd==NULL)
      {
        fprintf(cgiOut, "Cannot open file, addstu.html\n");
        return -1;
      }
  /*    char ch;
      ch = fgetc(fd);

  	while(ch != EOF){
  		fprintf(cgiOut, "%c", ch);
  		ch = fgetc(fd);
    }
  	db = mysql_init(NULL);
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
    sprintf(sql,"select pno,pname from school");
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
   unsigned int fields;
  	fields = mysql_num_fields(res);
    MYSQL_ROW  row;
    unsigned long  *len;
    fprintf(cgiOut, "<select name=\"pno\">");
  	while ((row = mysql_fetch_row(res)) != NULL)
  	{
  		fprintf(cgiOut,"<option ");
  		len = mysql_fetch_lengths(res);
      fprintf(cgiOut, "value=\"%.*s\" > %.*s",(int)len[0],row[0] ,(int)len[1],row[1]);
  		fprintf(cgiOut,"</option");
  	}
    fprintf(cgiOut, "</select>");

  	fprintf(cgiOut,"</div> </div> <div class=\"text-center\"> <butto type=\"submit\" class=\"btn btn-success\">提交</button> <button type=\"reset\" class=\"btn btn-success\">重置</button> </div> </form> </body> </html>");*/
    return 0;
}
