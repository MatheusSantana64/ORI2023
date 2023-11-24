#include "ORI_T01_HEADER.h"

/* Funções auxiliares para o qsort.
 * Com uma pequena alteração, é possível utilizá-las no bsearch, assim, evitando código duplicado.
 * */

/* Função de comparação entre chaves do índice corredores_idx */
int qsort_corredores_idx(const void *a, const void *b) {
    return strcmp( ( (corredores_index *)a )->id_corredor, ( (corredores_index *)b )->id_corredor);
}

/* Função de comparação entre chaves do índice veiculos_idx */
int qsort_veiculos_idx(const void *a, const void *b) {
    return strcmp( ( (veiculos_index *)a )->id_veiculo, ( (veiculos_index *)b )->id_veiculo);
}

/* Função de comparação entre chaves do índice pistas_idx */
int qsort_pistas_idx(const void *a, const void *b) {
    return strcmp( ( (pistas_index *)a )->id_pista, ( (pistas_index *)b )->id_pista);
}

/* Função de comparação entre chaves do índice corridas_idx */
int qsort_corridas_idx(const void *a, const void *b) {
	return strcmp( ( (corridas_index *)a )->id_pista, ( (corridas_index *)b )->id_pista);
}

/* Funções de comparação apenas entre data de ocorrencia do índice corridas_idx */
int qsort_data_idx(const void *a, const void *b){
	return strcmp( ( (corridas_index *)a )->ocorrencia, ( (corridas_index *)b )->ocorrencia);
}

/* Função de comparação entre chaves do índice nome_pista_idx */
int qsort_nome_pista_idx(const void *a, const void *b){
	return strcmp( ( (nome_pista_index *)a )->nome, ( (nome_pista_index *)b )->nome);
}

/* Função de comparação entre chaves do índice preco_veiculo_idx */
int qsort_preco_veiculo_idx(const void *a, const void *b){
    preco_veiculo_index *veiculo_a = (preco_veiculo_index *)a;
    preco_veiculo_index *veiculo_b = (preco_veiculo_index *)b;
    if(veiculo_a->preco < veiculo_b->preco) return -1;
    else if(veiculo_a->preco > veiculo_b->preco) return 1;
    else return strcmp(veiculo_a->id_veiculo, veiculo_b->id_veiculo);
}

/* Função de comparação entre chaves do índice secundário de corredor_veiculos_secundario_idx */
int qsort_corredor_veiculos_secundario_idx(const void *a, const void *b){
	return strcmp( ( (corredor_veiculos_secundario_index *)a )->chave_secundaria, ( (corredor_veiculos_secundario_index *)b )->chave_secundaria);
}

