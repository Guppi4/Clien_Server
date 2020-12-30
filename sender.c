#include <stdio.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <netinet/in.h> 
#include <netinet/tcp.h>
#include <time.h>
#define PORT 3254 

   
int main(int argc, char const *argv[]) 
{ 
	int i;
	for(int i = 0; i <=4 ; i ++){
		//printf("open socket\n");	
    		int sock = 0, valread; 
        //serv_addr save all of the data of the Measure server
    		struct sockaddr_in serv_addr; 
		bzero(&serv_addr, sizeof(serv_addr));
    		char buffer[1024*10] = {0}; 
    		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    		{ 
        		printf("\n Socket creation failed \n"); 
        		return -1; 
    		} 
   
            //port for IPV4
    		serv_addr.sin_family = AF_INET; 
            //add Port to stuct Adrress 
            //"PORT 3254"
    		serv_addr.sin_port = htons(PORT); 
       
    		// inet_pton - From IPV4 address to binary
            //sin_addr -> the ip adrr of Measure to binary
            int in_pt = inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    		if(in_pt<1)  
    		{ 
        		printf("\nIncorrect ipv4 address \n"); 
        		return -1; 
    		} 
    		
		// connect
		printf("connecting...\n");
    		int b;
    		if (b = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    		{ 
        		printf("\nConnection Failed \n"); 
        		return -1; 
    		} 
    
		printf("sending...\n");
    		FILE *fp1; 
		printf("sending file... %d\n",i+1);
		fp1 = fopen("1mb.txt", "r");
        	if(fp1 == NULL){
                //perror -> eror message
        		perror("File");
        		return 2;
        	}
            //b -> sizeOf buffer
    		while( (b = fread(buffer, 1, sizeof(buffer), fp1))>0 ){
        		send(sock, buffer, b, 0);
			//bzero(buffer, 1024);
   		} 
		fclose(fp1);
		close(sock);
	}

	printf("after changing algorithm to reno\n");
	for(int i = 0; i <=4 ; i ++){
        
        
		//printf("open socket\n");	
    		int sock = 0, valread; 
    		struct sockaddr_in serv_addr;
		bzero(&serv_addr, sizeof(serv_addr));  
    		char buffer[1024] = {0}; 
    		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    		{ 
        		printf("\n Socket creation error \n"); 
        		return -1; 
    		} 
   
    		serv_addr.sin_family = AF_INET; 
    		serv_addr.sin_port = htons(PORT); 
       
    		// inet_pton
    		if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    		{ 
        		printf("\nInvalid address/ Address not supported \n"); 
        		return -1; 
    		}
		

		//change CC algorithm to reno
    //socklen_t len1 = strlen(buffer);
    
		strcpy(buffer, "reno"); 
		if (setsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buffer, strlen(buffer)) != 0) {
			perror("setsockopt"); 
			return -1;
		}
		socklen_t len = sizeof(buffer);
		if (getsockopt(sock, IPPROTO_TCP, TCP_CONGESTION, buffer, &(len)) != 0) {
			perror("getsockopt"); 
			return -1; 
		} 
    
    		int b;
		printf("connecting...\n");
    		if (b = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    		{ 
        		printf("\nConnection Failed \n"); 
        		return -1; 
    		} 
    		
		
    		FILE *fp1; 
		printf("send file %d\n",i+1);
		fp1 = fopen("1mb.txt", "rb");
        	if(fp1 == NULL){
        		perror("File");
        		return 2;
        	}
    		while( (b = fread(buffer, 1, sizeof(buffer), fp1))>0 ){
        		send(sock, buffer, b, 0);
			//bzero(buffer, 1024);
   		} 
		fclose(fp1);
		close(sock);
	}

	

    
    return 0; 
} 
