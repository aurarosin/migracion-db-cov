#include <iostream>
#include <pqxx/pqxx>

#include "file_read.h"
#include "postgres_con.h"

using namespace std;
using namespace pqxx;

const char* dbname = "snie";

int main(int argc, char* argv[]) {
  // dirname = argv[1];

  // load_data("./datos_abiertos_covid19");
  char filename[MAXCHAR];
  load_data(
      "/home/ross/Documentos/CINVESTAV/cuatri3/ComputoCientifico/covid/"
      "migracion-db-cov/datos_abiertos_covid19",
      filename);
  printf("Filename main :%s \n", filename);

  char* sql;
  const char *postgres_host, *postgres_user, *postgres_pass;
  int postgres_port;

  if (argc < 3) {
    printf("Use: main.o <POSTGRES_HOST> <POSTGRES_PORT> <POSTGRES_USER?> <POSTGRES_PASS?>"); exit(1);
  }

  postgres_host = argv[1];
  postgres_port = atoi(argv[2]);
  postgres_user = (argc > 3) ? argv[3] : "";
  postgres_pass = (argc > 4) ? argv[4] : "";

  connection *c = postgres_init(postgres_host, postgres_port, postgres_user,
  postgres_pass, dbname);
  // postgres_create_table(c);
  
  postgres_execute_query_copy_from_csv(c,sql_copy_from_file,filename);
  postgres_disconnect(c);

  return 0;
}