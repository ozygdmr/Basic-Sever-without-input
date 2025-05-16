#undef UNICODE

#define WIN32_LEAN_AND_MEAN



#include<Windows.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<stdio.h>
#include<iostream>

#pragma comment(lib,"Ws2_32.lib")


using namespace std;

int main(){
WSADATA data;
int iresult;
SOCKET listensock,clientsock;
addrinfo *result,hint;
char recbufv[512];
iresult = WSAStartup(MAKEWORD(2,2),&data);
if(iresult != 0){
cout<< "WSA ERROR";
    return 2;


}
ZeroMemory(&hint,sizeof(hint));
hint.ai_family = AF_INET;
hint.ai_protocol= IPPROTO_TCP;
hint.ai_flags = AI_PASSIVE;
hint.ai_socktype = SOCK_STREAM;

getaddrinfo(NULL,"27015",&hint,&result);


listensock = socket(result->ai_family,result->ai_socktype,result->ai_protocol);
if(listensock == INVALID_SOCKET)return 3;


iresult = bind(listensock,result->ai_addr,(int)result->ai_addrlen);
if(iresult == SOCKET_ERROR)return 4;

listen(listensock,SOMAXCONN);
if(iresult == SOCKET_ERROR)return 5;


clientsock = accept(listensock,NULL,NULL);
do{
iresult = recv(clientsock,recbufv,512,0);
if(iresult>0)cout<<recbufv[0];
}while(iresult != SOCKET_ERROR);
}