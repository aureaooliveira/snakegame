#include <stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
    char c;
    int heatmap;
} tCelula;

typedef struct
{
    int linha;
    int coluna;

} tPosicao;

typedef struct{
    int linhas; 
    int colunas;
    int comida;
}tMapa;

typedef struct
{
    char cabecaCobra;
    tPosicao posicao;
    int tamanho;

} tCobra;

//---- funcoes que geram arquivos ----------------------------------------------------

void ImprimeHeatmap(tCelula mapa[100][100], int linhas, int colunas,char caminhoDiretorio[])
{
    char nomeArquivoHeatmap[1000];
    sprintf(nomeArquivoHeatmap,"%s/saida/heatmap.txt",caminhoDiretorio);

    FILE* arquivoHeatmap;

    arquivoHeatmap = fopen(nomeArquivoHeatmap,"w");
    int l, c;

    for (l = 1; l <= linhas; l++)
    {
        for (c = 1; c <= colunas + 1; c++)

        { if(mapa[l][c].c != '\n' && mapa[l][c].c != '\00' ){

            //conidicionais para garantir exatamente a formatacao exigida  

            if(c == colunas){
                fprintf(arquivoHeatmap,"%d", mapa[l][c].heatmap);
            }else{
            fprintf(arquivoHeatmap,"%d ", mapa[l][c].heatmap);
            }
        }else{
            fprintf(arquivoHeatmap,"\n");
        }
            
        }
        
    }
    fclose(arquivoHeatmap);
     
}
void ImprimeRankingPosicoesEmArquivo(tCelula mapa[100][100],int linhas, int colunas,char caminhoDiretorio[]){

    int l, c, Maior=1;
    int maiorLinha, maiorColuna;

    char nomeArquivoRanking[1000];
    
    FILE* arquivoRanking;
    sprintf(nomeArquivoRanking,"%s/saida/ranking.txt",caminhoDiretorio);
    arquivoRanking = fopen(nomeArquivoRanking,"w");

    while(Maior>0){

    Maior=0;
    for (l = 1; l <= linhas; l++){

        for (c = 1; c <= colunas; c++){
            if(mapa[l][c].heatmap > Maior){

                Maior = mapa[l][c].heatmap;
                maiorLinha = l;
                maiorColuna = c;

            }else if(mapa[l][c].heatmap == Maior){
                if(l<maiorLinha){
                    maiorLinha = l;
                    maiorColuna = c;
                }else if(l==maiorLinha && c< maiorColuna){
                    maiorLinha = l;
                    maiorColuna = c;

                }
            }
        }
    }
    if(Maior>0){
        fprintf(arquivoRanking,"(%d, %d) - %d\n",maiorLinha-1,maiorColuna-1,mapa[maiorLinha][maiorColuna].heatmap);
        mapa[maiorLinha][maiorColuna].heatmap = 0;
    }

    
    }
    fclose(arquivoRanking);
}
void GeraArquivoDeInicializacao(tCelula mapa[100][100], int linhas, int colunas,char caminhoDiretorio[]){

    //funcao imprime o mapa inicial e a posicao inicial da cobra 



    int l, c, unico = 0;
    char nomeArquivoInicializacao[1000] = "./inicializacao.txt";
    sprintf(nomeArquivoInicializacao,"%s/saida/inicializacao.txt",caminhoDiretorio);
    FILE* arquivoInicializacao;
    arquivoInicializacao = fopen(nomeArquivoInicializacao,"w");
    tPosicao posicaoCobra;

    for (l = 1; l <= linhas; l++)
    {
        for (c = 1; c <= colunas + 1; c++)
        {   
            if(mapa[l][c].c == '\00'){
                fprintf(arquivoInicializacao,"\n");
            }else{

            fprintf(arquivoInicializacao,"%c", mapa[l][c].c);
            if (mapa[l][c].c == '>')
            {
                posicaoCobra.linha = l;
                posicaoCobra.coluna = c;
            }
            }
            
        }
    }
     fprintf(arquivoInicializacao,"A cobra comecara o jogo na linha %d e coluna %d\n", posicaoCobra.linha, posicaoCobra.coluna);

    fclose(arquivoInicializacao);
}
void GeraResumoDeResultadoEmArquivo(int numMovimento,char movimento, int pontuacao,int tamanhoCobra,int fimDeJogo,FILE* arquivo){
    //funcao recebe arquivo e imprime as jogadas significativas dentro


    if(pontuacao!=0){

        

        fprintf(arquivo,"Movimento %d (%c) ",numMovimento, movimento);
    

    switch (pontuacao)
    {
    case 10:
    fprintf(arquivo,"gerou dinheiro\n");
    break;
    
    case 1:
    if(fimDeJogo==0){
        fprintf(arquivo,"fez a cobra crescer para o tamanho %d, terminando o jogo\n",tamanhoCobra+1); 
        
    }else{
    fprintf(arquivo,"fez a cobra crescer para o tamanho %d\n", tamanhoCobra+1);
    }
    
    break;

    case -1001:
    fprintf(arquivo,"resultou no fim de jogo por conta de colisao\n");
    break;

    default:
        break;
    }
    
}
 
}
void GeraArquivoDeEstatistica(int movTotal,int movSemPOnto,tCobra cobra[],int i,char caminhoDiretorio[]){

    char nomeArquivoEstatistica[1000];
    sprintf(nomeArquivoEstatistica,"%s/saida/estatisticas.txt",caminhoDiretorio);
    FILE* arquivoEstatistica;
    arquivoEstatistica = fopen(nomeArquivoEstatistica,"w");
    int direita=0, esquerda=0, cima=0, baixo=0;
    int a;

    fprintf(arquivoEstatistica,"Numero de movimentos: %d\n", movTotal);
    fprintf(arquivoEstatistica,"Numero de movimentos sem pontuar: %d\n",movSemPOnto);

//varre vetor com todos os estados da cobra durante jogopara gerar estatistica

    for(a=1;a<=i;a++){
        switch(cobra[a].cabecaCobra){
            case '>':
            direita++;
            break;

            case '<':
            esquerda++;
            break;

            case '^':
            cima++;
            break;

            case 'v':
            baixo++;
            break;

            defaut: break;
        }
    }
    fprintf(arquivoEstatistica,"Numero de movimentos para baixo: %d\n", baixo);
    fprintf(arquivoEstatistica,"Numero de movimentos para cima: %d\n", cima);
    fprintf(arquivoEstatistica,"Numero de movimentos para esquerda: %d\n", esquerda);
    fprintf(arquivoEstatistica,"Numero de movimentos para direita: %d\n", direita);
    
fclose(arquivoEstatistica);

}


