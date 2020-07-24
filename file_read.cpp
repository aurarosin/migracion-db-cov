#include "file_read.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isDatFile(char const *name) {
  size_t len = strlen(name);
  //   lo voy a ocupar para el reporte final
  //   printf("name :%s \n",name);
  return len > 4 && strcmp(name + len - 4, ".csv") == 0;
}

int load_from_file(char *filename) {
  char line[MAXCHAR];
  int lines;

  FILE *file = fopen(filename, "r");
  if (file == NULL) return 0;

  // Lectura de lineas en el archivo.
  for (lines = 0; fscanf(file, "%[^\n]\n", line) != EOF; lines++) {
    //
    printf("Line %d: %s \n", lines, line);
  }

  fclose(file);
  printf("End-1\n");

  return lines;
}

void load_data(char *dirname, char *filename_out) {
  
  DIR *d = opendir(dirname);
  int files_count = 0, total_reg = 0;

  if (d) {
    struct dirent *dir;

    for (files_count = 0; (dir = readdir(d)) != NULL; files_count++) {
      if (isDatFile(dir->d_name)) {
        char filename[MAXCHAR];
        strcpy(filename, dirname);
        strcat(filename, "/");
        strcat(filename, dir->d_name);
        // printf("Filename :%s \n",filename);

        total_reg += load_from_file(filename);
        printf("End\n");
        strcpy(filename_out, filename);
        // filename_out = &filename;
        // printf("Filename :%s \n",filename_out);
      }
    }
    
    closedir(d);
  } else {
    printf("No está el directorio");  // No está el directorio
  }

  // void move_file(char *filename) {


  // }
}
