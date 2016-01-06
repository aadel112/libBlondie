#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "blondie.h"

// #define D "/storage/emulated/0/Download/"
#define D "/storage/emulated/0/DCIM/Camera/"
#define LEN 1024

int n = 0;
char files[LEN][LEN]; 

void sort_by_size();
void listd(char* directory);
int fsize(char* filename);
int fexists(char* filename);

int main(int argc, char** argv) {

    int i;
    listd( D );
    sort_by_size();
    for( i = 0; i < n; ++i ) {
        printf("File %s, Size %d\n", files[i], fsize( files[i] ) );   
    }
}

void sort_by_size() {

    int c, d;
    int curr, next;
    char swap[LEN];

    for( c = 0; c < n - 1; ++c ) {
        for( d = 0; d < n - c - 1; ++d ) {
            curr = fsize( files[d] );
            next = fsize( files[(d+1)] );
            if( curr < next ) {
                memset(swap, 0, LEN);
                strncpy( swap, files[d], strlen(files[d]) > LEN ? LEN : strlen(files[d]));
                memset(files[d], 0, LEN);
                strncpy( files[d], files[d+1], strlen(files[d+1]) > LEN ? LEN : strlen(files[d+1]));
                memset(files[d+1], 0, LEN);
                strncpy(files[d+1], swap, strlen(swap) > LEN ? LEN : strlen(swap));
            }
        }
    }
}

void listd(char* directory) {
    DIR *dir;
    struct dirent *ent;
    int i = 0;
    char tmp[LEN];

    if ((dir = opendir (directory)) != NULL) {
        while ((ent = readdir (dir)) != NULL && i < LEN ) {
            memset(tmp, 0, LEN);
            memset(files[i], 0, LEN);
            sprintf(tmp, "%s%s", D, ent->d_name);
            if( fexists(tmp) ) {
                strncpy(files[i], tmp, strlen(tmp) > LEN ? LEN : strlen(tmp));
            } else {
                break;
            }
            ++i;
        }
        closedir (dir);
    }
    n = i;
}

BlondieMemoize( int, fsize,  $P(char* filename), $V(filename), 
    {
        struct stat st;
        stat(filename, &st);
        return st.st_size;
    }   
)

BlondieMemoize( int, fexists, $P(char* filename), $V(filename),
    { return access( filename, F_OK ) != -1; }
)