//----- funcoes pro funcionamento do jogo------------------------------------

int ValorEmCasoDeColisao(char c)
{
    //funcao retorna o valor da pontuacao gerada pelo movimento da cobra
    //retorna um valor negativo caso haja uma colisao que termine o jogo

    switch (c)
    {
    case '#':
        return -1001;
        break;

    case 'o':
        return -1001;
        break;

    case ' ':
        return 0;
        break;

    case '$':
        return 10;
        break;

    case '*':
        return 1;
        break;

    default:
        break;
    }
}
int  LeMapaEInicializaHeatmap(tCelula mapa[100][100], int linhas, int colunas, FILE *pFile)
{
    /* funcao le apenas os caracteres do mapa do arquivo
     e inicializa as posicoes com heatmap=0, menos a cobra inicial*/

    // matriz mapa de dimensoes linhasXcolunas+1 ---> ultima coluna armazenas os \n;

    //retorna a quantidade inicial de comida no mapa

    int l, c;
    int comida=0;
    int linhaCobra, colunaCobra;

    for (l = 1; l <= linhas; l++)
    {
        for (c = 1; c <= colunas + 1; c++)
        {
            fscanf(pFile, "%c", &mapa[l][c].c);

            if (mapa[l][c].c == '>')
            {
                mapa[l][c].heatmap = 1;
                linhaCobra = l;
                colunaCobra = c;
            }
            else
            {
                if(mapa[l][c].c=='*'){
                    comida++;
                }
                 mapa[l][c].heatmap = 0;
                
            }
        }
    }
    return comida;
}
tPosicao ImprimeMapa(tCelula mapa[100][100], int linhas, int colunas)
{
    //funcao para imprimir as alteracoes do mapa de cada rodada
    //imprime a ulltima coluna composta apenas por \n
    //retorna  a posicao atual da cobra

    int l, c, unico = 0;
    tPosicao posicao;

    for (l = 1; l <= linhas; l++)
    {
        for (c = 1; c <= colunas + 1; c++)
        {
            if(mapa[l][c].c=='\00'){
                printf("\n");
            }else{
            printf("%c", mapa[l][c].c);
            if (mapa[l][c].c == '>')
            {
                posicao.linha = l;
                posicao.coluna = c;
            }
            }
        }
    }
    return posicao;
}
tCobra LeMapaEntrePartidas(tCelula mapa[100][100], int linhas, int colunas)
{
    
    // funcao varre mapa entre rodadas para verificar estado da cobra
    // retorna posicao, tamanho e cabeca atual da cobra


    int c, l;
    tCobra cobra;
    cobra.tamanho=0;
    for (l = 1; l <= linhas; l++)
    {
        for (c = 1; c <= colunas + 1; c++)
        {
            if (mapa[l][c].c == '>' || mapa[l][c].c == '<' || mapa[l][c].c == '^' || mapa[l][c].c == 'v')
            {
                cobra.posicao.linha = l;
                cobra.posicao.coluna = c;
                cobra.cabecaCobra = mapa[l][c].c;
            }else if(mapa[l][c].c=='o'){
                cobra.tamanho++;
            }

        }
    }
    return cobra;
}

