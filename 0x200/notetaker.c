#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "hacking.h"

void usage(char *prog_name, char *filename){
  printf("使用方法：%s <%sに使用するデータ>\n", prog_name, filename);
  exit(0);
}

void fatal(char*);
void *ec_malloc(unsigned int);

int main(int argc, char *argv[]){
  int userid, fd;
  char *buffer, *datafile;

  buffer = (char *) ec_malloc(100);
  datafile = (char *) ec_malloc(20);
  strcpy(datafile, "/var/notes");

  if (argc < 2)
    usage(argv[0], datafile);

  strcpy(buffer, argv[1]);

  printf("[DEBUG] buffer @ %p: \'%s\'\n", buffer,buffer);
  printf("[DEBUG] datafile @ %p: \'%s\'\n", datafile, datafile);

  //strncat(buffer, "\n", 1);

  //open
  fd = open(datafile, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
  if (fd == -1)
    fatal("main()内、ファイルのオープン中にエラーが発生しました。");
  printf("[DEBUG] ファイル記述子:%d\n", fd);

  userid = getuid();

  //write
  if (write(fd, userid, 4) == -1)
    fatal("main()内、ファイルへのユーザーIDの書き込みでエラーが発生しました。");
  write(fd, "\n", 1);

  if (write(fd, buffer, strlen(buffer)) == -1)
    fatal("main()内、ファイルへのバッファの書き込み中にエラーが発生しました。");

  //close
  if (close(fd) == -1)
    fatal("main()内、ファイルのクローズ中にエラーが発生しました。");
  printf("メモが保存されました\n");
  free(buffer);
  free(datafile);
}
