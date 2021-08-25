//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include "functions.h"


void perror(const char *msg);
int memcmp(const void *buf1, const void *buf2, size_t count);

/* Function to get the size of files */
int getSize(int argc, char * pathname1, char * pathname2){

    int s_size; /* where size of files will be saved */

    /* Define two structs stat;
       they return informations about the input files;
       we are interested about the sizes of the files.
    */
    struct stat st1;
    stat(pathname1, &st1); /* Collect data from the file passed as pathname1 */
    off_t size1 = st1.st_size; /* fetch the size and assign its value to size1 variable */

    struct stat st2;
    stat(pathname2, &st2); /* Collect data from the file passed as pathname2 */
    off_t size2 = st2.st_size; /* fetch the size and assign its value to size2 variable */

    printf("Size 1 => %d bytes\n\n", size1);
    printf("Size 2 => %d bytes\n\n", size2);

     /* If size1 is bigger than size2 */
    if(size1 > size2){
        s_size = size1;
        printf("size1 is bigger than size2\n\n");
    }

     /* If size1 is smaller than size2 */
    if(size1 < size2){
        s_size = size2;
        printf("size2 is smaller than size1\n\n");
    }

     /* If size1 is equal to size2 */
    if(size1 == size2){
        s_size = size2;
        printf("Files have the same size\n\n\n");
    }

    return s_size;
}

int main(int argc, char **argv){
    char * pathname1 = argv[1];
    char * pathname2 = argv[2];

    printf("\nArgs passed: %d\n\n", argc);
    if(argc < 3 || argc > 4){
        perror("Check your number of args passed\n\n");
        exit(EXIT_FAILURE);
    }
   /*
      Get the file size
      if argv[3] is not defined it will assign to fsize the biggest file size
   */

    int fsize = 0; /* File size value */

    if(argc == 4){ /* If 4 arguments compose the input... */
        char * size = argv[3];
        fsize = atoi(size);
        if(fsize == 0){
            perror("No number passed as arg\n\n");
            exit(EXIT_FAILURE);
        }
        //printf("fsize => %d\n\n", fsize);
    }

    else{
        fsize = getSize(argc, pathname1, pathname2); /* Invoke getSize function and assign its return value to fsize */
    }

    printf("Pathname 1 => %s\n\n", pathname1);
    printf("Pathname 2 => %s\n\n", pathname2);
    diff_files(pathname1, pathname2, fsize); /* Invoke diff_files function, passing the pathnames and fsize as parameters */
    exit(EXIT_SUCCESS);
}

/* Function which checks the differences between two files */
void diff_files(char * pathname1, char * pathname2, int fsize){

    int fd1 = open(pathname1, O_RDONLY, 0644); /* File descriptor of the first file */
    int fd2 = open(pathname2, O_RDONLY, 0644); /* File descriptor of the second file */

    /* If an error occurs during the opening operation of the files... */
    if(fd1 == -1 || fd2 == -1){
        perror("Error on opening files\n\n");
        printf("Errno => %d\n\n", errno);
        exit(EXIT_FAILURE); /* Exit with error */
    }

    printf("fsize (compared bytes) ----> %d bytes\n\n", fsize);

    /* Allocate two memory areas for two buffers */
    char *buf1 = (char *) calloc(fsize, sizeof(char));
    char *buf2 = (char *) calloc(fsize, sizeof(char));

    int r1;
    int r2;

    r1 = read(fd1, buf1, fsize); /* Read first file */
    buf1[r1] = '\0';
    r2 = read(fd2, buf2, fsize); /* Read second file */
    buf2[r2] = '\0';

    // Bytes comparison
    if(memcmp(buf1, buf2, fsize) == 0){
        printf("The files have the same content\n\n");
        exit(EXIT_SUCCESS);
    }
    else{
        printf("The files have NOT the same content\n\n");
    }

    /* Print the differences of each file */
    printf("Differences between the files: \n\n");
    for(int i = 0; i < fsize; i++){
        if(buf1[i] != buf2[i]){
            printf("File 1 => %c at the position %d\n\n", buf1[i], i+1);
            printf("File 2 => %c at the position %d\n\n", buf2[i], i+1);
        }
    }

}

