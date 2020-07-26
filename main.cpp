#include <iostream>
#include <pqxx/pqxx>

#include "file_read.h"
#include "lib_querys.h"
#include "postgres_con.h"

using namespace std;
using namespace pqxx;

const char* dbname = "snie";

char* ruta_csv =
    "/home/ross/Documentos/CINVESTAV/cuatri3/ComputoCientifico/covid/"
    "migracion-db-cov/datos_abiertos_covid19/nuevo";
char* dst =
    "/home/ross/Documentos/CINVESTAV/cuatri3/ComputoCientifico/covid/"
    "migracion-db-cov/datos_abiertos_covid19/anteriores";

int main(int argc, char* argv[]) {
  // dirname = argv[1];

  char filename[MAXCHAR];
  // dir's path of csv
  load_data(ruta_csv, filename);
  printf("Filename main :%s \n", filename);

  char* sql;
  const char *postgres_host, *postgres_user, *postgres_pass;
  int postgres_port;

  if (argc < 3) {
    printf(
        "Use: main.o <POSTGRES_HOST> <POSTGRES_PORT> <POSTGRES_USER?> "
        "<POSTGRES_PASS?>");
    exit(1);
  }

  postgres_host = argv[1];
  postgres_port = atoi(argv[2]);
  postgres_user = (argc > 3) ? argv[3] : "";
  postgres_pass = (argc > 4) ? argv[4] : "";

  connection* c = postgres_init(postgres_host, postgres_port, postgres_user,
                                postgres_pass, dbname);
  // create table temporary
  postgres_create_table(c, sql_create_table_temp);
  postgres_execute_query_copy_from_csv(c, sql_copy_from_file, filename);

  postgres_execute_query(c, sql_truncate_pacientes_cascade);
  // falta hacer el truncate a las tablas
  postgres_execute_query(c, sql_insert_pacientes);

  // estas con hilos, pero cuales????
  postgres_execute_query(c, sql_insert_complicaciones);
  postgres_execute_query(c, sql_insert_padecimientos);
  postgres_execute_query(c, sql_insert_datos_generales);

  postgres_execute_query(c, sql_drop_temp);
  postgres_execute_query(c, sql_commit);

  postgres_disconnect(c);

  // Luego  de esto hay que mover el archivo
  move_file(filename, dst);

  return 0;
}