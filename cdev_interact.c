#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define bufSize 150
#define DEVICE "/dev/Gau_Device"

int main(){
	int fd;
	char command;
	char *read_data=malloc(bufSize);
	char *write_data=malloc(bufSize);
	fd=open(DEVICE,O_RDWR);
	if(fd<0){
		printf("Cannot open file");
		exit(-1);
	}
	printf("Enter 'r' to read and 'w' to write\nEnter command:");
	scanf("%c",&command);
	getchar();
	
	switch(command){
		case 'w':
			printf("Enter Data to be written:");
			fgets(write_data,bufSize,stdin);
			write_data[strlen(write_data)-1]='\0';
			printf("writing %s\n",write_data);
			write(fd,write_data,bufSize);
			break;
		case 'r':
			read(fd,read_data,bufSize);
			printf("device: %s\n",read_data);
			break;
		default:
			printf("command not recognized\n");
			break;
	}
	free(read_data);
	free(write_data);
	close(fd);
	return 0;

}
