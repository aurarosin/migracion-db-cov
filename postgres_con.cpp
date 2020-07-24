#include "postgres_con.h"

#include <string>
#include <string.h>

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

void postgres_insert(connection *c) {
  /* Create SQL statement */
  char *query =
      "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
      "VALUES (1, 'Paul', 32, 'California', 20000.00 ); ";

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

void postgres_create_table(connection *c) {
  // void postgres_create_table(connection *c, char *sql) {
  char *sql;
  /* Create SQL statement */
  // Crate temporary table for file data
  sql =
      "CREATE TABLE snie.temp1("
      "FECHA_ACTUALIZACION character varying ,"
      "ID_REGISTRO character varying ,"
      "ORIGEN character varying ,"
      "SECTOR character varying ,"
      "ENTIDAD_UM character varying ,"
      "SEXO character varying ,"
      "ENTIDAD_NAC character varying ,"
      "ENTIDAD_RES character varying ,"
      "MUNICIPIO_RES character varying,"
      "TIPO_PACIENTE character varying,"
      "FECHA_INGRESO character varying,"
      "FECHA_SINTOMAS character varying,"
      "FECHA_DEF character varying,"
      "INTUBADO character varying,"
      "NEUMONIA character varying,"
      "EDAD character varying,"
      "NACIONALIDAD character varying,"
      "EMBARAZO character varying,"
      "HABLA_LENGUA_INDIG character varying,"
      "DIABETES character varying,"
      "EPOC character varying,"
      "ASMA character varying,"
      "INMUSUPR character varying,"
      "HIPERTENSION character varying,"
      "OTRA_COM character varying,"
      "CARDIOVASCULAR character varying,"
      "OBESIDAD character varying,"
      "RENAL_CRONICA character varying,"
      "TABAQUISMO character varying,"
      "OTRO_CASO character varying,"
      "RESULTADO character varying,"
      "MIGRANTE character varying,"
      "PAIS_NACIONALIDAD character varying,"
      "PAIS_ORIGEN character varying,"
      "UCI character varying );";
  
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

// void postgres_execute_query(connection *c, char *sql);
// void postgres_execute_query_param(connection *c,  char *param_sql, char *filename);


void postgres_execute_query_copy_from_csv(connection *c,  char *param_sql, char *filename){
// void postgres_execute_query(connection *c, char *filename) {
  
    printf("Filename con :%s \n",filename);
  char sql[1500]="";
  /* Create SQL statement */
  strcat(sql, param_sql);
  strcat(sql, filename);                          
  strcat(sql, "' DELIMITER ',' CSV HEADER;");
  printf("sql :%s \n",sql);
//**********************
  // strcat(sql,   "COPY snie.temp1(FECHA_ACTUALIZACION, ID_REGISTRO, ORIGEN, SECTOR, ENTIDAD_UM, SEXO,"\
  //                        "ENTIDAD_NAC, ENTIDAD_RES, MUNICIPIO_RES, TIPO_PACIENTE, FECHA_INGRESO,"\
  //                        "FECHA_SINTOMAS, FECHA_DEF, INTUBADO, NEUMONIA, EDAD, NACIONALIDAD, EMBARAZO,"\
  //                         "HABLA_LENGUA_INDIG, DIABETES, EPOC, ASMA,INMUSUPR, HIPERTENSION, OTRA_COM,"\
  //                         "CARDIOVASCULAR, OBESIDAD, RENAL_CRONICA, TABAQUISMO, OTRO_CASO, RESULTADO,"\
  //                         "MIGRANTE, PAIS_NACIONALIDAD, PAIS_ORIGEN, UCI)" \
  //                         "FROM '");
  // strcat(sql, filename);                          
  // strcat(sql, "' DELIMITER ',' CSV HEADER;");
  // printf("sql :%s \n",sql);
  //Query copia archivo a tabla nueva, temporal para introducir los datos  *********************
  // sql =  "COPY snie.temp1(FECHA_ACTUALIZACION, ID_REGISTRO, ORIGEN, SECTOR, ENTIDAD_UM, SEXO,"\
  //                        "ENTIDAD_NAC, ENTIDAD_RES, MUNICIPIO_RES, TIPO_PACIENTE, FECHA_INGRESO,"\
  //                        "FECHA_SINTOMAS, FECHA_DEF, INTUBADO, NEUMONIA, EDAD, NACIONALIDAD, EMBARAZO,"\
  //                         "HABLA_LENGUA_INDIG, DIABETES, EPOC, ASMA,INMUSUPR, HIPERTENSION, OTRA_COM,"\
  //                         "CARDIOVASCULAR, OBESIDAD, RENAL_CRONICA, TABAQUISMO, OTRO_CASO, RESULTADO,"\
  //                         "MIGRANTE, PAIS_NACIONALIDAD, PAIS_ORIGEN, UCI)" \
  //                         "FROM "\
  //                         "'/home/ross/Documentos/CINVESTAV/cuatri3/ComputoCientifico/covid/migracion-db-cov/datos_abiertos_covid19/200604COVID19MEXICO1.csv' "\
  //                         "DELIMITER ',' CSV HEADER;";
//@esto no lo he tocado
  // sql = "CREATE SEQUENCE snie.pacientes_sequence "\
  //       "start 1 "
  //       "increment 1;";

  // sql =
  //     "INSERT INTO snie.pacientes"
  //     "(id_registro"
  //     ",clave_origen"
  //     ",clave_sector"
  //     ",fecha_actualizacion"
  //     ",fecha_ingreso"
  //     ",fecha_sintoma"
  //     ",fecha_fallecimiento"
  //     ",clave_entidad_unidad_medica"
  //     ",clave_tipo_paciente) "
  //     "SELECT "
  //     "ID_REGISTRO"
  //     ",CAST(ORIGEN AS SMALLINT) "
  //     ",CAST(SECTOR AS SMALLINT)"
  //     ",CAST(FECHA_ACTUALIZACION AS DATE) "
  //     ",CAST(FECHA_INGRESO AS DATE)"
  //     ",CAST(FECHA_SINTOMAS AS DATE)"
  //     ",FECHA_DEF"
  //     ",CAST(ENTIDAD_UM AS SMALLINT )    "
  //     ",CAST(TIPO_PACIENTE AS SMALLINT) "
  //     "FROM snie.temp1";

  // sql =
  //     "INSERT INTO snie.complicaciones"
  //     "(id_paciente"
  //     ",intubado"
  //     ",neumonia"
  //     ",inmusupr"
  //     ",clave_resultados"
  //     ",UIC"
  //     ",otra_complicacion"
  //     ",clave_contagio)"
  //     "select "
  //     "p.id_paciente"
  //     ",CAST(INTUBADO AS SMALLINT)"
  //     ",CAST(NEUMONIA AS SMALLINT)"
  //     ",CAST(INMUSUPR AS SMALLINT)"
  //     ",CAST(RESULTADO AS SMALLINT)"
  //     ",CAST(UCI AS SMALLINT)"
  //     ",CAST(OTRA_COM AS SMALLINT)"
  //     ",1	       "
  //     " FROM snie.temp1 a"
  //     " inner join snie.pacientes p on a.ID_REGISTRO=p.id_registro ;";

//   sql = "INSERT INTO snie.padecimientos "\
//            "(id_paciente "\
//            ",diabetes "\
//            ",EPOC "\
//            ",asma"\
//            ",hipertension "\
//            ",cardiovascular "\
//            ",renal_cronica "\
//            ",embarazo "\
//            ",obesidad "\
//            ",tabaquismo "\
//            ",otro_caso) "\
// "select "\
// "p.id_paciente"\
// ",CAST(DIABETES AS SMALLINT)"\
// ",CAST(EPOC AS SMALLINT)"\
// ",CAST(ASMA AS SMALLINT)"\
// ",CAST(HIPERTENSION AS SMALLINT)"\
// ",CAST(CARDIOVASCULAR AS SMALLINT)"\
// ",CAST(RENAL_CRONICA AS SMALLINT)"\
// ",CAST(EMBARAZO AS SMALLINT)"\
// ",CAST(OBESIDAD AS SMALLINT)"\
// ",CAST(TABAQUISMO AS SMALLINT)"\
// ",CAST(OTRO_CASO AS SMALLINT)"\

// " FROM snie.temp1 a"
// " inner join snie.pacientes p on a.ID_REGISTRO=p.id_registro;";

// sql = "INSERT INTO snie.datos_generales"\
//            "(id_paciente"\
//            ",edad"\
//            ",clave_entiadad_nacimiento"\
//            ",clave_entidad_residencia"\
//            ",clave_municipio_residencia"\
//            ",clave_lengua_indigena"\
//            ",clave_genero"\
//            ",clave_nacionalidad"\
//            ",clave_migrante"\
//            ",clave_pais"\
//            ",clave_pais_orige)"\
// "select "\
// "p.id_paciente,"\
// "CAST(EDAD AS SMALLINT),"\
// /*"cast(substring(ENTIDAD_NAC,2,2)  as smallint) entidad_nac, "\*/
// "case "\ 
// "when(substring(ENTIDAD_NAC,0,1) ='0') then cast(substring(ENTIDAD_NAC,2,2) as smallint) "\
// "else cast(entidad_nac as smallint)  "\
// "end, "\

// /*"cast(substring(ENTIDAD_RES,2,2) as smallint ) entidad_res, "\*/
// "case  "\
// "when(substring(ENTIDAD_RES,0,1) ='0') then cast(substring(ENTIDAD_RES,2,2) as smallint) "\
// "else cast(entidad_RES as smallint)  "\
// "end, "\

// "case "\
// "when length(MUNICIPIO_RES)=5 then substring (MUNICIPIO_RES,2,3) "\
// "when length(MUNICIPIO_RES)=2 then MUNICIPIO_RES "\
// "else MUNICIPIO_RES end municipio_Res, "\
// "CAST(HABLA_LENGUA_INDIG AS SMALLINT), "\
// "CAST(SEXO AS SMALLINT), "\
// "CAST(NACIONALIDAD AS SMALLINT), "\
// "CAST(MIGRANTE AS SMALLINT), "\
// "case "\
// "when PAIS_NACIONALIDAD='Alemania' then CAST(1 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='ArchipiÃ©lago de Svalbard' then CAST(2 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Argelia' then CAST(3 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Argentina' then CAST(4 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='AscensiÃ³n' then CAST(5 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Australia' then CAST(6 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Austria' then CAST(7 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='BÃ©lgica' then CAST(8 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Bangladesh' then CAST(9 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Belice' then CAST(10 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Bolivia' then CAST(11 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Bosnia y Herzegovina' then CAST(12 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Brasil' then CAST(13 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='CamerÃºn' then CAST(14 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='CanadÃ¡' then CAST(15 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Chile' then CAST(16 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='China' then CAST(17 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Colombia' then CAST(18 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Commonwealth de Dominica' then CAST(19 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Costa de Marfil' then CAST(20 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Cuba' then CAST(21 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Dinamarca' then CAST(22 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Ecuador' then CAST(23 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Egipto' then CAST(24 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='El Salvador' then CAST(25 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Eritrea' then CAST(26 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Eslovaquia' then CAST(27 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Eslovenia' then CAST(28 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='EspaÃ±a' then CAST(29 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Estados Unidos de AmÃ©rica' then CAST(30 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Estados Unidos de Am?ica' then CAST(30 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Filipinas' then CAST(31 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Finlandia' then CAST(32 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Francia' then CAST(33 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Gran BretaÃ±a (Reino Unido)' then CAST(34 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Grecia' then CAST(35 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Guatemala' then CAST(36 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='HaitÃ­' then CAST(37 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Holanda' then CAST(38 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='HungrÃ­a' then CAST(39 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='India' then CAST(40 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Indonesia' then CAST(41 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='IrÃ¡n' then CAST(42 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Irlanda' then CAST(43 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Islandia' then CAST(44 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Islas VÃ­rgenes de Estados Unidos de AmÃ©rica' then CAST(45 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Israel' then CAST(46 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Italia' then CAST(47 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='JapÃ³n' then CAST(48 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Letonia' then CAST(49 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Libia' then CAST(50 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='MÃ©xico' then CAST(51 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Macao' then CAST(52 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Malasia' then CAST(53 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Micronesia' then CAST(54 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Nicaragua' then CAST(55 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Noruega' then CAST(56 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Otro' then CAST(57 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='PakistÃ¡n' then  CAST(59 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Paraguay' then CAST(60 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Per?' then CAST(61 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='PerÃº' then CAST(61 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Polonia' then CAST(62 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Portugal' then CAST(63 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Principado de MÃ³naco' then CAST(64 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='RepÃºblicaRepública Checa y RepÃºblica Eslovaca' then CAST(65 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='RepÃºblica de Angola' then CAST(66 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='RepÃºblica de Corea' then CAST(67 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='RepÃºblica de Costa Rica' then CAST(68 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='RepÃºblica de Honduras' then CAST(69 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='RepÃºblica de Mauricio' then CAST(70 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='RepÃºblica de PanamÃ¡' then CAST(71 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='RepÃºblica Dominicana' then CAST(72 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='RepÃºblica Oriental del Uruguay' then CAST(73 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Rumania' then CAST(74 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Rusia' then CAST(75 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Suecia' then CAST(76 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Suiza' then CAST(77 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='TaiwÃ¡n' then CAST(78 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Trieste' then CAST(79 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='TurquÃ­a' then CAST(80 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Ucrania' then CAST(81 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Venezuela' then CAST(82 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Zimbabwe' then CAST(83 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='Zona Neutral' then CAST(84 AS SMALLINT) "\
// "when PAIS_NACIONALIDAD='99' then CAST(99 AS SMALLINT) "\
// /*"else PAIS_NACIONALIDAD "\ */
// "end, "\
// "case "\
// "when PAIS_origen='Alemania' then 1 "\
// "when PAIS_origen='ArchipiÃ©lago de Svalbard' then 2 "\
// "when PAIS_origen='Argelia' then 3 "\
// "when PAIS_origen='Argentina' then 4 "\
// "when PAIS_origen='AscensiÃ³n' then 5 "\
// "when PAIS_origen='Australia' then 6 "\
// "when PAIS_origen='Austria' then 7 "\
// "when PAIS_origen='BÃ©lgica' then 8 "\
// "when PAIS_origen='Bangladesh' then 9 "\
// "when PAIS_origen='Belice' then 10 "\
// "when PAIS_origen='Bolivia' then 11 "\
// "when PAIS_origen='Bosnia y Herzegovina' then 12 "\
// "when PAIS_origen='Brasil' then 13 "\
// "when PAIS_origen='CamerÃºn' then 14 "\
// "when PAIS_origen='Camer?n' then 14 "\
// "when PAIS_origen='CanadÃ¡' then 15 "\
// "when PAIS_origen='Canad?' then 15 "\
// "when PAIS_origen='Chile' then 16 "\
// "when PAIS_origen='China' then 17 "\
// "when PAIS_origen='Colombia' then 18 "\
// "when PAIS_origen='Commonwealth de Dominica' then 19 "\
// "when PAIS_origen='Costa de Marfil' then 20 "\
// "when PAIS_origen='Cuba' then 21 "\
// "when PAIS_origen='Dinamarca' then 22 "\
// "when PAIS_origen='Ecuador' then 23 "\
// "when PAIS_origen='Egipto' then 24 "\
// "when PAIS_origen='El Salvador' then 25 "\
// "when PAIS_origen='Eritrea' then 26 "\
// "when PAIS_origen='Eslovaquia' then 27 "\
// "when PAIS_origen='Eslovenia' then 28 "\
// "when PAIS_origen='EspaÃ±a' then 29 "\
// "when PAIS_origen='Espa?' then 29 "\
// "when PAIS_origen='Estados Unidos de AmÃ©rica' then 30 "\
// "when PAIS_origen='Estados Unidos de Am?ica' then 30 "\
// "when PAIS_origen='Filipinas' then 31 "\
// "when PAIS_origen='Finlandia' then 32 "\
// "when PAIS_origen='Francia' then 33 "\
// "when PAIS_origen='Gran BretaÃ±a (Reino Unido)' then 34 "\
// "when PAIS_origen='Gran Breta? (Reino Unido)' then 34 "\
// "when PAIS_origen='Grecia' then 35 "\
// "when PAIS_origen='Guatemala' then 36 "\
// "when PAIS_origen='Hait?' then 37 "\
// "when PAIS_origen='Hait?' then 37 "\
// "when PAIS_origen='HaitÃ­' then 37 "\
// "when PAIS_origen='Holanda' then 38 "\
// "when PAIS_origen='HungrÃ­a' then 39 "\
// "when PAIS_origen='India' then 40 "\
// "when PAIS_origen='Indonesia' then 41 "\
// "when PAIS_origen='IrÃ¡n' then 42 "\
// "when PAIS_origen='Irlanda' then 43 "\
// "when PAIS_origen='Islandia' then 44 "\
// "when PAIS_origen='Islas VÃ­rgenes de Estados Unidos de AmÃ©rica' then 45 "\
// "when PAIS_origen='Israel' then 46 "\
// "when PAIS_origen='Italia' then 47 "\
// "when PAIS_origen='JapÃ³n' then 48 "\
// "when PAIS_origen='Jap?' then 48 "\
// "when PAIS_origen='Letonia' then 49 "\
// "when PAIS_origen='Libia' then 50 "\
// "when PAIS_origen='MÃ©xico' then 51 "\
// "when PAIS_origen='Macao' then 52 "\
// "when PAIS_origen='Malasia' then 53 "\
// "when PAIS_origen='Micronesia' then 54 "\
// "when PAIS_origen='Nicaragua' then 55 "\
// "when PAIS_origen='Noruega' then 56 "\
// "when PAIS_origen='Otro' then 57 "\
// "when PAIS_origen='PakistÃ¡n' then  59 "\
// "when PAIS_origen='Paraguay' then 60 "\
// "when PAIS_origen='PerÃº' then 61 "\
// "when PAIS_origen='Per?' then 61 "\
// "when PAIS_origen='Polonia' then 62 "\
// "when PAIS_origen='Portugal' then 63 "\
// "when PAIS_origen='Principado de MÃ³naco' then 64 "\
// "when PAIS_origen='RepÃºblicaRepública Checa y RepÃºblica Eslovaca' then 65 "\
// "when PAIS_origen='Rep?blica Checa y Rep?blica Eslovaca' then 65 "\
// "when PAIS_origen='RepÃºblica de Angola' then 66 "\
// "when PAIS_origen='RepÃºblica de Corea' then 67 "\
// "when PAIS_origen='RepÃºblica de Costa Rica' then 68 "\
// "when PAIS_origen='RepÃºblica de Honduras' then 69 "\
// "when PAIS_origen='Rep?blica de Honduras' then 69 "\
// "when PAIS_origen='RepÃºblica de Mauricio' then 70 "\
// "when PAIS_origen='RepÃºblica de PanamÃ¡' then 71 "\
// "when PAIS_origen='RepÃºblica de PanamÃ¡' then 71 "\
// "when PAIS_origen='RepÃºblica Dominicana' then 72 "\
// "when PAIS_origen='Rep?blica Dominicana' then 72 "\
// "when PAIS_origen='RepÃºblica Oriental del Uruguay' then 73 "\
// "when PAIS_origen='Rumania' then 74 "\
// "when PAIS_origen='Rusia' then 75 "\
// "when PAIS_origen='Suecia' then 76 "\
// "when PAIS_origen='Suiza' then 77 "\
// "when PAIS_origen='TaiwÃ¡n' then 78 "\
// "when PAIS_origen='Trieste' then 79 "\
// "when PAIS_origen='TurquÃ­a' then 80 "\
// "when PAIS_origen='Turqu?' then 80 "\
// "when PAIS_origen='Ucrania' then 81 "\
// "when PAIS_origen='Venezuela' then 82 "\
// "when PAIS_origen='Zimbabwe' then 83 "\
// "when PAIS_origen='Zona Neutral' then 84 "\
// "when PAIS_origen='99' then 99  "\
// "when PAIS_origen='97' then 97  "\
// /*"else PAIS_origen  "\*/
// "end "\
// " FROM snie.temp1 a "\
// " inner join snie.pacientes p on a.ID_REGISTRO=p.id_registro";

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