tCobra MudaPosicaoECabecaCobra(tCobra cobra, char movimento, int ultimaL, int ultimaC)
{
    //funcao recebe a ultima direcao da cabeca da cobra e o movimento do usuario
    //para definir a proxima direcao da cabeca e a proxima celula a ser ocupada por ela

    //retorna as info da cobra atualizada, cabeca e posicao

    tCobra c;
    if (cobra.cabecaCobra == '>')
    {
        switch (movimento)
        {
        case 'c':
            c.posicao.linha = cobra.posicao.linha;
            c.posicao.coluna = cobra.posicao.coluna + 1;
            c.cabecaCobra = '>';
            if (c.posicao.coluna > ultimaC)
            {
                
                c.posicao.coluna = 1;
            }
            break;

        case 'h':
            c.posicao.linha = cobra.posicao.linha + 1;
            c.posicao.coluna = cobra.posicao.coluna;
            c.cabecaCobra = 'v';
            if (c.posicao.linha > ultimaL)
            {
                c.posicao.linha = 1;
            }
            
            break;

        case 'a':
            c.posicao.linha = cobra.posicao.linha - 1;
            c.posicao.coluna = cobra.posicao.coluna;
            c.cabecaCobra = '^';
            if (c.posicao.linha < 1)
            {
                c.posicao.linha = ultimaL;
            }
            
            break;

        default:
            break;
        }
    }
    if (cobra.cabecaCobra == '<')
    {
        switch (movimento)
        {
        case 'c':
            c.posicao.linha = cobra.posicao.linha;
            c.posicao.coluna = cobra.posicao.coluna - 1;
            c.cabecaCobra = '<';
            if (c.posicao.coluna < 1)
            {
                c.posicao.coluna = ultimaC;
            }
            break;

        case 'h':
            c.posicao.linha = cobra.posicao.linha - 1;
            c.posicao.coluna = cobra.posicao.coluna;
            c.cabecaCobra = '^';
            if (c.posicao.linha < 1)
            {
                c.posicao.linha = ultimaL;
            }
            break;

        case 'a':
            c.posicao.linha = cobra.posicao.linha + 1;
            c.posicao.coluna = cobra.posicao.coluna;
            c.cabecaCobra = 'v';
            if (c.posicao.linha > ultimaL)
            {
                c.posicao.linha = 1;
            }
            break;

        default:
            break;
        }
    }
    if (cobra.cabecaCobra == '^')
    {
        switch (movimento)
        {
        case 'c':
            c.posicao.linha = cobra.posicao.linha - 1;
            c.posicao.coluna = cobra.posicao.coluna;
            c.cabecaCobra = '^';
            if (c.posicao.linha < 1)
            {
                c.posicao.linha = ultimaL;
            }
            break;

        case 'h':
            c.posicao.linha = cobra.posicao.linha;
            c.posicao.coluna = cobra.posicao.coluna + 1;
            c.cabecaCobra = '>';
            if (c.posicao.coluna > ultimaC)
            {
                c.posicao.coluna = 1;
            }
            break;

        case 'a':
            c.posicao.linha = cobra.posicao.linha;
            c.posicao.coluna = cobra.posicao.coluna - 1;
            c.cabecaCobra = '<';
            if (c.posicao.coluna < 1)
            {
                c.posicao.coluna = ultimaC;
            }
            break;

        default:
            break;
        }
    }
    if (cobra.cabecaCobra == 'v')
    {
        switch (movimento)
        {
        case 'c':
            c.posicao.linha = cobra.posicao.linha + 1;
            c.posicao.coluna = cobra.posicao.coluna;
            c.cabecaCobra = 'v';
            if (c.posicao.linha > ultimaL)
            {
                c.posicao.linha = 1;
            }
            break;

        case 'h':
            c.posicao.linha = cobra.posicao.linha;
            c.posicao.coluna = cobra.posicao.coluna - 1;
            c.cabecaCobra = '<';
            if (c.posicao.coluna < 1)
            {
                c.posicao.coluna = ultimaC;
            }
            break;

        case 'a':
            c.posicao.linha = cobra.posicao.linha;
            c.posicao.coluna = cobra.posicao.coluna + 1;
            c.cabecaCobra = '>';
            if (c.posicao.coluna > ultimaC)
            {
                c.posicao.coluna = 1;
            }
            break;

        default:
            break;
        }
    }
    return c;
}

