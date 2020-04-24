#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

void green_str_print(const char *format, ...);

void green_str_print(const char *format, ...){
	va_list ap;
	char str[1024];

	memset(str, 0x00, sizeof(str));	

	va_start(ap, format);
	vsnprintf(str, sizeof(str), format, ap);
	va_end(ap);
	
	printf("\033[32m%s\033[37m", str);
}

void clock_num(int hour, int min, int type){
	char clock_str[4096];
	memset(clock_str, 0x00, sizeof(clock_str));	

	char *clock_split = "            ///              ///             ";

	char *clock[] = {"    /////   // //   // //   // //   /////    ",
                     "    ////      //      //      //    //////   ",
	                 "    /////      //   /////   //      /////    ",
	                 "    /////      //   /////      //   /////    ",
	                 "   //  //  //  //  ////////    //      //    ",
	                 "    /////   //      /////      //   /////    ",
	                 "    /////   //      /////   // //   /////    ",
	                 "    /////      //      //      //      //    ",
	                 "    /////   // //   /////   // //   /////    ",
	                 "    /////   // //   /////      //   /////    "};

	int hour_high,hour_low,min_high,min_low;
	
	hour_high = hour / 10;
	hour_low = hour % 10;
	min_high = min / 10;
	min_low = min % 10;		

	int i;
	for(i=0;i<5;++i){
		strncat(clock_str, clock[hour_high] + i*9, 9);
		strncat(clock_str, clock[hour_low] + i*9, 9);
		if(type == 1){
			strncat(clock_str, clock_split + i*9, 9);
		}else{
			strncat(clock_str, "         ", 9);
		}
		strncat(clock_str, clock[min_high] + i*9, 9);
		strncat(clock_str, clock[min_low] + i*9, 9);
		strcat(clock_str, "\n");
	}

	green_str_print("%s", clock_str);
}

int main(int argc, char *argv){
	time_t now;
	struct tm *local_now;

	while(1){
		system("clear");
		time(&now);
		local_now = localtime(&now);	
		clock_num(local_now->tm_hour, local_now->tm_min, 0);
		sleep(1);
		system("clear");
		clock_num(local_now->tm_hour, local_now->tm_min, 1);
		sleep(1);
	}
	return 0;
}
