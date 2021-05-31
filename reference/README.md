# minishell 허용 함수

> printf

- `#include <stdio.h>`
- `int printf(const char *restrict format, ...);`
- 출력을 위해 사용하는 함수
- 실패시 -1, 성공시 출력한 문자의 갯수가 리턴됩니다.

> malloc

- `#include <stdlib.h>`
- `void *malloc(size_t size);`
- 메모리 동적할당을 위해 사용하는 함수
- 실패시 `NULL`반환
- 동적할당 후 `free` 를 꼭 해주어야 메모리 leak을 없앨 수 있습니다.

> free

- `#include <stdlib.h>`
- `void free(void *ptr);`
- 동적할당 한 메모리를 해제하기 위한 함수
- 리턴 값은 없습니다.
- 이미 free하거나 다시 free 하거나 해당 변수를 접근할 수 있을때에 free를 해주어야합니다.

> write

- `#include <unistd.h>`
- `ssize_t write(int fd, const void *buf, size_t count);`
- fd 값을 이용해서 파일에 데이터를 입력하거나 화면에 출력하는 등 여러 처리를 할 수 있습니다.
- 실패시 return 값은 -1 이며 errno를 이용해서 해당 이유를 알 수 있습니다.
- 성공시 count를 반환합니다.

> open

- `#include <fcntl.h>`
- `int open(const char *pathname, int flags);`
- 이미 존재하는 파일을 열거나 새로 생성하는 함수입니다.
- 실패시 -1을 반환하여 errno를 이용해서 해당 이유를 알 수 있습니다.
- 성공시 fd 값을 반환합니다.

> read

- `#include <unistd.h>`
- `ssize_t read(int fd, void *buf, size_t count);`
- 입력받은 내용을 읽는 함수입니다. (std input or file)
- 성공시 읽어들인 바이트 수를 반환합니다.
- 실패시 -1을 반환하며 errno를 이용해서 해당 이유를 알 수 있습니다.

> close

- `#include <unistd.h>`
- `int close(int fd);`
- open 함수를 이용해서 연 파일을 닫는 함수입니다.
- 성공시 0을 반환합니다.
- 실패시 -1을 반환하며 errno를 이용해서 해당 이유를 알 수 있습니다.

> fork

- `#include <unistd.h>`
- `pid_t fork(void);`
- 프로세스를 생성하려고 할 때 사용하는 함수입니다.
- fork 함수를 호출하는 프로세스는 부모 프로세스가 되고 fork를 이용해 새로 생성된 프로세스는 자식 프로세스가 됩니다.
- 성공시 부모 프로세스에게는 자식 프로세스의 PID를 반환하며 자식 프로세스에게는 0을 반환합니다.
- 실패시 부모 프로세스에게는 -1을 반환하며 자식 프로세스는 생성되지 않습니다. errno를 이용해서 에러코드를 확인할 수 있습니다.
- fork 함수가 실행된 직 후에는 부모 프로세스와 자식 프로세스가 동일한 주소 공간의 복사본을 가지게 되지만 fork 함수 이후의 코드가 pid  값을 기준으로 분리되어 있습니다.

> Wait

- `#include <sys/wait.h>`
- `pid_t wait(int *wstatus);`
- 부모 프로세스가 자식 프로세스의 종료될 때 까지 대기하는 함수입니다.
- 성공시 자식 프로세스가 종료될 때 자식 프로세스의 PID를 반환 받습니다.
- 자식 프로세스가 존재하지 않는 등 호출에 실패하게 되면 -1을 반환합니다.
- 자식 프로세스가 정상적으로 종료되면 wstatus가 true를 반환하며 매크로를 이용하여 하위 8비트를 참조하여 자식 프로세스가 exit, _exit, _Exit에 넘겨준 인자 값을 알 수 있습니다.
- 자식 프로세스가 비정상적으로 종료되면 wstatus가 true가 반환되며 비정상적으로 종료된 이유를 매크로를 이용해서 구할수 있습니다.

> waitpid

- `#include <sys/wait.h>`
- `pid_t waitpid(pid_t pid, int *stat_loc, int options);`
- wait 함수와 마찬가지로 부모프로세스가 자식프로세스가 종료될때까지 대기하게 해주는 함수입니다.
- 첫번째 인자로 pid를 줄 수 있으며 옵션을 이용하여 wait보다 많은 많은 상황을 구현해볼 수 있습니다.

> wait3

