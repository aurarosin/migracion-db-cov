#include <pthread.h>

#include <iostream>
#include <pqxx/pqxx>

#include "file_read.h"
#include "lib_querys.h"
#include "postgres_con.h"

using namespace std;
using namespace pqxx;

const char* dbname = "snie";

int main(int argc, char* argv[]) {

  const char *postgres_host, *postgres_user, *postgres_pass;
  int postgres_port;
  char *ruta_csv, *dst;
  if (argc < 5) {
    printf(
        "Use: main.o <POSTGRES_HOST> <POSTGRES_PORT> <POSTGRES_USER?> "
        "<POSTGRES_PASS?> <CSV_DIR> <DST_FILE>");
    exit(1);
  }

  postgres_host = argv[1];
  postgres_port = atoi(argv[2]);
  postgres_user = (argc > 3) ? argv[3] : "";
  postgres_pass = (argc > 4) ? argv[4] : "";
  ruta_csv = argv[5];
  dst = argv[6];

  char filename[MAXCHAR];
  // dir's path of csv
  // DEBERIA VALIDAR QUE EXISTA EL ARCHIVO
  load_data(ruta_csv, filename);
  printf("Filename main :%s \n", filename);

  connection* c = postgres_init(postgres_host, postgres_port, postgres_user,
                                postgres_pass, dbname);
  // create table temporary
  postgres_create_table(c, query_create_table_temp);
  postgres_execute_query_copy_from_csv(c, query_copy_from_file, filename);

  postgres_execute_query(c, query_truncate_pacientes_cascade);

  postgres_execute_query(c, query_insert_pacientes);

  pthread_t thd1, thd2, thd3;
  tparam param_complicaciones, param_padecimientos, param_datos_generales;

  param_complicaciones.c = c;
  param_complicaciones.query_param = query_insert_complicaciones;

  param_padecimientos.c = c;
  param_padecimientos.query_param = query_insert_padecimientos;

  param_datos_generales.c = c;
  param_datos_generales.query_param = query_insert_datos_generales;

  // postgres_execute_query(c, query_insert_complicaciones);
  pthread_create(&thd1, NULL, hiloInsert, (void*)&param_complicaciones);
  pthread_join(thd1, NULL);

  // postgres_execute_query(c, query_insert_padecimientos);
  pthread_create(&thd2, NULL, hiloInsert, (void*)&param_padecimientos);
  pthread_join(thd2, NULL);

  // postgres_execute_query(c, query_insert_datos_generales);
  pthread_create(&thd3, NULL, hiloInsert, (void*)&param_datos_generales);
  pthread_join(thd3, NULL);

  // esto cuando terminen los hilos
  postgres_execute_query(c, query_drop_temp);
  postgres_execute_query(c, query_commit);

  postgres_disconnect(c);

  // Move file
  move_file(filename, dst);

  return 0;
}
