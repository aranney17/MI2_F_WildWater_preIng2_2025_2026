typedef struct {
	char* col1;
	char* col2;
	char* col3;
	char* volume;
	char* leak;
}Info;

typedef enum { SOURCE_USINE, USINE, USINE_STOCKAGE, STOCKAGE_JONCTION, JONCTION_RACC, RACC_USAGER, INCONNU } TypeLigne;