- `#include <sys/wait.h>`
- `pid_t wait3(int *statloc, int options, struct rusage *rusage);`
- 부모 프로세스가 자식 프로세스 가 종료되는 것을 기다리고, 종료된 프로세스의 상태와 자원 사용량을 알려주는 함수입니다.
- 성공시 프로세스 ID를 리턴하며, 만약 함수가 WNOHANG 옵션으로 실행되었고 자식 프로세스가 아직 종료되지 않았을 때는 0을 리턴합니다.
- 실패시 -1을 리턴 합니다.

> wait4

- `#include <sys/wait.h>`
- `pid_t wait4(pid_t pid, int *statloc, int options, struct rusage *rusage);`
- 부모 프로세스가 자식 프로세스 가 종료되는 것을 기다리고, 종료된 프로세스의 상태와 자원 사용량을 알려주는 함수입니다. 첫번째는
- 성공시 프로세스 ID를 리턴하며, 만약 함수가 WNOHANG 옵션으로 실행되었고 자식 프로세스가 아직 종료되지 않았을 때는 0을 리턴합니다.
- 실패시 -1을 리턴 합니다.

> signal

- `#include <signal.h>`
- `void (*signal(int signum, void (*handler)(int)))(int);`
- signum → 시그널 번호, handler → 시그널을 처리할 핸들러
- 리턴 값은 이전에 설정된 시그널 핸들러가 반환됩니다.

> kill

- `#include <signal.h>`
- `int kill(pid_t pid, int sig)`
- pid_t pid → 프로세스 pid 값, int sig → 시그널 번호
- 성공시 0을 반환하며, 실패시 -1을 반환합니다.

> exit

- `#include <stdlib.h>`
- `void exit(int status);`
- status → 호스트 에게 알려 줄 종료 값(에러코드)을 알려줍니다.
- 프로세스를 종료할 때 사용하는 함수입니다.

> getcwd

- `#include <unistd.h>`
- `char *getcwd(char *buf, size_t size);`
- 현재 디렉토리의 절대경로를 출력하는 함수입니다.
- buf → 현재 경로를 담아둘 버퍼
size → 해당 버퍼의 크기
- 만약 버퍼의 주소가 NULL이면 직접 malloc으로 메모리를 할당하고 주소를 리턴합니다.
- 성공시 현재 디렉토리의 절대경로를 출력합니다.
- 실패시 NULL을 리턴합니다.

> chdir

- `#include <unistd.h>`
- `int chdir(const char *dirname)`
- 현재 작업 디렉토리를 변경하는 명령입니다.
- dirname → 이동할 디렉터리 명
- 성공시 0을 리턴합니다.
- 실패시 -1을 리턴합니다.

> stat

- `#include <unistd.h>` `#include <sys/stat.h>`
- `int stat(const char *path, struct stat *buf);`
- 파일의 크기, 파일의 권한, 파일의 생성일시, 파일의 최종 변경일 등, 파일의 상태나 파일의 정보를 얻는 함수입니다.
- `stat` 함수는 심볼릭 링크파일을 path로 넘기면 해당 원본파일의 정보를 얻습니다.
- path → 파일 명 또는 파일에 대한 상대경로 또는 절대경로
	buf → 파일의 상태 및 정보를 저장할 buf 구조체
    ```c
	#include <sys/stat.h>
    struct stat
    {
    	dev_t st_dev;         //파일이 들어있는 장치의 ID
    	ino_t st_ino;         //아이노드 넘버
    	mode_t st_mode;       //파일의 접근권한
    	nlink_t st_nlink;     //하드링크 된 횟수
    	uid_t st_uid;         //파일의 소유자
    	gid_t st_gid;         //파일의 소유그룹
    	dev_t st_rdev;        //장치 ID
    	off_t st_size;        //파일의 크기(bytes)
    	blksize_t st_blksize; //파일 시스템 입출력에 대한 블록 사이즈
    	blkcnt_t st_blocks;   //512bytes 블록의 수
		time_t st_atime;	  //최근 액세스 시간
		time_t st_mtime;	  //최근 수정 시간
		time_t st_ctime;	  //최근 상태 변경 시간
    }
    ```
- 성공시 0, 실패시 -1을 리턴합니다.

> lstat

