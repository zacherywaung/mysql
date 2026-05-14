#include <iostream>
#include <string>
#include <unistd.h>
#include <mysql/mysql.h>
// env
const std::string host = "127.0.0.1";
const std::string user = "wz";
const std::string password = "123456";
const std::string database = "library";
const unsigned int port = 3306;

int main()
{
    // grep handler
    MYSQL* my = mysql_init(nullptr);
    if(nullptr == my)
    {
        std::cerr << "init fail" << std::endl;
        return 1;
    }
    // connet
    MYSQL* cn = mysql_real_connect(my, host.c_str(), user.c_str(), password.c_str(), database.c_str(), port, nullptr, 0);
    if(nullptr == cn)
    {
        std::cerr << "connect fail" << std::endl;
        return 2;
    }
    mysql_set_character_set(my, "utf8");
    // sql
    std::string sql = "select * from books where id > 0 and id < 100 limit 1000";
    int n = mysql_query(my, sql.c_str());
    if(n == 0)
    {
        std::cout << "success" << std::endl;
    }
    else{
        std::cerr << sql << " failed" << std::endl;
        return 3;
    }
    // grep result handler
    MYSQL_RES* res = mysql_store_result(my);
    if(nullptr == res)
    {
        std::cerr << "result store err" << std::endl;
        return 4;
    }
    // row col
    int row = mysql_num_rows(res);
    int col = mysql_num_fields(res);
    std::cout << "row: " << row << std::endl;
    std::cout << "fields: " << col << std::endl;
    // print field tag
    MYSQL_FIELD* fields = mysql_fetch_fields(res);
    for(int i = 0; i < col; i++)
    {
        std::cout << fields[i].name << "\t";
    }
    std::cout << std::endl;
    // print data
    for(int i = 0; i < row; i++)
    {
        MYSQL_ROW line = mysql_fetch_row(res);
        for(int j = 0; j < col; j++)
        {
            if(nullptr == line[j])
            {
                std::cout << "NULL" << "\t";
            }
            else{
                std::cout << line[j] << "\t";
            }
        }
        std::cout << std::endl;
    }
    // free, disconnect
    mysql_free_result(res);
    mysql_close(my);

}


