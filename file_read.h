#ifndef FILE_READ_H
#define FILE_READ_H
 
#define MAXCHAR 500

bool isDatFile(char const *name);
int load_from_file(char *filename);
void load_data(char *dirname, char *filename_out);
void move_file(char *filename, char *dst); 

#endif /* file_read.h */




