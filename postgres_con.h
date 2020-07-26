#include <pqxx/pqxx>

using namespace pqxx;

connection *postgres_init(const char *host, int port, const char *user,
                          const char *pass, const char *dbname);
void postgres_disconnect(connection *c);

void postgres_create_table(connection *c, char *sql);
void postgres_insert(connection *c, char *query);
void postgres_execute_query(connection *c, char *sql);
void postgres_execute_query_copy_from_csv(connection *c, char *param_sql,
                                          char *filename);