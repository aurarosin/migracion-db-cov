#include <pqxx/pqxx>

using namespace pqxx;

static char sql_copy_from_file[] = "COPY snie.temp1(FECHA_ACTUALIZACION, ID_REGISTRO, ORIGEN, SECTOR, ENTIDAD_UM, SEXO,"\
                         "ENTIDAD_NAC, ENTIDAD_RES, MUNICIPIO_RES, TIPO_PACIENTE, FECHA_INGRESO,"\
                         "FECHA_SINTOMAS, FECHA_DEF, INTUBADO, NEUMONIA, EDAD, NACIONALIDAD, EMBARAZO,"\
                          "HABLA_LENGUA_INDIG, DIABETES, EPOC, ASMA,INMUSUPR, HIPERTENSION, OTRA_COM,"\
                          "CARDIOVASCULAR, OBESIDAD, RENAL_CRONICA, TABAQUISMO, OTRO_CASO, RESULTADO,"\
                          "MIGRANTE, PAIS_NACIONALIDAD, PAIS_ORIGEN, UCI)" \
                          "FROM '";

connection *postgres_init(const char *host, int port, const char *user,
                         const char *pass, const char *dbname);
void postgres_disconnect(connection *c);

void postgres_create_table(connection *c);
void postgres_execute_query(connection *c, char *sql);
void postgres_execute_query_copy_from_csv(connection *c,  char *param_sql, char *filename);