int AtualizaMapaMudaCobra(tCelula mapa[100][100],tCobra cobra,tCobra Vcobras[],int i,int tamanhoCobra, int atualizaHeatmap)

//funcao recebe informacao sobre o novo estado da cobra e atualiza mapa
//retorna valor da celula colidida, ou seja a pontuacao da rodada
//retorna negativo se a cobra colidir com obstaculo e morrer
{
    int rtn;
    int a=0;
    int b=i;

    //rtn informa oque tem na celula em que a cobra esta indo
    rtn = ValorEmCasoDeColisao(mapa[cobra.posicao.linha][cobra.posicao.coluna].c);

    
    mapa[Vcobras[i].posicao.linha][Vcobras[i].posicao.coluna].c  = cobra.cabecaCobra;

if(atualizaHeatmap==1){
    mapa[Vcobras[i].posicao.linha][Vcobras[i].posicao.coluna].heatmap++;
}

    

    //entra na funcao com a cobra atualizada ja
    if(rtn==0 ){
        mapa[Vcobras[i-tamanhoCobra-1].posicao.linha][Vcobras[i-tamanhoCobra-1].posicao.coluna].c =' ';

    }else if(rtn == 10){
        mapa[Vcobras[i-tamanhoCobra-1].posicao.linha][Vcobras[i-tamanhoCobra-1].posicao.coluna].c =' ';
            
    }else if(rtn == 1){
        mapa[Vcobras[i-tamanhoCobra-1].posicao.linha][Vcobras[i-tamanhoCobra-1].posicao.coluna].c ='o'; 
        tamanhoCobra++;
        

    }else if(rtn == -1001){

        //condicional para verificar se a celula da proxima posicao 
        //eh ocupada pelo ultimo pedaco do seu corpo---> caso sim, cobra nao morre
        if(cobra.posicao.linha==Vcobras[i-tamanhoCobra-1].posicao.linha && cobra.posicao.coluna==Vcobras[i-tamanhoCobra-1].posicao.coluna ){
            mapa[Vcobras[i-tamanhoCobra-1].posicao.linha][Vcobras[i-tamanhoCobra-1].posicao.coluna].c = cobra.cabecaCobra;
            rtn=0;

        }else{
            mapa[Vcobras[i-tamanhoCobra-1].posicao.linha][Vcobras[i-tamanhoCobra-1].posicao.coluna].c =' ';
        }
        
    
    }

    //loop para atualizar as posicoes do corpo da cobra 'o' apenas

    while(a<tamanhoCobra){

                mapa[Vcobras[b-1].posicao.linha][Vcobras[b-1].posicao.coluna].c ='o';
                b--;
                a++;
            }

            return rtn;
     
    }

