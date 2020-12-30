
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <time.h>
#include <netinet/tcp.h>
#define PORT 3254 


static time_t total = 0;
static double totalt = 0;
static int count = 0;

int main(int argc, char const *argv[]) 
{ 
    	int server_fd, new_socket, valread; 
    	struct sockaddr_in address;
	bzero(&address, sizeof(address)); 
    	int opt = 1; 
    	int addrlen = sizeof(address); 
    	char buffer[1024*10] = {0};  
       
    	// Creating server 
	printf("create server\n");
    	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    	{ 
        	perror("socket failed"); 
        	exit(EXIT_FAILURE); 
    	} 
       
    	
	
    	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    	{ 
        	perror("setsockopt"); 
        	exit(EXIT_FAILURE); 
    	} 
    	address.sin_family = AF_INET; 
        //check again
    	address.sin_addr.s_addr = INADDR_ANY; 
    	address.sin_port = htons( PORT ); 
       
    	
	
    //server_fd -> soket , sockaddr-> PORT , bind-> connecet between the soket and the PORT
    	if (bind(server_fd, (struct sockaddr *)&address,  sizeof(address))<0) 
    	{ 
        	perror("bind failed"); 
        	exit(EXIT_FAILURE); 
    	} 
    
	// listen
	if (listen(server_fd, 1) < 0) 
    	{ 
        	perror("listen"); 
        	exit(EXIT_FAILURE); 
    	}
	int b =0 ;
    	int i =0;

    //struct sockaddr_in clientAddress;
    //socklen_t clientAddressLen = sizeof(clientAddress);

	while(i<=4)
	{
    
		// recive file

       // memset(&clientAddress, 0, sizeof(clientAddress));
       // clientAddressLen = sizeof(clientAddress);
                	new_socket = accept(server_fd, (struct sockaddr*)NULL, NULL);


        	//new_socket = accept(server_fd, (struct sockaddr*)&clientAddress, clientAddress);
        	if (new_socket==-1) 
		{
            		perror("Accept");
            		//continue;
        	}
		time_t begin = clock();
		time_t t = time(0);
		//printf("%f\n",(double)clock());
		int numOfBits = 0;
        	while( (b = recv(new_socket, buffer, sizeof(buffer),0))> 0 ) 
		{
                	numOfBits = numOfBits + b;
        	}
		//b=0;
		//printf("%ld",clock());
		time_t start = time(0);
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		count++;
		total += start-t;
		totalt += time_spent;
        	printf("Received byte: %d in %f seconds \t",numOfBits,time_spent);
		printf("(real time in about %ld seconds) \n", start-t);
        	if (b<0)
               		perror("Receiving");

        	i++;
		close(new_socket);
	}
	printf("total avarage time =  %f\n",totalt/count);
	printf("total general time = about %ld seconds\n",total);

	//change CC algorithm to reno
	strcpy(buffer, "reno"); 
	if (setsockopt(server_fd, IPPROTO_TCP, TCP_CONGESTION, buffer, strlen(buffer)) != 0) 
	{
		perror("setsockopt"); 
		return -1;
	}
	socklen_t len = sizeof(buffer);
	if (getsockopt(server_fd, IPPROTO_TCP, TCP_CONGESTION, buffer, &(len)) != 0) 
	{
		perror("getsockopt"); 
		return -1; 
	}
	printf("changed to reno algorithm\n");
	b = 0;
	total = 0;
	totalt=0;
	count = 0;
	i = 0;	
	while(i<5)
	{
		//printf("%ld",clock());
		clock_t begin = clock();
        	new_socket = accept(server_fd, (struct sockaddr*)NULL, NULL);
        	if (new_socket==-1) 
		{
            		perror("Accept");
            		//continue;
        	}
		
		time_t t = time(0);
		// int numOfBits =0;
        // 	while( (b = recv(new_socket, buffer, sizeof(buffer),0))> 0 ) 
		// {
        //         	numOfBits = numOfBits + b;
        // 	}
		
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		count+1;
		time_t e =time(0);
		total += e-t;
		totalt += time_spent;
        	//printf("Received byte: %d in %f seconds \t",numOfBits,time_spent);
			        	

		printf("(real time in about %ld seconds) \n", e-t);
		
        	if (b<0)
               		perror("Receiving");

        	i++;
		close(new_socket);
	}
	printf("avarage time is=  %f\n",totalt/count);
	printf("general time is= about %ld seconds\n",total);

    return 0; 
} 
