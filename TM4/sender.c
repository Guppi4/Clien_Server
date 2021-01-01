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
#define IP "127.1.1.1"
   
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
            int in_pt = inet_pton(AF_INET,IP, &(serv_addr.sin_addr));
    		if(in_pt<1)  
    		{ 
        		printf("\nIncorrect ipv4 address \n"); 
        		return -1; 
    		} 
    		
		// connect
    		int b;
    		if (b = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    		{ 
        		printf("\nConnection Failed \n"); 
        		return -1; 
    		} 
    
    		FILE *fp1; 
		printf("sending file to the server %d\n",i+1);
		fp1 = fopen("1mb.txt", "r");
        	if(fp1 == NULL){
                //perror -> eror message
        		perror("File");
        		return 2;
        	}
            //b -> sizeOf buffer
    		while( (b = fread(buffer, 1, sizeof(buffer), fp1))>0 ){
        		send(sock, buffer, b, 0);
			
   		} 
		fclose(fp1);
		close(sock);
	}

	printf("after changing algorithm to reno\n");
	for(int i = 0; i <=4 ; i ++){
        
        
	
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
    		if(inet_pton(AF_INET,IP, &serv_addr.sin_addr)<=0)  
    		{ 
        		printf("\nInvalid address/ Address not supported \n"); 
        		return -1; 
    		}
		

    
    		int b;
    		if (b = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    		{ 
        		printf("\nConnection Failed \n"); 
        		return -1; 
    		} 
    		
		
    		FILE *fp1; 
		printf("sending file to the server %d\n",i+1);
		fp1 = fopen("1mb.txt", "rb");
        	if(fp1 == NULL){
        		perror("File");
        		return 2;
        	}
    		while( (b = fread(buffer, 1, sizeof(buffer), fp1))>0 ){
        		send(sock, buffer, b, 0);
			
   		} 
		fclose(fp1);
		close(sock);
	}

	

    
    return 0; 
} 