void ImprimeMapaDaMorte(tCelula mapa[100][100],int linhas, int colunas){
    int l,c;

    //funcao modifica mapa em caso de morte ---> substitui caracteres da cobra por X

    for (l = 1; l <= linhas; l++)
    {
        for (c = 1; c <= colunas + 1; c++)
        {
            if (mapa[l][c].c == '>' || mapa[l][c].c == '<' || mapa[l][c].c == '^' || mapa[l][c].c == 'v'||mapa[l][c].c =='o')
            {
                printf("X");
            }else{
                if(mapa[l][c].c == '\00'){
                    printf("\n");
                }else{
                printf("%c", mapa[l][c].c);
                }

            }
            }

        }
    }

tMapa InicializaJogo(tCelula mapa[100][100], FILE *pFile,char caminhoDiretorio[]){
    
    //funcao responsavel por ler o arquivo mapa.txt e criar inicializacao.txt
    //retorna as dimensoes do mapa e a quantidade de comida inicial


    int l, c;
    tPosicao posicao;
    tMapa mapaJogo;
    tPosicao posicaoCobra;



    char nomeArquivoInicializacao[1000];
    sprintf(nomeArquivoInicializacao,"%s/saida/inicializacao.txt",caminhoDiretorio);
    FILE* arquivoInicializacao;
    arquivoInicializacao = fopen(nomeArquivoInicializacao,"w");

    

    fscanf(pFile, "%d %d", &l, &c);
    mapaJogo.linhas = l;
    mapaJogo.colunas = c; 
    fscanf(pFile, "%*c");

    mapaJogo.comida = LeMapaEInicializaHeatmap(mapa, l, c,pFile); //funcao retorna quantidade inicial de comida
    GeraArquivoDeInicializacao(mapa,l,c,caminhoDiretorio);
    return mapaJogo;
    
}
void RealizarJogo(tCelula mapa[100][100],int l, int c,int comida, char caminhoDiretorio[]){

    tCobra Vcobras[100000];
    
    char movimento;
    int fimDeJogo=1;
    int pontuacaoTotal=0;
    tCobra cobra;
    int i=0;
    int countMov=0;
    int countMovSemPonto=0;
    int atualizaHeatmap;
    int pontoRodada=0;
    int tamanhoCobra=0;
    

    FILE* arquivoResumo;
    
    char nomeArquivoResultado[1000];
    sprintf(nomeArquivoResultado,"%s/saida/resumo.txt",caminhoDiretorio);
    //abrindo aquirvo de resumo
    arquivoResumo = fopen(nomeArquivoResultado,"w");

        cobra.tamanho=0;

    

    while(fimDeJogo){

        scanf("%c",&movimento);
        scanf("%*c");
        printf("Estado do jogo apos o movimento '%c':\n",movimento);
        countMov++;
        

        cobra = LeMapaEntrePartidas(mapa, l,c); //funcao retorna posicao,cabeca e tamanho da cobra atual
        tamanhoCobra = cobra.tamanho;
        
        // salva dados da cobra atual no vetor Vcobras
        Vcobras[i].posicao.linha = cobra.posicao.linha;
        Vcobras[i].posicao.coluna = cobra.posicao.coluna;
        Vcobras[i].cabecaCobra = cobra.cabecaCobra;
        i++;

        
        cobra = MudaPosicaoECabecaCobra(cobra,movimento,l,c);//funcao retorna nova cobra apos movimento
        //salva nova cobra no vetor VCobras
        Vcobras[i].posicao.linha = cobra.posicao.linha;
        Vcobras[i].posicao.coluna = cobra.posicao.coluna;
        Vcobras[i].cabecaCobra = cobra.cabecaCobra;
        atualizaHeatmap=1;

// identificador na funcao de atualizar mapa -- para definir se atualiza cabeca para posicao nova
// ou apenas atualiza o mov o corpo 'o'
//se apenas move o corpo, a funcao nao atualiza o heatmap, pra nao duplicar a contagem 
        pontoRodada = AtualizaMapaMudaCobra(mapa,cobra,Vcobras,i,tamanhoCobra,atualizaHeatmap);

        if(pontoRodada==1){
            //se cobra comeu
            atualizaHeatmap=0;
            tamanhoCobra++;
            comida--;
            AtualizaMapaMudaCobra(mapa,cobra,Vcobras,i,tamanhoCobra,atualizaHeatmap);
            //atualiza apenas o corpo 'o' no mapa, nao a cabeca
        
            if(comida==0){
                //acabar o jogo
                pontuacaoTotal++;
                ImprimeMapa(mapa,l,c);
                printf("Pontuacao: %d\n", pontuacaoTotal);
                printf("Voce venceu!\n");
                printf("Pontuacao final: %d\n", pontuacaoTotal);
                fimDeJogo=0; // para sair do loop da funcao realizaJogo
                GeraResumoDeResultadoEmArquivo(countMov,movimento,pontoRodada,tamanhoCobra,fimDeJogo,arquivoResumo);
                break;
                
              }
        }
        
        if(pontoRodada==0){
            countMovSemPonto++;
        }
        
        if(pontoRodada>=0){
            pontuacaoTotal= pontuacaoTotal + pontoRodada;
        }else{
            //cobra morreu
            ImprimeMapaDaMorte(mapa,l,c);
            
            printf("Pontuacao: %d\n",pontuacaoTotal);
            printf("Game over!\n");
            printf("Pontuacao final: %d\n", pontuacaoTotal);
            fimDeJogo = 0; // pra sair do loop que realizaJogo
            countMovSemPonto++; 
            GeraResumoDeResultadoEmArquivo(countMov,movimento,pontoRodada,tamanhoCobra,fimDeJogo,arquivoResumo);
            break;
        }
        
        //imprime estado de jogo
        ImprimeMapa(mapa,l,c);
        printf("Pontuacao: %d\n", pontuacaoTotal);
        printf("\n");
        GeraResumoDeResultadoEmArquivo(countMov,movimento,pontoRodada,tamanhoCobra,fimDeJogo,arquivoResumo);
        


    }
    
    fclose(arquivoResumo);
    GeraArquivoDeEstatistica(countMov,countMovSemPonto,Vcobras,i,caminhoDiretorio);
    
    }

