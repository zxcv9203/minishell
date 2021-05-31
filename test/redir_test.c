#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

void print_list(int length,char *buf[]);

int main(){
    char str[1024];
    char *buffer[255];
    int buf_leng = 1;
    int str_len;
    int t;
    int fd;
    char *command[16];
    char *pip_command[16][16];
    char *cur_dir;
    int cmd_num = 0;
    int fdr[2];
    int fdd = 0;
    int p;
    int type = 0;
    int semi = 0;
    int semi_pre_buf_leng =0;
    char his_buf[256];
    char c = '\n';
    pid_t pid;
    int his;
    int bck_gnd = 0;

    // signal(SIGINT,SIG_IGN);
    // signal(SIGQUIT,SIG_IGN);
    // signal(SIGTSTP,SIG_IGN);
    while(1){

        type = 0;
        buf_leng = 1;
        cmd_num = 0;
        for(int i=0 ; i < 1024 ; i++) str[i]='\0'; //initialization of str
        if(semi != 0){
            // printf("어서오십시오! 세미월드입니다\n");
            for(int i = semi+1; i < semi_pre_buf_leng; i++){
                strcat(str,buffer[i]);
                strcat(str," ");
            }
            semi = 0;
            semi_pre_buf_leng = 0;
            // printf("%s",str);
        }
        else {
            fgets(str,sizeof(str),stdin);
            his = open("history",O_CREAT|O_RDWR|O_APPEND);
            write(his,str,strlen(str));
            // write(his,&c,1);
            close(his);

        }
        for(int i=0; i < 15; i++) {
            command[i] = NULL;
            buffer[i] = malloc(sizeof(char) * 20);
        }
        for(int i=0; i< 16;i++){
            for(int k = 0; k<16;k++)
                pip_command[i][k] =malloc(sizeof(char) * 20);
        }

        str[strlen(str) -1] = '\0';
        str_len = strlen(str);
        // printf("왜 나왔다가 안나왓다가.. ㅜㅠㅜㅠㅜ 길이:%d\n",str_len);
        // print_list(buf_leng,buffer);
        for(int i=0; i< strlen(str);i++){
            // printf("%c",str[i]);
            switch(str[i]){
                case ' ':
                    if(strcmp(buffer[buf_leng],"") != 0)
                        buf_leng++;
                    break;
                case '>':
                    if(buf_leng > 0 && strcmp(buffer[buf_leng-1],">")== 0){
                        strcat(buffer[buf_leng-1],">");
                    }
                    else{
                        if(strcmp(buffer[buf_leng],"") != 0)
                            buf_leng++;
                        strcat(buffer[buf_leng], ">");
                        buf_leng++;
                    }
                    break;
                case '|' :
                    if(strcmp(buffer[buf_leng-1],">")== 0){
                        strcat(buffer[buf_leng-1],"|");
                    }
                    else{
                        if(strcmp(buffer[buf_leng],"") != 0)
                            buf_leng++;
                        strcat(buffer[buf_leng], "|");
                        buf_leng++;
                        type = 1;
                        break;
                    }
                    break;
                case '<' :
                    if(strcmp(buffer[buf_leng],"") != 0)
                        buf_leng++;
                    strcat(buffer[buf_leng], "<");
                    buf_leng++;
                    break;
                case '&' :
                    if(strcmp(buffer[buf_leng],"") != 0)
                        buf_leng++;
                    strcat(buffer[buf_leng], "&");
                    buf_leng++;
                    break;
                case ';' :
                    if(strcmp(buffer[buf_leng],"") != 0)
                        buf_leng++;
                    strcat(buffer[buf_leng], ";");
                    semi = buf_leng;
                    buf_leng++;
                    break;

                default:
                    // printf("%d",i);
                    strncat(buffer[buf_leng],&str[i],1);
                    // printf("%s",buffer[buf_leng]);
                    break;
            }

        }

        // if(strcmp(buffer[buf_leng-1],"hello") == 0) printf("please..");
        buf_leng++;
        if(semi != 0){
            semi_pre_buf_leng = buf_leng;
            buf_leng = semi;
        }
        // printf("이 밑에거는 왜 실행이 안되는거죠..\n");
        // print_list(buf_leng,buffer);
        switch(type){
            case 0 :
                if((pid = fork() )== 0){
                    // printf("맛있는 포크를 성공시켰습니다\n");
                    t = 1;
                    while(t < buf_leng){
                        if(strcmp(buffer[t],">")== 0){
                            // printf(">가 써져있으니 여기로 오시지요\n 파일 성함이 %s가 맞는 지요?",buffer[t+1]);
                            fd = open(buffer[t+1],O_CREAT | O_RDWR|O_TRUNC, 0644);
                            dup2(fd,1);
                            close(fd);
                            t += 2;
                        }
                        else if(strcmp(buffer[t],"<")== 0){
                            fd = open(buffer[t+1],O_RDWR);

                            dup2(fd,0);
                            close(fd);
                            // command[cmd_num] = buffer[t+1];
                            // cmd_num++;
                            t += 2;
                        }
                        else if(strcmp(buffer[t],">>")== 0){
                            fd = open(buffer[t+1],O_CREAT|O_RDWR|O_APPEND, 0644);
                            dup2(fd,1);
                            close(fd);
                            t += 2;

                        }
                        else if(strcmp(buffer[t],">|")== 0){
                            fd = open(buffer[t+1],O_CREAT | O_RDWR|O_TRUNC, 0644);
                            dup2(fd,1);
                            close(fd);

                            t += 2;
                        }
                        else if(strcmp(buffer[t],"&")== 0){
                            bck_gnd = 0;
                            t += 2;
                        }
                        else{
                            command[cmd_num] = buffer[t];
                            cmd_num++;
                            t++;

                        }
                    }
                    // printf("왜 실행이 안될까요?\n");
                    // printf("커맨드1번째의 값은 이겁니다.%s\n",command[1]);
                    if(strcmp(command[0],"cd")==0){//내장명령어 cd
                        chdir(command[1]);//현재 디렉토리 변경
                    }
                    else if(strcmp(command[0],"history")== 0){
                        his = open("history",O_CREAT|O_RDWR);
                        read(his,his_buf,255);
                        printf("%s",his_buf);
                        bck_gnd = 1;
                    }
                    else{
                        execvp(command[0],command);
                        exit(0);
                    }

                }
                break;
            //pipe
            case 1 :
                // if(fork() == 0){
                    // printf("맛있는 파이프 포크를 성공시켰습니다\n");
                    t = 1;
                    p = 0;
                    while(t < buf_leng){
                        if(strcmp(buffer[t],"|") == 0){
                            pip_command[cmd_num][p] = NULL;
                            cmd_num++;
                            t++;
                            p = 0;
                        }
                        else{

                            strcat(pip_command[cmd_num][p],buffer[t]);
                            // printf("현재 파이프 커맨드%d %d에 %s를 넣고 싶다.. 미칠듯이\n ",cmd_num,p,buffer[t]);
                            // printf("넣어졌는지 확인해볼까? -> %s\n",pip_command[cmd_num][p]);
                            p++;
                            t++;
                        }

                    }
                    pip_command[cmd_num][p] = NULL;
                    p = 0;
                    int i;
                    for(i=0; i<cmd_num; i++){
                        pipe(fdr);
                        switch(fork()){
                            case -1: perror("fork error"); break;
                            case  0:
                                if(close(1) == -1) perror("close1");
                                dup(fdr[1]);
                                if(close(fdr[0]) == -1 || close(fdr[1]) == -1){
                                    perror("close2");
                                }
                                execvp(pip_command[i][0], pip_command[i]);
                                printf("cmd not found");
                                exit(0);
                            default:
                                close(fdr[1]);
                                dup2(fdr[0], 0);
                        }
                    }
                    execvp(pip_command[i][0], pip_command[i]);
                break;

            default :
                if(!bck_gnd){
                    wait(NULL);
                    fflush(stdout);
                }
                else{
                    printf("BACKGROUND PID: %d\n",getpid());
                    bck_gnd = 0;
                    break;
                }

        }
        // for(int i=0; i < 15; i++) { free(buffer[i]);}
    }
}


void print_list(int length,char *buf[]){
    for(int i = 1 ; i < length ; i++){
        printf("[%s]\t", buf[i]);
    }
    printf("\n");
}