- `#include <unistd.h>` `#include <sys/stat.h>`
- `int lstat(const char *path, struct stat *buf);`
- 파일의 크기, 파일의 권한, 파일의 생성일시, 파일의 최종 변경일 등, 파일의 상태나 파일의 정보를 얻는 함수입니다.
- `lstat` 함수는 심볼릭 링크파일을 path로 넘기면 심볼릭 링크파일 자체의 정보를 얻습니다. 그 이외에는 `stat` 함수와 똑같이 작동합니다.
- 성공시 0, 실패시 -1을 리턴합니다.

> fstat

- `#include <unistd.h>` `#include <sys/stat.h>`
- `int fstat(int fd, struct stat *buf);`
- 열려진 파일의 크기, 파일의 권한, 파일의 생성일시, 파일의 최종 변경일 등, 파일의 상태나 파일의 정보를 얻는 함수입니다.
- fd → 파일 디스크립터
	buf → 파일의 상태 및 정보를 저장할 구조체
- 성공시 0, 실패시 -1을 리턴합니다.

> execve

- `#include <unistd.h>`
- `int execve(const char *filename, char *const argv[], char *const envp[])`
- 실행가능한 파일인 filename의 실행 코드를 현재 프로세스에 적재하여 기존의 실행코드와 교체하여 새로운 기능으로 실행합니다. 즉, 현재 실행되는 프로그램의 기능은 없어지고 filename 프로그램을 메모리에 로딩하여 처음부터 실행합니다.
- filename → 교체할 실행파일 이나 명령어, 실행가능한 binary 이거나 shell이어야 합니다.
	argv → main의 argv의 역할을 합니다.
	envp → key=value 형식의 환경변수 문자열 배열리스트로 마지막은 NULL이어야 합니다.
- 성공시 프로그램이 정상적으로 실행됩니다. 리턴 값은 이미 지정된 프로그램의 로직으로 실행되기 때문에 받을 수 없습니다.
- 실패시 -1을 리턴합니다.

> dup

- `#include <unistd.h>`
- `int dup(int fd)`
- fd를 복사하여 다른 fd로 반환하는 함수이며, 가장 낮은 수의 fd를 반환합니다.
- fd → 복사할 file descriptor 값
- 성공시 새 fd 값을 반환해줍니다.
- 실패시 -1을 리턴합니다.

> dup2

- `#include <unistd.h>`
- `int dup2(int fd, int fd2);`
- fd2를 복사하여 fd로 반환하는 함수이며, 이를 이용하여 파일 입출력의 방향을 변경할 수 있습니다.(리다이렉션 구현시 필요)
- fd → 복사하려는 원본 fd
	fd2 → 복사되는 target fd
- 성공시 fd2를 반환
- 실패시 -1을 반환

> pipe
- `#include <unistd.h>`
- `int pipe(int fd[2])`
- 프로세스간의 통신을 하기위해 사용하는 함수입니다.
- 프로세스는 메모리가 독립적으로 존재해서 프로세스간 통신하는 것이 불가능하기 때문에 fork로 생성한 프로세스는 프로그램내에서 데이터를 주고받을 수 없습니다. 이에 대한 해결책으로 pipe 함수를 사용합니다.
- fd[0] → 함수호출 후 데이터를 입력받을 수 있는 fd 값이 담김
	fd[1] → 함수호출 후 데이터를 출력할 수 있는 fd 값이 담김
- 성공시 0을 반환
- 실패시 -1을 반환

> opendir
- `#include <dirent.h>`
- `DIR *opendir(const char *name)`
- 매개변수로 받은 디렉토리를 여는 함수입니다. (open의 디렉터리 버전같은 느낌)
- name → 열려고하는 디렉토리
- 성공시 디렉토리 정보 구조체인 DIR을 반환합니다.
- 실패하면 NULL을 반환합니다.

> readdir
- `#include <dirent.h>`
- `struct dirent *readdir(DIR *dir)`
- opendir 함수로 연 디렉토리에 대해, 파일과 하위 디렉토리의 정보를 구합니다.
- DIR *dir → opendir로 연 디렉토리 정보
- 성공시 파일이나 디렉토리 정보를 반환합니다.
- 실패시 NULL을 반환합니다.

> closedir
- `#include <dirent.h>`
- `int closedir(DIR *dir)`
- opendir 함수로 연 디렉터리 정보를 닫는 함수입니다.
- DIR *dir → opendir로 연 디렉토리 정보
- 성공시 0을 반환합니다.
- 실패시 -1을 반환합니다.

