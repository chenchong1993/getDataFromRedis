#include <iostream>
#include <stdio.h>
#include <sys/select.h>
#include <hiredis/hiredis.h>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <typeinfo>

#include <fstream>
//#include "src/rtklib.h"
//#include "gips.h"
#include <iomanip>
using namespace std;

int main()
{
	//login redis
    redisContext* c = redisConnect("121.28.103.199", 5622);
    if (c->err) {    /* Error flags, 0 when there is no error */
        printf("连接Redis失败: %s\n", c->errstr);
        exit(1);
    }
    else{
        printf("连接Redis成功！\n");
    }

    redisReply* reply = (redisReply*)redisCommand(c, "AUTH %s", "CASMadmin2019");
    if (reply->type == REDIS_REPLY_ERROR) {
        printf("Redis认证失败！\n");
    }
    else{
        printf("Redis认证成功！\n");
    }
    freeReplyObject(reply);

    //强制使用小数,防止使用科学计数法
    cout << fixed;
    //控制显示的精度，控制小数点后面的位数
    cout << setprecision(7);

    ofstream out;
    out.open("com.txt",ios::trunc);
    out <<"redisTime" <<"     "<<"nowTime"<<endl;
	while (true)
	{
        redisReply* getDate = (redisReply*)redisCommand(c, "get x ");
        string redisTime= getDate->str;
		cout<<"redisTime" <<redisTime <<endl;

        struct  timeval    tv;
        struct  timezone   tz;
        gettimeofday(&tv,&tz);
        cout<<"  nowTime"<<tv.tv_sec<<"."<<tv.tv_usec<<endl;
        out <<redisTime <<"     "<<tv.tv_sec<<"."<<tv.tv_usec <<endl;
		cout<<"---------------"<<endl;




		sleep(1);
	}

    out.close();
    return 0;
}
