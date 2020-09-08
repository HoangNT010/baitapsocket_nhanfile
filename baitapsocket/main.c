#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "Socket.h"
#include "string_process.h"


void recive_data_header(char * buff_recive_pt)
{
	int count = 0;
	int flag = 1;
	do {
		int recive_res = Recv((buff_recive_pt + count), 1);

		if (buff_recive_pt[count - 3] == 0x0d && buff_recive_pt[count - 2] == 0x0a && buff_recive_pt[count - 1] == 0x0d && buff_recive_pt[count] == 0x0a)
		{
			flag = 0;
		}
		count++;
		buff_recive_pt[count] = '\0';
	} while (flag == 1);

}

void writting_file(char *buff_recive_pt, int len, char *des_pt)
{
	for (int i = 0; i < len; i++)
	{
		int recive_res_file = Recv(buff_recive_pt, 1);
		fwrite(buff_recive_pt, sizeof(char), 1, des_pt);
	}
}

int main()
{
	//create file
	errno_t err1, err2;
	FILE* data_header_file, *data_get_file;

	//config of server variable
	char server_ip[] = "116.193.72.106";
	int server_port = 80;

	//send request
	char data_send[] = "GET /2.jpg HTTP/1.1\r\nHost: mainhan.tk\r\n\r\n";
	int size_recive = 1;
	
	//create dyanmic variable
	char* buff_recive = NULL, * search_key = NULL;
	buff_recive	= (char*)calloc(512, sizeof(char));
	search_key = (char*)calloc(40, sizeof(char));
	if (buff_recive == NULL || search_key == NULL)
	{
		printf_s("Cap phat bo nho bi loi!\r\n");
		exit(0);
	}

	//open connet to server
	Socket_Client_Init(server_ip, server_port);
	int send_res = Send(data_send);

	//recive header
	recive_data_header(buff_recive);

	//process header to get lenght of file
	search_key = "Content-Length";
	int search_len = Str_len(search_key);
	int search_pos = find_SubStr_Position(buff_recive, search_key, search_len);
	int len_file = getValue(buff_recive,search_pos,search_len);

	//write header file to text for checking and testing
	err1 = fopen_s(&data_header_file, "header.txt", "w+");
	if (err1 != 0)
	{
		printf_s("Error! create file!");
		exit(0);
	}
	fputs(buff_recive, data_header_file);
	fclose(data_header_file);

	//reset buffer to 0 
	memset(buff_recive,0,(512*sizeof(char)));

	//writting a data of file
	err2 = fopen_s(&data_get_file, "1.jpg", "wb");
	if (err2 != 0)
	{
		printf_s("Error! create file!");
		exit(0);
	}
	writting_file(buff_recive,len_file,data_get_file);
	fclose(data_get_file);

	free(buff_recive);
	return 0;
}