#include "postgres_con.h"

#include <string.h>

#include <string>

#define MAX_CHAR 300

using namespace std;

connection *postgres_init(const char *host, int port, const char *user,
                          const char *pass, const char *dbname) {
  connection *c = NULL;
  char query[MAX_CHAR];

  sprintf(query, "dbname = %s user = %s password = %s hostaddr = %s port = %d",
          dbname, user, pass, host, port);

  printf("dbname = %s user = %s password = %s hostaddr = %s port = %d", dbname,
         user, pass, host, port);

  //   connection C("dbname = testdb user = postgres password = cohondob \
    //   hostaddr = 127.0.0.1 port = 5432");

  try {
    c = new connection(query);

    if (c->is_open()) {
      printf("Opened database successfully: %s\n", c->dbname());
    } else {
      fprintf(stderr, "Can't open database\n");
      exit(1);
    }
  } catch (const std::exception &e) {
    fprintf(stderr, "Error: %s", e.what());

    exit(1);
  }

  return c;
}

void postgres_disconnect(connection *c) { c->disconnect(); }
 
void postgres_insert(connection *c, char *query) {
  /* Create SQL statement */
  //Example query
  // char *query =
  //     "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
  //     "VALUES (1, 'Paul', 32, 'California', 20000.00 ); ";

  try {
    /* Create a transactional object. */
    work W(*c);

    /* Execute SQL query */
    W.exec(query);
    W.commit();

    printf("Records created successfully\n");
  } catch (const std::exception &e) {
    fprintf(stderr, "Error al cargar datos: %s", e.what());
  }
}

void postgres_create_table(connection *c, char *sql) {
  
  try {
    /* Create a transactional object. */
    work W(*c);

    /* Execute SQL query */
    W.exec(sql);
    W.commit();
    printf("Table created successfully\n");

  } catch (const std::exception &e) {
    fprintf(stderr, "Error al cargar datos: %s", e.what());
    // return 1;
  }
}

void postgres_execute_query_copy_from_csv(connection *c, char *param_sql,
                                          char *filename) {
  printf("Filename con :%s \n", filename);
  char sql[1500] = "";
  /* Create SQL statement */
  strcat(sql, param_sql);
  strcat(sql, filename);
  strcat(sql, "' DELIMITER ',' CSV HEADER;");
  // printf("sql :%s \n",sql);

  try {
    /* Create a transactional object. */
    work W(*c);

    /* Execute SQL query */
    W.exec(sql);
    W.commit();
    printf("Execute query successfully\n");

  } catch (const std::exception &e) {
    fprintf(stderr, "Error al cargar datos: %s", e.what());
    // return 1;
  }
}

void postgres_execute_query(connection *c, char *sql) {
  try {
    /* Create a transactional object. */
    work W(*c);

    /* Execute SQL query */
    W.exec(sql);
    W.commit();
    printf("Execute query successfully\n");

  } catch (const std::exception &e) {
    fprintf(stderr, "Error al cargar datos: %s", e.what());
    // return 1;
  }
}

//Función de los hilos
void *hiloInsert(void *paramIn){
  tparam param1;
   param1 = *(tparam *) paramIn;
 
  connection *c; 
  char *sql;

  c = param1.c;
  sql = param1.query_param;
  //printf("%s %d\n",paramIn->c, paramIn->query_param);

   try {
    /* Create a transactional object. */
    work W(*c);

    /* Execute SQL query */
    W.exec(sql);
    W.commit();
    printf("Execute query successfully\n");

  } catch (const std::exception &e) {
    fprintf(stderr, "Error al cargar datos: %s", e.what());
    // return 1;
  }


}