int main(int argc, char *argv[])
{

    tCelula mapa[100][100];
    char arquivoMapa[1000];
    char caminhoDiretorio[100];
    FILE *pFile;
    int colunas, linhas;
    int c, l;
    tPosicao tamanhoMapa;
    tMapa mapaJogo;
    int comida;

    sprintf(caminhoDiretorio,"%s",argv[1]);

    if(argc<=1){
        printf("ERRO - favor informar o caminho do diretorio em questao\n");
        exit(0);
    }

    sprintf(arquivoMapa, "%s/mapa.txt", argv[1]);

    //abre arquivo do mapa
    pFile = fopen(arquivoMapa, "r");

    if(pFile == 0){
        printf("arquivo nao encontrado em %s\n",argv[1]);
        exit(0);
    }

    mapaJogo = InicializaJogo(mapa, pFile,caminhoDiretorio);
    fclose(pFile);
    //dimensoes do mapa
    l = mapaJogo.linhas;
    c = mapaJogo.colunas;
    comida = mapaJogo.comida;

    printf("\n");
    RealizarJogo(mapa,l,c,comida,caminhoDiretorio);
    

    ImprimeHeatmap(mapa,l,c,caminhoDiretorio);
    ImprimeRankingPosicoesEmArquivo(mapa,l,c,caminhoDiretorio);

    return 0;
}