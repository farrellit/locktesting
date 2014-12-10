#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/file.h>

int openandlock( const char* file );

int main( int argc, char** argv){
  openandlock("/tmp/test.file");
  while(1) sleep(10);
  return 0;
}

int openandlock( const char* file ) {
  int openfd = open(file, O_CREAT | O_RDWR, 00744 );
  if(openfd < 0){
    char errormsg[] = "Failed to open file %*s for read/write: ";
    char* str = (char*)malloc(
      sizeof(char) * ( strlen(errormsg) + strlen(file) ) 
    );
    sprintf( str, errormsg, strlen(file), file );
    perror(str);
    exit(-1);
  }
  if( flock(openfd, LOCK_EX|LOCK_NB) != 0 ) {
    char errormsg[] = "Failed to open file %*s for read/write: ";
    char* str = (char*)malloc(
      sizeof(char) * ( strlen(errormsg) + strlen(file) ) 
    );
    sprintf( str, errormsg, strlen(file), file );
    perror(str);
    exit(-1);
  }  
  return 0;
}