> strerror
- `#include <string.h>`
- `char *strerror(int errno)`
- errno에 해당하는 오류 문자열을 가져오는 함수입니다.
- errno → 에러가 발생했을 시 저장되는 에러 번호
- 성공시 errno에 해당하는 오류 문자열을 가져옵니다.
- 오류넘버가 잘못 입력될시 NULL 또는 unknownerror가 리턴됩니다.

> errno
- `#include <errno.h>`
- 함수 실행시 오류의 원인을 저장하는 전역변수입니다.
- 함수를 실행할 때마다 값이 변경됩니다.
- 오류가 없으면 0이 저장되고 오류가 발생하면 에러코드가 저장됩니다.

> isatty
- `#include <unistd.h>`
- `int isatty(int fd)`
- 매개변수로 받은 fd가 터미널에 연결되어있는 확인하는 함수입니다.
- fd → 터미널에 연결되어 있는지 확인할 fd 값
- 연결되어있을 경우 1을 반환합니다.
- 연결되어 있지 않을 경우 0을 반환합니다.

> ttyname
- `#include <unistd.h>`
- `char *ttyname(int fd)`
- fd 값을 확인해서 해당 하는 fd에 대한 터미널 이름을 얻어오는 함수입니다.
- fd → 해당하는 fd의 터미널 이름을 알아내기 위해 지정하는 fd 값
- 성공시 해당하는 터미널의 이름을 반환합니다.
- 실패시 NULL을 반환합니다.

> ttyslot
- `#include <unistd.h>`
- `int ttyslot(void)`
- 일부 파일들에서 현재 사용자 터미널의 슬롯을 찾는 함수입니다.
- 성공시 사용자 계정 데이터베이스에 있는 현재 사용자의 항목의 인덱스를 반환합니다.
- 데이터베이스를 검색하는 동안 오류가 발생했거나 fd가 0, 1, 2가 터미널 장치와 연결되어 있지 않을 경우 0을 반환합니다.

> ioctl
- `#include <sys/ioctl.h>`
- `int ioctl(int fd, unsigned long request, ...)`
- 하드웨어의 제어와 상태정보를 얻기 위해 제공되는 함수입니다.
- read, write를 통한 데이터를 읽고 쓰는 등의 기능은 사용가능하지만 하드웨어를 제어하거나 상태를 확인하려면 ioctl 함수를 써야합니다.
- fd → open한 디바이스 드라이버의 fd 값
	request → 디바이스에게 전달할 명령(이 명령에 따라서 디바이스를 컨트롤 할 수 있습니다.)
- 성공시 0을 반환합니다.
- 에러 발생시 -1을 반환합니다.

> getenv
- `#include <stdlib.h>`
- `char *getenv(const char *name)`
- 매개변수로 받은 name이 가리키는 문자열과 일치하는 문자열을 찾기 위해 환경 변수 리스트를 탐색한다.
- name = value 형태로 탐색된다.
- name → name이 가리키는 문자열을 찾기위해 입력받음
- 성공시 name과 매칭되는 문자열을 반환 받습니다.
- 실패시 NULL 포인터를 반환받습니다.

> tcsetattr
- `#include <termios.h>`
- `int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p)`
- 터미널의 속성을 변경하는 함수입니다.
- fileds → 터미널 fd 값
	optional_actions → 터미널에 주어지는 동작
	*termios_p → 터미널 속성을 저장할 주소
- 성공시 0을 반환합니다.
- 실패시 -1을 반환합니다.

> tcgetattr
- `#include <termios.h>`
- `int tcgetattr(int fildes, struct termios *termios_p)`
- 터미널 속성을 가져오는 함수입니다.
- fileds → 터미널 fd 값
	*termios_p → 터미널 속성을 저장할 주소
- 성공시 0을 반환합니다.
- 실패시 -1을 반환합니다.

> tgetent
- `#include <term.h>`
- `int tgetent(char *bp, const char *name)`
- name에 대한 termcap의 항목을 찾습니다.

> tgetflag

- `#include <term.h>`
- `int tgetflag(char *id)`
-

> tgetnum
- `#include <term.h>`
- `int tgetnum(char *id)`
-

> tgetstr
- `#include <term.h>`
- `char *tgetstr(char *id, char **area)`
-

> tgoto
- `#include <term.h>`
- `char *tgoto(const char *cap, int col, int row)`
-

> tputs
- `#include <term.h>`
- `int tputs(const char *str, int affcnt, int (*putc)(int))`
-