/* Cria o índice respectivo */
//criar_corredores_idx() não deve ser modificada
void criar_corredores_idx() {
    if (!corredores_idx)
        corredores_idx = malloc(MAX_REGISTROS * sizeof(corredores_index));
 
    if (!corredores_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
 
    for (unsigned i = 0; i < qtd_registros_corredores; ++i) {
        Corredor c = recuperar_registro_corredor(i);
 
        if (strncmp(c.id_corredor, "*|", 2) == 0)
            corredores_idx[i].rrn = -1; // registro excluído
        else
            corredores_idx[i].rrn = i;
 
        strcpy(corredores_idx[i].id_corredor, c.id_corredor);
    }
 
    qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
    printf(INDICE_CRIADO, "corredores_idx");
}

void criar_veiculos_idx() {
    if (!veiculos_idx)
        veiculos_idx = malloc(MAX_REGISTROS * sizeof(veiculos_index));

    if (!veiculos_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    for (unsigned i = 0; i < qtd_registros_veiculos; ++i) {
        Veiculo v = recuperar_registro_veiculo(i);

        if (strncmp(v.id_veiculo, "*|", 2) == 0)
            veiculos_idx[i].rrn = -1; // registro excluído
        else
            veiculos_idx[i].rrn = i;

        strcpy(veiculos_idx[i].id_veiculo, v.id_veiculo);
    }

    qsort(veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);
    printf(INDICE_CRIADO, "veiculos_idx");
}

void criar_pistas_idx() {
    if (!pistas_idx)
        pistas_idx = malloc(MAX_REGISTROS * sizeof(pistas_index));

    if (!pistas_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    for (unsigned i = 0; i < qtd_registros_pistas; ++i) {
        Pista p = recuperar_registro_pista(i);

        if (strncmp(p.id_pista, "*|", 2) == 0)
            pistas_idx[i].rrn = -1; // registro excluído
        else
            pistas_idx[i].rrn = i;

        strcpy(pistas_idx[i].id_pista, p.id_pista);
    }

    qsort(pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx);
    printf(INDICE_CRIADO, "pistas_idx");
}

void criar_corridas_idx() {
    if (!corridas_idx)
        corridas_idx = malloc(MAX_REGISTROS * sizeof(corridas_index));

    if (!corridas_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    for (unsigned i = 0; i < qtd_registros_corridas; ++i) {
        Corrida c = recuperar_registro_corrida(i);

        if (strncmp(c.id_pista, "*|", 2) == 0)
            corridas_idx[i].rrn = -1; // registro excluído
        else
            corridas_idx[i].rrn = i;

        strcpy(corridas_idx[i].id_pista, c.id_pista);
        strcpy(corridas_idx[i].ocorrencia, c.ocorrencia);
    }

    qsort(corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx);
    printf(INDICE_CRIADO, "corridas_idx");
}

void criar_nome_pista_idx() {
    if (!nome_pista_idx)
        nome_pista_idx = malloc(MAX_REGISTROS * sizeof(nome_pista_index));

    if (!nome_pista_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    for (unsigned i = 0; i < qtd_registros_pistas; ++i) {
        Pista p = recuperar_registro_pista(i);

        strcpy(nome_pista_idx[i].nome, p.nome);
        strcpy(nome_pista_idx[i].id_pista, p.id_pista);
    }

    qsort(nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx);
    printf(INDICE_CRIADO, "nome_pista_idx");
}

void criar_preco_veiculo_idx() {
    if (!preco_veiculo_idx)
        preco_veiculo_idx = malloc(MAX_REGISTROS * sizeof(preco_veiculo_index));

    if (!preco_veiculo_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    for (unsigned i = 0; i < qtd_registros_veiculos; ++i) {
        Veiculo v = recuperar_registro_veiculo(i);

        preco_veiculo_idx[i].preco = v.preco;
        strcpy(preco_veiculo_idx[i].id_veiculo, v.id_veiculo);
    }

    qsort(preco_veiculo_idx, qtd_registros_veiculos, sizeof(preco_veiculo_index), qsort_preco_veiculo_idx);
    printf(INDICE_CRIADO, "preco_veiculo_idx");
}

void criar_corredor_veiculos_idx() {
    if (!corredor_veiculos_idx.corredor_veiculos_primario_idx)
        corredor_veiculos_idx.corredor_veiculos_primario_idx = malloc(MAX_REGISTROS * sizeof(corredor_veiculos_primario_index));

    if (!corredor_veiculos_idx.corredor_veiculos_primario_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    if (!corredor_veiculos_idx.corredor_veiculos_secundario_idx)
        corredor_veiculos_idx.corredor_veiculos_secundario_idx = malloc(MAX_REGISTROS * sizeof(corredor_veiculos_secundario_index));

    if (!corredor_veiculos_idx.corredor_veiculos_secundario_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    for (unsigned i = 0; i < qtd_registros_corredores; ++i) {
        Corredor c = recuperar_registro_corredor(i);

        for (int j = 0; j < QTD_MAX_VEICULO; ++j) {
            if (strlen(c.veiculos[j]) > 0) {
                strcpy(corredor_veiculos_idx.corredor_veiculos_primario_idx[i].chave_primaria, c.id_corredor);
                corredor_veiculos_idx.corredor_veiculos_primario_idx[i].proximo_indice = -1;

                strcpy(corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].chave_secundaria, c.veiculos[j]);
                corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].primeiro_indice = i;
            }
        }
    }

    qsort(corredor_veiculos_idx.corredor_veiculos_secundario_idx, qtd_registros_corredores, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx);
    printf(INDICE_CRIADO, "corredor_veiculos_idx");
}

/* Exibe um registro com base no RRN */
//exibir_corredor() não deve ser modificada
bool exibir_corredor(int rrn) {
    if (rrn < 0)
        return false;
 
    Corredor c = recuperar_registro_corredor(rrn);
 
    printf("%s, %s, %s, %s, %.2lf\n", c.id_corredor, c.nome, c.apelido, c.cadastro, c.saldo);
    return true;
}

bool exibir_veiculo(int rrn) {
    if (rrn < 0)
        return false;

    Veiculo v = recuperar_registro_veiculo(rrn);

    printf("%s, %s, %s, %s, %d, %d, %d, %.2lf\n", v.id_veiculo, v.marca, v.modelo, v.poder, v.velocidade, v.aceleracao, v.peso, v.preco);
    return true;
}

bool exibir_pista(int rrn) {
    if (rrn < 0)
        return false;

    Pista p = recuperar_registro_pista(rrn);

    printf("%s, %s, %d, %d, %d\n", p.id_pista, p.nome, p.dificuldade, p.distancia, p.recorde);
    return true;
}

bool exibir_corrida(int rrn) {
    if (rrn < 0)
        return false;

    Corrida c = recuperar_registro_corrida(rrn);

    printf("%s, %s, %s, %s\n", c.id_pista, c.ocorrencia, c.id_corredores, c.id_veiculos);
    return true;
}

/* Recupera do arquivo o registro com o RRN informado e retorna os dados nas structs */
//recuperar_registro_corredor() não deve ser modificada
Corredor recuperar_registro_corredor(int rrn) {
	Corredor c;
	char temp[TAM_REGISTRO_CORREDOR + 1], *p;
	strncpy(temp, ARQUIVO_CORREDORES + (rrn * TAM_REGISTRO_CORREDOR), TAM_REGISTRO_CORREDOR);
	temp[TAM_REGISTRO_CORREDOR] = '\0';

	p = strtok(temp, ";");
	strcpy(c.id_corredor, p);
	p = strtok(NULL, ";");
	strcpy(c.nome, p);
	p = strtok(NULL, ";");
	strcpy(c.apelido, p);
	p = strtok(NULL, ";");
	strcpy(c.cadastro, p);
	p = strtok(NULL, ";");
	c.saldo = atof(p);
	p = strtok(NULL, ";");

	for(int i = 0; i < QTD_MAX_VEICULO; ++i)
		c.veiculos[i][0] = '\0';

	if(p[0] != '#') {
		p = strtok(p, "|");

		for(int pos = 0; p; p = strtok(NULL, "|"), ++pos)
			strcpy(c.veiculos[pos], p);
	}

	return c;
}

Veiculo recuperar_registro_veiculo(int rrn) {
    Veiculo v;
    char temp[TAM_REGISTRO_VEICULO + 1], *p;
    strncpy(temp, ARQUIVO_VEICULOS + (rrn * TAM_REGISTRO_VEICULO), TAM_REGISTRO_VEICULO);
    temp[TAM_REGISTRO_VEICULO] = '\0';

    p = strtok(temp, ";");
    strcpy(v.id_veiculo, p);
    p = strtok(NULL, ";");
    strcpy(v.marca, p);
    p = strtok(NULL, ";");
    strcpy(v.modelo, p);
    p = strtok(NULL, ";");
    strcpy(v.poder, p);
    p = strtok(NULL, ";");
    v.velocidade = atoi(p);
    p = strtok(NULL, ";");
    v.aceleracao = atoi(p);
    p = strtok(NULL, ";");
    v.peso = atoi(p);
    p = strtok(NULL, ";");
    v.preco = atof(p);

    return v;
}

Pista recuperar_registro_pista(int rrn) {
    Pista p;
    char temp[TAM_REGISTRO_PISTA + 1], *p_str;
    strncpy(temp, ARQUIVO_PISTAS + (rrn * TAM_REGISTRO_PISTA), TAM_REGISTRO_PISTA);
    temp[TAM_REGISTRO_PISTA] = '\0';

    p_str = strtok(temp, ";");
    strcpy(p.id_pista, p_str);
    p_str = strtok(NULL, ";");
    strcpy(p.nome, p_str);
    p_str = strtok(NULL, ";");
    p.dificuldade = atoi(p_str);
    p_str = strtok(NULL, ";");
    p.distancia = atoi(p_str);
    p_str = strtok(NULL, ";");
    p.recorde = atoi(p_str);

    return p;
}

Corrida recuperar_registro_corrida(int rrn) {
    Corrida c;
    char temp[TAM_REGISTRO_CORRIDA + 1], *p;
    strncpy(temp, ARQUIVO_CORRIDAS + (rrn * TAM_REGISTRO_CORRIDA), TAM_REGISTRO_CORRIDA);
    temp[TAM_REGISTRO_CORRIDA] = '\0';

    p = strtok(temp, ";");
    strcpy(c.id_pista, p);
    p = strtok(NULL, ";");
    strcpy(c.ocorrencia, p);
    p = strtok(NULL, ";");
    strcpy(c.id_corredores, p);
    p = strtok(NULL, ";");
    strcpy(c.id_veiculos, p);

    return c;
}

/* Escreve em seu respectivo arquivo na posição informada (RRN) */
//escrever_registro_corredor() não deve ser modificada
void escrever_registro_corredor(Corredor c, int rrn) {
	char temp[TAM_REGISTRO_CORREDOR + 1], p[100];
	temp[0] = '\0'; p[0] = '\0';

	strcpy(temp, c.id_corredor);
	strcat(temp, ";");
	strcat(temp, c.nome);
	strcat(temp, ";");
	strcat(temp, c.apelido);
	strcat(temp, ";");
	strcat(temp, c.cadastro);
	strcat(temp, ";");
	sprintf(p, "%013.2lf", c.saldo);
	strcat(temp, p);
	strcat(temp, ";");

	for(int i = 0, k = 0; i < QTD_MAX_VEICULO; ++i) {
		if(strlen(c.veiculos[i]) > 0) {
			if (k == 0)
				k = 1;
			else
				strcat(temp, "|");
			strcat(temp, c.veiculos[i]);
		}
	}
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_CORREDOR);

	strncpy(ARQUIVO_CORREDORES + rrn*TAM_REGISTRO_CORREDOR, temp, TAM_REGISTRO_CORREDOR);
}

void escrever_registro_veiculo(Veiculo v, int rrn) {
    char temp[TAM_REGISTRO_VEICULO + 1], p[100];
    temp[0] = '\0'; p[0] = '\0';

    sprintf(temp, "%07d", atoi(v.id_veiculo));
    strcat(temp, ";");
    strcat(temp, v.marca);
    strcat(temp, ";");
    strcat(temp, v.modelo);
    strcat(temp, ";");
    strcat(temp, v.poder);
    strcat(temp, ";");
    sprintf(p, "%04d", v.velocidade);
    strcat(temp, p);
    strcat(temp, ";");
    sprintf(p, "%04d", v.aceleracao);
    strcat(temp, p);
    strcat(temp, ";");
    sprintf(p, "%04d", v.peso);
    strcat(temp, p);
    strcat(temp, ";");
    sprintf(p, "%013.2lf", v.preco);
    strcat(temp, p);
    strcat(temp, ";");

    strpadright(temp, '#', TAM_REGISTRO_VEICULO);

    strncpy(ARQUIVO_VEICULOS + rrn*TAM_REGISTRO_VEICULO, temp, TAM_REGISTRO_VEICULO);
}

void escrever_registro_pista(Pista p, int rrn) {
    char temp[TAM_REGISTRO_PISTA + 1], p_str[100];
    temp[0] = '\0'; p_str[0] = '\0';

    strcpy(temp, p.id_pista);
    strcat(temp, ";");
    strcat(temp, p.nome);
    strcat(temp, ";");
    sprintf(p_str, "%d", p.dificuldade);
    strcat(temp, p_str);
    strcat(temp, ";");
    sprintf(p_str, "%d", p.distancia);
    strcat(temp, p_str);
    strcat(temp, ";");
    sprintf(p_str, "%d", p.recorde);
    strcat(temp, p_str);
    strcat(temp, ";");

    strpadright(temp, '#', TAM_REGISTRO_PISTA);

    strncpy(ARQUIVO_PISTAS + rrn*TAM_REGISTRO_PISTA, temp, TAM_REGISTRO_PISTA);
}

void escrever_registro_corrida(Corrida c, int rrn) {
    char temp[TAM_REGISTRO_CORRIDA + 1];
    temp[0] = '\0';

    strcpy(temp, c.id_pista);
    strcat(temp, ";");
    strcat(temp, c.ocorrencia);
    strcat(temp, ";");
    strcat(temp, c.id_corredores);
    strcat(temp, ";");
    strcat(temp, c.id_veiculos);
    strcat(temp, ";");

    strpadright(temp, '#', TAM_REGISTRO_CORRIDA);

    strncpy(ARQUIVO_CORRIDAS + rrn*TAM_REGISTRO_CORRIDA, temp, TAM_REGISTRO_CORRIDA);
}

/* Funções principais */
void cadastrar_corredor_menu(char *id_corredor, char *nome, char *apelido){
    Corredor novo_corredor;

    // Copia os dados para a nova struct Corredor
    strcpy(novo_corredor.id_corredor, id_corredor);
    strcpy(novo_corredor.nome, nome);
    strcpy(novo_corredor.apelido, apelido);
    novo_corredor.saldo = 0.0;
    current_datetime(novo_corredor.cadastro);

    // Inicializa o array de veículos
    for(int i = 0; i < QTD_MAX_VEICULO; ++i)
        novo_corredor.veiculos[i][0] = '\0';

    // Verifica se o id_corredor já existe
    corredores_index chave;
    strcpy(chave.id_corredor, id_corredor);
    corredores_index *corredor_existente = (corredores_index*) bsearch(&chave, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
    if (corredor_existente != NULL) {
        printf(ERRO_PK_REPETIDA, id_corredor);
        return;
    }

    // Adiciona o novo corredor ao final do arquivo de corredores
    escrever_registro_corredor(novo_corredor, qtd_registros_corredores);

    // Atualiza o índice de corredores
    strcpy(corredores_idx[qtd_registros_corredores].id_corredor, id_corredor);
    corredores_idx[qtd_registros_corredores].rrn = qtd_registros_corredores;

    // Incrementa a quantidade de registros de corredores
    qtd_registros_corredores++;

    // Reordena o índice de corredores
    qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);

    printf(SUCESSO);
}

void remover_corredor_menu(char *id_corredor) {
    corredores_index chave;
    strcpy(chave.id_corredor, id_corredor);

    corredores_index *corredor_encontrado = (corredores_index*) bsearch(&chave, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);

    if (corredor_encontrado == NULL || corredor_encontrado->rrn < 0) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    // Marcar o registro como excluído no arquivo de corredores
    memcpy(ARQUIVO_CORREDORES + corredor_encontrado->rrn * TAM_REGISTRO_CORREDOR, "*|", 2);

    // Marcar o registro como excluído no índice de corredores
    corredor_encontrado->rrn = -1;

    printf(SUCESSO);
}

void adicionar_saldo_menu(char *id_corredor, double valor) {
	adicionar_saldo(id_corredor, valor, true);
}

void adicionar_saldo(char *id_corredor, double valor, bool flag){
    corredores_index chave;
    strcpy(chave.id_corredor, id_corredor);

    corredores_index *corredor_encontrado = (corredores_index*) bsearch(&chave, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);

    if (corredor_encontrado == NULL || corredor_encontrado->rrn < 0) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    if (valor <= 0) {
        printf(ERRO_VALOR_INVALIDO);
        return;
    }

    // Recuperar o registro de corredor
    Corredor c = recuperar_registro_corredor(corredor_encontrado->rrn);

    // Atualizar o saldo
    c.saldo += valor;

    // Escrever o registro de corredor atualizado de volta no arquivo
    escrever_registro_corredor(c, corredor_encontrado->rrn);

    if (flag)
        printf(SUCESSO);
}

void comprar_veiculo_menu(char *id_corredor, char *id_veiculo) {
    corredores_index chave_corredor;
    strcpy(chave_corredor.id_corredor, id_corredor);
    corredores_index *corredor_encontrado = (corredores_index*) bsearch(&chave_corredor, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);

    veiculos_index chave_veiculo;
    strcpy(chave_veiculo.id_veiculo, id_veiculo);
    veiculos_index *veiculo_encontrado = (veiculos_index*) bsearch(&chave_veiculo, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);

    if (corredor_encontrado == NULL || corredor_encontrado->rrn < 0 || veiculo_encontrado == NULL || veiculo_encontrado->rrn < 0) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    Corredor c = recuperar_registro_corredor(corredor_encontrado->rrn);
    Veiculo v = recuperar_registro_veiculo(veiculo_encontrado->rrn);

    if (c.saldo < v.preco) {
        printf(ERRO_SALDO_NAO_SUFICIENTE);
        return;
    }

    for (int i = 0; i < QTD_MAX_VEICULO; ++i) {
        if (strcmp(c.veiculos[i], v.modelo) == 0) {
            printf(ERRO_VEICULO_REPETIDO, c.id_corredor, v.id_veiculo);
            return;
        }
    }

    for (int i = 0; i < QTD_MAX_VEICULO; ++i) {
        if (strlen(c.veiculos[i]) == 0) {
            strcpy(c.veiculos[i], v.modelo);
            break;
        }
    }

    c.saldo -= v.preco;
    escrever_registro_corredor(c, corredor_encontrado->rrn);

    printf(SUCESSO);
}

void cadastrar_veiculo_menu(char *marca, char *modelo, char *poder, int velocidade, int aceleracao, int peso, double preco) {
    Veiculo novo_veiculo;

    // Copia os dados para a nova struct Veiculo
    strcpy(novo_veiculo.marca, marca);
    strcpy(novo_veiculo.modelo, modelo);
    strcpy(novo_veiculo.poder, poder);
    novo_veiculo.velocidade = velocidade;
    novo_veiculo.aceleracao = aceleracao;
    novo_veiculo.peso = peso;
    novo_veiculo.preco = preco;

    // Gera o ID do veículo
    char id_veiculo[TAM_ID_VEICULO];
    sprintf(id_veiculo, "%07d", qtd_registros_veiculos);
    strcpy(novo_veiculo.id_veiculo, id_veiculo);

    // Verifica se o ID do veículo já existe
    veiculos_index chave;
    strcpy(chave.id_veiculo, id_veiculo);
    veiculos_index *veiculo_encontrado = (veiculos_index*) bsearch(&chave, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);
    if (veiculo_encontrado != NULL) {
        printf(ERRO_PK_REPETIDA, id_veiculo);
        return;
    }

    // Adiciona o novo veículo ao final do arquivo de veículos
    escrever_registro_veiculo(novo_veiculo, qtd_registros_veiculos);

    // Atualiza o índice de veículos
    strcpy(veiculos_idx[qtd_registros_veiculos].id_veiculo, id_veiculo);
    veiculos_idx[qtd_registros_veiculos].rrn = qtd_registros_veiculos;

    // Atualiza o índice de preços de veículos
    preco_veiculo_idx[qtd_registros_veiculos].preco = preco;
    strcpy(preco_veiculo_idx[qtd_registros_veiculos].id_veiculo, id_veiculo);

    // Incrementa a quantidade de registros de veículos
    qtd_registros_veiculos++;

    // Reordena os índices de veículos e preços de veículos
    qsort(veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);
    qsort(preco_veiculo_idx, qtd_registros_veiculos, sizeof(preco_veiculo_index), qsort_preco_veiculo_idx);

    printf(SUCESSO);
}

void cadastrar_pista_menu(char *nome, int dificuldade, int distancia, int recorde) {
    Pista nova_pista;

    // Copia os dados para a nova struct Pista
    strcpy(nova_pista.nome, nome);
    nova_pista.dificuldade = dificuldade;
    nova_pista.distancia = distancia;
    nova_pista.recorde = recorde;

    // Gera o ID da pista
    char id_pista[TAM_ID_PISTA];
    sprintf(id_pista, "%04d", qtd_registros_pistas + 1);
    strcpy(nova_pista.id_pista, id_pista);

    // Verifica se o nome da pista já existe
    nome_pista_index chave;
    strcpy(chave.nome, nome);
    nome_pista_index *pista_existente = (nome_pista_index*) bsearch(&chave, nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx);
    if (pista_existente != NULL) {
        printf(ERRO_PK_REPETIDA, nome);
        return;
    }

    // Adiciona a nova pista ao final do arquivo de pistas
    escrever_registro_pista(nova_pista, qtd_registros_pistas);

    // Atualiza o índice de pistas
    strcpy(pistas_idx[qtd_registros_pistas].id_pista, id_pista);
    pistas_idx[qtd_registros_pistas].rrn = qtd_registros_pistas;

    // Atualiza o índice de nomes de pistas
    strcpy(nome_pista_idx[qtd_registros_pistas].nome, nome);
    strcpy(nome_pista_idx[qtd_registros_pistas].id_pista, id_pista);

    // Incrementa a quantidade de registros de pistas
    qtd_registros_pistas++;

    // Reordena os índices de pistas e nomes de pistas
    qsort(pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx);
    qsort(nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx);

    printf(SUCESSO);
}

void executar_corrida_menu(char *id_pista, char *ocorrencia, char *id_corredores, char *id_veiculos) {
    // Verificar se a pista, corredores e veículos existem no banco de dados
    pistas_index *pista_idx = (pistas_index*) bsearch(id_pista, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx);
    if (!pista_idx) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    // Recuperar o registro da pista
    Pista pista = recuperar_registro_pista(pista_idx->rrn);

    char *id_corredor = strtok(id_corredores, "|");
    while (id_corredor) {
        corredores_index *corredor = (corredores_index*) bsearch(id_corredor, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
        if (!corredor) {
            printf(ERRO_REGISTRO_NAO_ENCONTRADO);
            return;
        }
        id_corredor = strtok(NULL, "|");
    }

    char *id_veiculo = strtok(id_veiculos, "|");
    while (id_veiculo) {
        veiculos_index *veiculo = (veiculos_index*) bsearch(id_veiculo, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);
        if (!veiculo) {
            printf(ERRO_REGISTRO_NAO_ENCONTRADO);
            return;
        }
        id_veiculo = strtok(NULL, "|");
    }

    // Verificar se a chave composta (id_pista e ocorrencia) já existe no banco de dados
    corridas_index chave;
    strcpy(chave.id_pista, id_pista);
    strcpy(chave.ocorrencia, ocorrencia);
    corridas_index *corrida_existente = (corridas_index*) bsearch(&chave, corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx);
    if (corrida_existente) {
        printf(ERRO_PK_REPETIDA, id_pista);
        return;
    }

    // Verificar se cada corredor possui o veículo atribuído a ele
    id_corredor = strtok(id_corredores, "|");
    id_veiculo = strtok(id_veiculos, "|");
    while (id_corredor && id_veiculo) {
        corredores_index *corredor = (corredores_index*) bsearch(id_corredor, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
        Corredor c = recuperar_registro_corredor(corredor->rrn);
        bool possui_veiculo = false;
        for (int i = 0; i < QTD_MAX_VEICULO; ++i) {
            if (strcmp(c.veiculos[i], id_veiculo) == 0) {
                possui_veiculo = true;
                break;
            }
        }
        if (!possui_veiculo) {
            printf(ERRO_CORREDOR_VEICULO, id_corredor, id_veiculo);
            return;
        }
        id_corredor = strtok(NULL, "|");
        id_veiculo = strtok(NULL, "|");
    }

    // Calcular o valor total arrecadado na corrida e distribuir os prêmios para os três primeiros colocados
    double valor_total = 6 * (TX_FIXA * pista.dificuldade);
    double premio_1 = valor_total * 0.4;
    double premio_2 = valor_total * 0.3;
    double premio_3 = valor_total * 0.2;

    // Inserir a nova corrida no banco de dados
    Corrida nova_corrida;
    strcpy(nova_corrida.id_pista, id_pista);
    strcpy(nova_corrida.ocorrencia, ocorrencia);
    strcpy(nova_corrida.id_corredores, id_corredores);
    strcpy(nova_corrida.id_veiculos, id_veiculos);
    escrever_registro_corrida(nova_corrida, qtd_registros_corridas);

    // Atualizar o índice de corridas
    strcpy(corridas_idx[qtd_registros_corridas].id_pista, id_pista);
    strcpy(corridas_idx[qtd_registros_corridas].ocorrencia, ocorrencia);
    corridas_idx[qtd_registros_corridas].rrn = qtd_registros_corridas;

    // Incrementar a quantidade de registros de corridas
    qtd_registros_corridas++;

    // Reordenar o índice de corridas
    qsort(corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx);

    // Distribuir os prêmios para os três primeiros colocados
    id_corredor = strtok(id_corredores, "|");
    corredores_index *corredor_1 = (corredores_index*) bsearch(id_corredor, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
    Corredor c1 = recuperar_registro_corredor(corredor_1->rrn);
    c1.saldo += premio_1;
    escrever_registro_corredor(c1, corredor_1->rrn);

    id_corredor = strtok(NULL, "|");
    corredores_index *corredor_2 = (corredores_index*) bsearch(id_corredor, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
    Corredor c2 = recuperar_registro_corredor(corredor_2->rrn);
    c2.saldo += premio_2;
    escrever_registro_corredor(c2, corredor_2->rrn);

    id_corredor = strtok(NULL, "|");
    corredores_index *corredor_3 = (corredores_index*) bsearch(id_corredor, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
    Corredor c3 = recuperar_registro_corredor(corredor_3->rrn);
    c3.saldo += premio_3;
    escrever_registro_corredor(c3, corredor_3->rrn);

    printf(SUCESSO);
}

/* Busca */
//buscar_corredor_id_menu() não deve ser modificada
void buscar_corredor_id_menu(char *id_corredor) {
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
    corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, true, 0);
	if (found == NULL || found->rrn < 0)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_corredor(found->rrn);
}

void buscar_pista_id_menu(char *id_pista) {
    pistas_index chave;
    strcpy(chave.id_pista, id_pista);

    pistas_index *pista_encontrada = (pistas_index*) busca_binaria((void*)&chave, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, true, 0);

    if (pista_encontrada == NULL || pista_encontrada->rrn < 0) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
    } else {
        exibir_pista(pista_encontrada->rrn);
    }
}

void buscar_pista_nome_menu(char *nome_pista) {
    // Buscar a pista pelo nome no índice secundário
    nome_pista_index chave;
    strcpy(chave.nome, nome_pista);
    nome_pista_index *pista_encontrada = (nome_pista_index*) busca_binaria((void*)&chave, nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx, true, 0);

    // Se a pista não foi encontrada, exibir uma mensagem de erro
    if (pista_encontrada == NULL) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    // Buscar a pista pelo id no índice primário
    pistas_index chave_primaria;
    strcpy(chave_primaria.id_pista, pista_encontrada->id_pista);
    pistas_index *pista_final = (pistas_index*) busca_binaria((void*)&chave_primaria, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, true, 0);

    // Se a pista não foi encontrada, exibir uma mensagem de erro
    if (pista_final == NULL || pista_final->rrn < 0) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    // Exibir os dados da pista
    exibir_pista(pista_final->rrn);
}

/* Listagem */
//listar_corredores_id_menu() não deve ser modificada
void listar_corredores_id_menu() {
	if (qtd_registros_corredores == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
		for (unsigned int i = 0; i < qtd_registros_corredores; i++)
			exibir_corredor(corredores_idx[i].rrn);
}

void listar_corredores_modelo_menu(char *modelo) {
    bool found = false;
    for (unsigned int i = 0; i < qtd_registros_corredores; i++) {
        Corredor c = recuperar_registro_corredor(corredores_idx[i].rrn);
        for (int j = 0; j < QTD_MAX_VEICULO; ++j) {
            if (strcmp(c.veiculos[j], modelo) == 0) {
                exibir_corredor(corredores_idx[i].rrn);
                found = true;
                break;
            }
        }
    }
    if (!found)
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
}

void listar_veiculos_compra_menu(char *id_corredor) {
    // Encontrar o corredor com o ID fornecido
    corredores_index chave;
    strcpy(chave.id_corredor, id_corredor);
    corredores_index *corredor_encontrado = (corredores_index*) bsearch(&chave, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
    
    // Se o corredor não for encontrado, exibir uma mensagem de erro
    if (corredor_encontrado == NULL || corredor_encontrado->rrn < 0) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    // Obter o saldo do corredor
    Corredor c = recuperar_registro_corredor(corredor_encontrado->rrn);
    double saldo_corredor = c.saldo;

    // Percorrer todos os veículos e exibir aqueles que o corredor pode comprar
    bool found = false;
    for (unsigned int i = 0; i < qtd_registros_veiculos; i++) {
        Veiculo v = recuperar_registro_veiculo(veiculos_idx[i].rrn);
        if (v.preco <= saldo_corredor) {
            exibir_veiculo(veiculos_idx[i].rrn);
            found = true;
        }
    }

    // Se nenhum veículo for encontrado, exibir uma mensagem
    if (!found)
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
}

void listar_corridas_periodo_menu(char *data_inicio, char *data_fim) {
    bool found = false;
    for (unsigned int i = 0; i < qtd_registros_corridas; i++) {
        Corrida c = recuperar_registro_corrida(corridas_idx[i].rrn);
        if (strcmp(c.ocorrencia, data_inicio) >= 0 && strcmp(c.ocorrencia, data_fim) <= 0) {
            exibir_corrida(corridas_idx[i].rrn);
            found = true;
        }
    }
    if (!found)
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
}

/* Liberar espaço */
void liberar_espaco_menu() {
    // Criar um novo array de corredores e um novo índice de corredores
    char novo_arquivo_corredores[TAM_ARQUIVO_CORREDORES];
    corredores_index novo_corredores_idx[MAX_REGISTROS];

    // Inicializar o contador de novos registros
    unsigned novo_qtd_registros_corredores = 0;

    // Percorrer todos os registros de corredores
    for (unsigned i = 0; i < qtd_registros_corredores; ++i) {
        // Se o registro não foi excluído
        if (corredores_idx[i].rrn >= 0) {
            // Copiar o registro para o novo array de corredores
            strncpy(novo_arquivo_corredores + novo_qtd_registros_corredores * TAM_REGISTRO_CORREDOR, ARQUIVO_CORREDORES + corredores_idx[i].rrn * TAM_REGISTRO_CORREDOR, TAM_REGISTRO_CORREDOR);

            // Copiar o índice para o novo índice de corredores
            strcpy(novo_corredores_idx[novo_qtd_registros_corredores].id_corredor, corredores_idx[i].id_corredor);
            novo_corredores_idx[novo_qtd_registros_corredores].rrn = novo_qtd_registros_corredores;

            // Incrementar o contador de novos registros
            ++novo_qtd_registros_corredores;
        }
    }

    // Substituir o array de corredores e o índice de corredores originais pelos novos
    memcpy(ARQUIVO_CORREDORES, novo_arquivo_corredores, TAM_ARQUIVO_CORREDORES);
    memcpy(corredores_idx, novo_corredores_idx, MAX_REGISTROS * sizeof(corredores_index));
    qtd_registros_corredores = novo_qtd_registros_corredores;

    printf(SUCESSO);
}

/* Imprimir arquivos de dados */
//Estas funções de imprimir arquivo não devem ser modificadas 
void imprimir_arquivo_corredores_menu() {
	if (qtd_registros_corredores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORREDORES);
}

void imprimir_arquivo_veiculos_menu() {
	if (qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_VEICULOS);
}

void imprimir_arquivo_pistas_menu() {
	if (qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_PISTAS);
}

void imprimir_arquivo_corridas_menu() {
	if (qtd_registros_corridas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORRIDAS);
}

/* Imprimir índices primários */
//imprimir_corredores_idx_menu() não deve ser modificada
void imprimir_corredores_idx_menu() {
	if (corredores_idx == NULL || qtd_registros_corredores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_corredores; ++i)
			printf("%s, %d\n", corredores_idx[i].id_corredor, corredores_idx[i].rrn);
}

void imprimir_veiculos_idx_menu() {
    if (qtd_registros_veiculos == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned int i = 0; i < qtd_registros_veiculos; ++i)
            printf("%07d, %d\n", atoi(veiculos_idx[i].id_veiculo), veiculos_idx[i].rrn);
}

void imprimir_pistas_idx_menu() {
    if (qtd_registros_pistas == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned int i = 0; i < qtd_registros_pistas; ++i)
            exibir_pista(pistas_idx[i].rrn);
}

void imprimir_corridas_idx_menu() {
    if (qtd_registros_corridas == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned int i = 0; i < qtd_registros_corridas; ++i)
            exibir_corrida(corridas_idx[i].rrn);
}

/* Imprimir índices secundários */
void imprimir_nome_pista_idx_menu() {
    if (qtd_registros_pistas == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned int i = 0; i < qtd_registros_pistas; ++i)
            printf("%s, %s\n", nome_pista_idx[i].nome, nome_pista_idx[i].id_pista);
}

void imprimir_preco_veiculo_idx_menu() {
    if (qtd_registros_veiculos == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned int i = 0; i < qtd_registros_veiculos; ++i){
            printf("%.2lf, %s\n", preco_veiculo_idx[i].preco, preco_veiculo_idx[i].id_veiculo);
        }
}

void imprimir_corredor_veiculos_secundario_idx_menu() {
    if (corredor_veiculos_idx.qtd_registros_secundario == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else {
        printf("Índice de corredor veículos secundário:\n");
        for (unsigned int i = 0; i < corredor_veiculos_idx.qtd_registros_secundario; ++i)
            printf("Modelo: %s, Primeiro índice: %d\n", corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].chave_secundaria, corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].primeiro_indice);
    }
}

void imprimir_corredor_veiculos_primario_idx_menu() {
    if (corredor_veiculos_idx.qtd_registros_primario == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else {
        printf("Índice de corredor veículos primário:\n");
        for (unsigned int i = 0; i < corredor_veiculos_idx.qtd_registros_primario; ++i)
            printf("ID Corredor: %s, Próximo índice: %d\n", corredor_veiculos_idx.corredor_veiculos_primario_idx[i].chave_primaria, corredor_veiculos_idx.corredor_veiculos_primario_idx[i].proximo_indice);
    }
}

/* Liberar memória e encerrar programa */
void liberar_memoria_menu() {
    free(corredores_idx);
    free(veiculos_idx);
    free(pistas_idx);
    free(corridas_idx);
    free(nome_pista_idx);
    free(preco_veiculo_idx);
    free(corredor_veiculos_idx.corredor_veiculos_secundario_idx);
    free(corredor_veiculos_idx.corredor_veiculos_primario_idx);
    exit(0);
}

void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t) {
    // Verificar se a chave secundária já existe
    for (unsigned int i = 0; i < t->qtd_registros_secundario; ++i) {
        if (strcmp(t->corredor_veiculos_secundario_idx[i].chave_secundaria, chave_secundaria) == 0) {
            // Encontrar a última chave primária para essa chave secundária
            int indice = t->corredor_veiculos_secundario_idx[i].primeiro_indice;
            while (t->corredor_veiculos_primario_idx[indice].proximo_indice != -1) {
                indice = t->corredor_veiculos_primario_idx[indice].proximo_indice;
            }

            // Adicionar a nova chave primária no final da lista
            t->corredor_veiculos_primario_idx[indice].proximo_indice = t->qtd_registros_primario;
            strcpy(t->corredor_veiculos_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);
            t->corredor_veiculos_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
            ++t->qtd_registros_primario;

            return;
        }
    }

    // Se a chave secundária não existir, criar uma nova entrada
    strcpy(t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].chave_secundaria, chave_secundaria);
    t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].primeiro_indice = t->qtd_registros_primario;
    ++t->qtd_registros_secundario;

    // Adicionar a chave primária correspondente
    strcpy(t->corredor_veiculos_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);
    t->corredor_veiculos_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
    ++t->qtd_registros_primario;
}

bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t) {
    // Buscar a chave secundária
    for (unsigned int i = 0; i < t->qtd_registros_secundario; ++i) {
        if (strcmp(t->corredor_veiculos_secundario_idx[i].chave_secundaria, chave_secundaria) == 0) {
            // Se a chave foi encontrada, armazenar o índice inicial no resultado (se fornecido)
            if (result != NULL) {
                *result = t->corredor_veiculos_secundario_idx[i].primeiro_indice;
            }

            // Se solicitado, exibir o caminho percorrido
            if (exibir_caminho) {
                printf("Caminho percorrido: %d\n", i);
            }

            return true;
        }
    }

    // Se a chave não foi encontrada, retornar false
    return false;
}

int inverted_list_primary_search(char result[][TAM_ID_CORREDOR], bool exibir_caminho, int indice, int *indice_final, inverted_list *t) {
    int count = 0;
    int current_index = indice;

    // Percorrer a lista encadeada de chaves primárias
    while (current_index != -1) {
        // Se solicitado, armazenar a chave primária no resultado
        if (result != NULL) {
            strcpy(result[count], t->corredor_veiculos_primario_idx[current_index].chave_primaria);
        }

        // Se solicitado, exibir o caminho percorrido
        if (exibir_caminho) {
            printf("Caminho percorrido: %d\n", current_index);
        }

        // Avançar para a próxima chave primária na lista encadeada
        current_index = t->corredor_veiculos_primario_idx[current_index].proximo_indice;

        // Incrementar o contador de chaves encontradas
        count++;
    }

    // Se fornecido, armazenar o índice final no resultado
    if (indice_final != NULL) {
        *indice_final = current_index;
    }

    // Retornar a quantidade de chaves encontradas
    return count;
}


void* busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado) {
    const char *base = base0;
    size_t low = 0;
    size_t high = nmemb;
    size_t mid;
    int cond;

    if (exibir_caminho) {
        printf("Registros percorridos: ");
    }

    while (low < high) {
        mid = (low + high) / 2;

        if (exibir_caminho) {
            printf("%zu ", mid);
        }

        cond = (*compar)(key, base + mid * size);

        if (cond < 0) {
            high = mid;
        } else if (cond > 0) {
            low = mid + 1;
        } else { // key is equal to mid
            if (posicao_caso_repetido == -1) { // first occurrence
                while (mid > 0 && (*compar)(key, base + (mid - 1) * size) == 0) {
                    mid--;
                    if (exibir_caminho) {
                        printf("%zu ", mid);
                    }
                }
            } else if (posicao_caso_repetido == 1) { // last occurrence
                while (mid < nmemb - 1 && (*compar)(key, base + (mid + 1) * size) == 0) {
                    mid++;
                    if (exibir_caminho) {
                        printf("%zu ", mid);
                    }
                }
            }
            if (exibir_caminho) {
                printf("\n");
            }
            return (void *)(base + mid * size);
        }
    }

    // key not found
    if (retorno_se_nao_encontrado == -1 && low > 0) { // predecessor
        if (exibir_caminho) {
            printf("%zu \n", low - 1);
        }
        return (void *)(base + (low - 1) * size);
    } else if (retorno_se_nao_encontrado == 1 && low < nmemb) { // successor
        if (exibir_caminho) {
            printf("%zu \n", low);
        }
        return (void *)(base + low * size);
    }

    if (exibir_caminho) {
        printf("\n");
    }
    return NULL;
}

//As funções abaixo não devem ser modificadas
void* busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado) {
	return busca_binaria_com_reps(key, base0, nmemb, size, compar, exibir_caminho, 0, retorno_se_nao_encontrado);
}

char *strpadright(char *str, char pad, unsigned size){
	for (unsigned i = strlen(str); i < size; ++i)
		str[i] = pad;
	str[size] = '\0';
	return str;
}
char *strupr(char *str){
	for (char *p = str; *p; ++p)
		*p = toupper(*p);
	return str;
}
char *strlower(char *str){
	for (char *p = str; *p; ++p)
		*p = tolower(*p);
	return str;
}