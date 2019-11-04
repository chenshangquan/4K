#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
/* According to earlier standards */

#include "mcc_tran.h"

int main(void)
{
/* command: e1<0-3> channel-group <0-7> timeslots <0-31> serial <16-62> mtu <0-65535>*/	
	int e1 = 0;
	int channel = TRAN_CH_START;
	int mtu = 8192;
	int fd ;
	char timeslot[] = "1-15";
	pid_t  pid;
	char t_buff[8192];
	int i;
	char r_buff[10000];
	fd_set f_set;
	int result;
	int freeslots;
	
	for (i = 0; i< 8192 ;i++){
		t_buff[i] = 'a' + i%26;
	}
	
	printf("###args\nE1 %d\nchannel %d\ntimeslot %s\nmtu %d\r\n", e1, channel,timeslot, mtu);

	fd = open_e1_trans(e1, channel, timeslot,  mtu);
	
	if (fd<0){
		printf("###error code = %d", fd);
		return (1);
	}
	
	i = 0;
	if ((pid = fork())>0){
		while(i<= 20){
			freeslots = get_e1_in_use_slot(fd);
			printf("\n###used slots = %d \r\n", freeslots);
			write(fd, t_buff,8192);
			i++ ;
		}	
		waitpid(pid, NULL, 0);	
	}else{
		while(i<= 25){
			FD_ZERO(&f_set);
			FD_SET(fd,&f_set);		
			select(fd+1,&f_set,NULL, NULL,NULL);

			if (FD_ISSET(fd, &f_set)){
				result =read(fd,r_buff,10000);
				r_buff[result]= '\0';
				printf("\n###the data received :length =%d\n buff = %s\r\n", result ,r_buff);
				memset(r_buff, 0 , 10000);
			}
			i++;
		}
		return 1;
	}
	
	close_e1_trans(e1, channel ,fd);
	printf("###end of test function\r\n");
	return 1;
}




