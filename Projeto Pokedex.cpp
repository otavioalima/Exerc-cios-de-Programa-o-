//Trabalho Pokedex - C04
/*Alunos:
Matheus Vieira Honorio de Souza - 525 - GES
Otavio Augusto Silva Lima - 279 - GES
Vinicius Vilela Paulino - 436 - GES
Vitor Dias Carlos - 445 - GES
*/
//O código cria cidades com nome, código, e se tem ou nao centro Pokemon, e mostra a cidade cadastrada.

#include <iostream>
#include <string>
#include <list>
#include <climits>
#include <cmath>
#include <locale.h>

using namespace std;


struct ponto { //estrutura ponto
  int x;
  int y;
};

struct segmento { //estrutura segmento
  ponto a;
  ponto b;
};

struct pokemon{ //estrutura pokemon
  int codigo;
  ponto coordenada;
  string nome;
  string tipo;
};

struct treenode{ //estrutura treenode para a arvore de pokemons
  pokemon info;
  struct treenode* left;
  struct treenode* right;
  int altura;
  list<pokemon> pokemons;
};

struct estrada{ //estrutura estrada para a cidade
  int origem;
  int destino;
  int distancia;
};

struct Cidade{ //estrutura cidade
  int codigo;
  string nome;
  bool centro_pokemon;
  list<estrada> vizinhos;
};

typedef treenode *treenodeptr; //ponteiro para a estrutura treenode

int altura(treenodeptr p){ //função para pegar a altura da arvore
	if(p == NULL)
		return -1;
	else
		return p->altura;
}

int balanceamento(treenodeptr p){ //função para balancear a arvore
	if(p == NULL)
		return 0;
	return altura(p->left) - altura(p->right);
}

int maior(int a, int b){ //função para pegar o maior valor entre dois numeros
	if(a > b)
		return a;
	else
		return b;
}

treenodeptr rotate_right(treenodeptr y){ //função para rotacionar a arvore para a direita
	treenodeptr x = y->left;
	treenodeptr T2 = x->right;
	
	x->right = y;
	y->left = T2;
	
	
	y->altura = maior(altura(y->left), altura(y->right)) + 1;
	x->altura = maior(altura(x->left), altura(x->right)) + 1;
	
	return x;	
}

treenodeptr rotate_left(treenodeptr x){ //função para rotacionar a arvore para a esquerda
	treenodeptr y = x->right;
	treenodeptr T2 = y->left;
	
	y->left = x;
	x->right = T2;
	
	
	x->altura = maior(altura(x->left), altura(x->right)) + 1;
	y->altura = maior(altura(y->left), altura(y->right)) + 1;
	
	return y;	
}

void tinsert(treenodeptr &p, pokemon poke) {  //função para inserir um pokemon na arvore
    if (p == NULL) {
        p = new treenode;
        p->info = poke;
        p->left = NULL;
        p->right = NULL;
        p->altura = 0;
    } else if (poke.nome < p->info.nome) {
        tinsert(p->left, poke);
    } else if (poke.nome > p->info.nome) {
        tinsert(p->right, poke);
    }
    
    p->altura = 1 + maior(altura(p->left), altura(p->right));

    int balance = balanceamento(p);

    if (balance > 1 && poke.nome < p->left->info.nome) {
        p = rotate_right(p);
    }
    if (balance < -1 && poke.nome > p->right->info.nome) {
        p = rotate_left(p);
    }
    if (balance > 1 && poke.nome > p->left->info.nome) {
        p->left = rotate_left(p->left);
        p = rotate_right(p);
    }
    if (balance < -1 && poke.nome < p->right->info.nome) {
        p->right = rotate_right(p->right);
        p = rotate_left(p);
    }
}

void tinsertTipo(treenodeptr &p, pokemon poke) { //função para inserir um pokemon na arvore por tipo
   if (p == NULL) {
        p = new treenode;
        p->info = poke;
        p->left = NULL;
        p->right = NULL;
        p->altura = 0;
        p->pokemons.push_back(poke);
    } else if (poke.tipo < p->info.tipo) {
        tinsertTipo(p->left, poke);
    } else if (poke.tipo > p->info.tipo) {
        tinsertTipo(p->right, poke);
    } else {
        p->pokemons.push_back(poke);
    }

    p->altura = 1 + maior(altura(p->left), altura(p->right));

    int balance = balanceamento(p);

    if (balance > 1 && poke.tipo < p->left->info.tipo) {
        p = rotate_right(p);
    }
    if (balance < -1 && poke.tipo > p->right->info.tipo) {
        p = rotate_left(p);
    }
    if (balance > 1 && poke.tipo > p->left->info.tipo) {
        p->left = rotate_left(p->left);
        p = rotate_right(p);
    }
    if (balance < -1 && poke.tipo < p->right->info.tipo) {
        p->right = rotate_right(p->right);
        p = rotate_left(p);
    }
}

treenodeptr tsearch(treenodeptr p, string nome){ //função para procurar um pokemon na arvore
  if(p == NULL){
    return NULL;
  }else if(nome == p->info.nome){
      return p;
  }else if(nome < p->info.nome){
      return tsearch(p->left,nome);
  }else
    return tsearch(p->right,nome);	
}

treenodeptr tsearchTipo(treenodeptr p, string tipo) { //função para procurar um pokemon na arvore por tipo
    if (p == NULL) {
        return NULL;
    } else if (tipo == p->info.tipo) {
        return p;
    } else if (tipo < p->info.tipo) {
        return tsearchTipo(p->left, tipo);
    } else {
        return tsearchTipo(p->right, tipo);
    }
}

treenodeptr tpointsmaller(treenodeptr &p){ //função para pegar o menor valor da arvore
	treenodeptr t = p;
	if(p->left == NULL){
		p = p->right;
		return t;
	}
	else
		return tpointsmaller(p->left);
}


bool tremove(treenodeptr &p, string nome) { //função para remover um pokemon da arvore
    if (p == NULL)
        return false;

    bool result;
    if (nome == p->info.nome) { 
        if (p->left == NULL || p->right == NULL) { 
            treenodeptr temp = p->left ? p->left : p->right;
            if (temp == NULL) {
                temp = p;
                p = NULL;
            } else {
                *p = *temp;
            }
            delete temp;
        } else {
            treenodeptr temp = tpointsmaller(p->right);
            p->info = temp->info;
            result = tremove(p->right, temp->info.nome);
        }
        result = true;
    } else if (nome < p->info.nome) {
        result = tremove(p->left, nome);
    } else {
        result = tremove(p->right, nome);
    }

    if (p == NULL)
        return result;

    p->altura = maior(altura(p->left), altura(p->right)) + 1;
    int balance = balanceamento(p);

    if (balance > 1 && balanceamento(p->left) >= 0)
        p = rotate_right(p);

    if (balance > 1 && balanceamento(p->left) < 0) {
        p->left = rotate_left(p->left);
        p = rotate_right(p);
    }

    if (balance < -1 && balanceamento(p->right) <= 0)
        p = rotate_left(p);

    if (balance < -1 && balanceamento(p->right) > 0) {
        p->right = rotate_right(p->right);
        p = rotate_left(p);
    }

    return result;
}

bool tremoveTipo(treenodeptr& p, string tipo, string nome) { //função para remover um pokemon da arvore por tipo
    if (p == NULL)
        return false;

    bool result;
    if (tipo == p->info.tipo) {
        // Procura o Pok?mon pelo nome e remove da lista
        for (list<pokemon>::iterator it = p->pokemons.begin(); it != p->pokemons.end(); ++it) {
            if (it->nome == nome) {
                p->pokemons.erase(it);
                break;
            }
        }
        // Se a lista estiver vazia, remove o n? da ?rvore
        if (p->pokemons.empty()) {
            if (p->left == NULL || p->right == NULL) {
                treenodeptr temp = p->left ? p->left : p->right;
                if (temp == NULL) {
                    temp = p;
                    p = NULL;
                } else {
                    *p = *temp;
                }
                delete temp;
            } else {
                treenodeptr temp = tpointsmaller(p->right);
                p->info = temp->info;
                p->pokemons = temp->pokemons;
                result = tremoveTipo(p->right, temp->info.tipo, temp->info.nome);
            }
        }
        result = true;
    } else if (tipo < p->info.tipo) {
        result = tremoveTipo(p->left, tipo, nome);
    } else {
        result = tremoveTipo(p->right, tipo, nome);
    }

    if (p == NULL)
        return result;

    p->altura = maior(altura(p->left), altura(p->right)) + 1;
    int balance = balanceamento(p);

    if (balance > 1 && balanceamento(p->left) >= 0)
        p = rotate_right(p);

    if (balance > 1 && balanceamento(p->left) < 0) {
        p->left = rotate_left(p->left);
        p = rotate_right(p);
    }

    if (balance < -1 && balanceamento(p->right) <= 0)
        p = rotate_left(p);

    if (balance < -1 && balanceamento(p->right) > 0) {
        p->right = rotate_right(p->right);
        p = rotate_left(p);
    }

    return result;
}

void emOrdem (treenodeptr p){ //função para mostrar a arvore em ordem
   if (p != NULL) {
        emOrdem(p->left);
        cout << "Tipo: " << p->info.tipo << endl;
        list<pokemon>::iterator it;
        for(it = p->pokemons.begin(); it != p->pokemons.end(); ++it){
  	  	    cout << "  Cóigo: " << it->codigo << ", Nome: " << it->nome << endl;
		}
        emOrdem(p->right);
    }
  }


void emOrdem_info (treenodeptr raiz){ //função para mostrar a arvore em ordem com informação
  if(raiz != NULL){
    emOrdem_info(raiz->left);
    
    cout<<"Código: "<<raiz->info.codigo<<endl;
    cout<<"Nome: "<<raiz->info.nome<<endl;
    cout<<"Tipo: "<<raiz->info.tipo<<endl;
    cout<<"Coordenada: "<<"("<<raiz->info.coordenada.x<<", "<<raiz->info.coordenada.y<<")"<<endl<<endl;
    
    emOrdem_info(raiz->right);
  }
}

string tipo_do_nome(treenodeptr p, string nome) { //função para pegar o tipo de um pokemon
    if (p == NULL) {
        return "";
    } else if (nome == p->info.nome) {
        return p->info.tipo;
    } else if (nome < p->info.nome) {
        return tipo_do_nome(p->left, nome);
    } else {
        return tipo_do_nome(p->right, nome);
    }
}

int poketipos(treenodeptr raiz, string tipo) { //função para contar a quantidade de pokemons de um tipo
    if (raiz == NULL) {
        return 0;
    }
    int cont = 0;
    if (raiz->info.tipo == tipo) {
        cont++;
    }
    cont += poketipos(raiz->left, tipo);
    cont += poketipos(raiz->right, tipo);
    
    return cont;
}

void dijkstra(Cidade cidade[], int nVertices, int start){ //função para mostrar o menor caminho até um centro pokemon
  bool intree[nVertices];
  int distance[nVertices], parent[nVertices];
  for(int u = 0; u < nVertices; u++){
    intree[u] = false;
    distance[u] = INT_MAX;
    parent[u] = -1;
  }
  distance[start] = 0;
  int v = start;
  while(intree[v] == false){
    intree[v] = true;
    list<estrada>::iterator p;
    for(p = cidade[v].vizinhos.begin(); p != cidade[v].vizinhos.end(); p++){
      int dest = p->destino;
      int weight = p->distancia;
      if(distance[dest] > distance[v]+weight){
        distance[dest] = distance[v]+weight;
        parent[dest] = v;

      }
    }

      v = 0;
      int dist = INT_MAX;
    for(int u = 0; u < nVertices; u++){
      if(intree[u] == false && dist > distance[u]){
        dist = distance[u];
        v = u;
      }
    }
  }

  int distancia_centro = INT_MAX, end;
  for(int i = 0; i < nVertices; i++){
    if(cidade[i].centro_pokemon == 1 && distancia_centro > distance[i]){
      distancia_centro = distance[i];
      end = i;
    } 
  }


  int caminho[nVertices], x = 0;
  cout<<"Menor caminho: ";
  for(int i = end; i != -1; i = parent[i]){
    caminho[x] = i;
    x++;
  }

  for(int i = x-1; i >= 0; i--){

  cout<<cidade[caminho[i]].nome;
  if(i >= 1)
    cout<<"->";
  }
  cout<<endl;
}

 void cria_cidade(int num_cidades,int num_estradas, Cidade cidade[]){ //função para criar a cidade

  for(int i=0; i< num_cidades; i++){
    cidade[i].codigo = i;
    cout<<"Nome da cidade: ";
    cin.ignore();
    getline(cin,cidade[i].nome);
    cout<<"Ela possui Centro Pokemon? (1 para sim, 0 para nao): ";
    cin>>cidade[i].centro_pokemon;
  }


    int origem, destino, distancia;
    cout<<"Entre com o código da cidade de origem, da de destino, e a distância: " << endl;
  for(int i = 0; i < num_estradas; i++){
    cin>>origem>>destino>>distancia;
    cidade[origem].vizinhos.push_back({origem,destino,distancia});
    cidade[destino].vizinhos.push_back({destino,origem,distancia});

  }

}

void mostra_cidades(int num_cidades, Cidade cidade[]){
  for(int i=0; i<num_cidades; i++){
    cout<<"Código: "<<cidade[i].codigo<<endl;
    cout<<"Nome: "<<cidade[i].nome<<endl;
    if(cidade[i].centro_pokemon == 1){
      cout<<"Tem centro Pokemon."<<endl;
    }else{
      cout<<"Não tem Centro Pokemon."<<endl;
        }
    list<estrada>::iterator it;

    cout<<"Cidades vizinhas: ";

    for(it = cidade[i].vizinhos.begin(); it != cidade[i].vizinhos.end(); it++){
      cout<<cidade[it->destino].nome<<endl;
    }

  }

}

double distancia(ponto p1, ponto p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y));
}

int poke100m(treenodeptr p, ponto u){
  if(p == NULL)
    return 0;
  int i = 0;
  if(distancia(p->info.coordenada, u) <= 100){
    i = 1;
  }
  return i + poke100m(p->left, u) + poke100m(p->right, u);
}

int pokemons_no_raio(treenodeptr p, ponto u, ponto a[], int &i) {
    if (p == NULL)
        return 0;
    
    int pokemons = 0;
    if (distancia(p->info.coordenada, u) <= 100) {
        a[i] = p->info.coordenada;
        i++;
        pokemons = 1;
    }
    
    pokemons += pokemons_no_raio(p->left, u, a, i);
    pokemons += pokemons_no_raio(p->right, u, a, i);
    
    return pokemons;
}


double area_triangulo(ponto a, ponto b, ponto c){
	return 
		((a.x*b.y) - (a.y*b.x) + 
		(a.y*c.x) - (a.x*c.y) + 
		(b.x*c.y) - (b.y*c.x))/2.0;  
}

int orientacao(ponto a, ponto b, ponto c){
	double area = area_triangulo(a,b,c);
	if(area > 0){
		return 1; 
	} else if(area < 0){
		return -1; 
	} else {
		return 0; 
	}
}



double gift_wraping(ponto points[], int n) {
    if (n < 3)
        return -1;
 
    int next[n];
    for (int i = 0; i < n; i++){
        next[i] = -1;
    }
 
    int l = 0;
    for (int i = 1; i < n; i++){
        if (points[i].x < points[l].x)
            l = i;
    }
   
    int p = l, q;
    do {
        q = (p + 1) % n;
        for (int i = 0; i < n; i++){
            if (orientacao(points[p], points[i], points[q]) == -1)
                q = i;
        }
        next[p] = q; 
        p = q; 
    } while (p != l);
    
    double perimetro = 0;
    for (int i = 0; i < n; i++) {
        if (next[i] != -1){
            perimetro += distancia(points[i], points[next[i]]);
        }
    }
    
    return perimetro;
}

void deleteTree(treenodeptr p){ //função para deletar a arvore
  if(p != NULL){
    deleteTree(p->left);
    deleteTree(p->right);
    delete p;
  }
}

int main() { //função principal

  setlocale(LC_ALL, "Portuguese.UTF-8"); //para aceitar acentos

  int var; //variavel para escolher a opção

  cout<<"Quantas cidades deseja cadastrar? ";
  int num_cidades, num_estradas, codigo = 0;
  cin >> num_cidades;
  cout<<"Quantas estradas deseja cadastrar? ";
  cin >> num_estradas;

  Cidade cidades[num_cidades];//variavel para a cidade
  pokemon poke;
  treenodeptr arvore = NULL, result, arvore_tipo = NULL;
  string pesquisa, tipo;
  ponto point;
  bool cidades_criadas = false;
  ponto encontrados[100];
  int count = 0;
  int num_pokemons;

  while(true){ //loop para escolher a opção

    cout<<"0 - Sair"<<endl;
    cout<<"1 - Cadastrar cidades"<<endl;
    cout<<"2 - Mostrar conteudo"<<endl;
    cout<<"3 - Como chegar ao Centro Pokemon mais proximo"<<endl;
    cout<<"4 - Cadastrar Pokemon"<<endl;
    cout<<"5 - Informacoes dos Pokemons"<<endl;
    cout<<"6 - Remover Pokemon"<<endl;
    cout<<"7 - Procurar Pokemon"<<endl;
    cout<<"8 - Mostrar Pokemons por tipo"<<endl;
    cout<<"9 - Contagem de tipo"<<endl;
    cout<<"10 - Quantidade de Pokemons proximos"<<endl;
    cout<<"11 - Perímetro minimo dos Pokemons proximos"<<endl;
    cout<<endl;

    cin>>var; //escolhe a opçãoo	
	cout<<endl;
	
    int a;

  switch(var){ //switch para escolher a opção

    case 0:

      deleteTree(arvore);
      deleteTree(arvore_tipo);

      return 0;

    case 1: //cria a cidade
      cria_cidade(num_cidades, num_estradas, cidades);
      cidades_criadas = true;
      cout<<endl;
      break;

    case 2: //mostra o conteudo do Grafo Cidades

    if(cidades_criadas == true){
      mostra_cidades(num_cidades, cidades);
      cout<<endl;
    }
    else
      cout<<"Insira as cidades antes de mostrar conteudo"<<endl;

    cout<<endl;
    
      break;

    case 3: //mostra a rota mais proxima até um centro pokemon

      cout<<"Em que cidade você está ? ";

      cin>>a;

    if(cidades[a].centro_pokemon == 1)
      cout<<"Esta cidade já tem Centro Pokemon"<<endl;
    else	  	
          dijkstra(cidades, num_cidades, a);
      
      cout<<endl;
      break;

    case 4: //cadastra um pokemon
      poke.codigo = codigo;
      codigo++;
      cout<<"Nome do Pokemon: ";
      cin>>poke.nome;
      cout<<"Tipo do Pokemon: ";
      cin>>poke.tipo;
      cout<<"Coordenada x do Pokemon: ";
      cin>>poke.coordenada.x;
      cout<<"Coordenada y do Pokemon: ";
      cin>>poke.coordenada.y;

      tinsert(arvore,poke);
      tinsertTipo(arvore_tipo,poke);
      
      cout<<endl;
      break;
  
    case 5: //mostra as informações dos pokemons
    	
    	emOrdem_info(arvore);
    	
    	cout<<endl<<endl;
    	break;
  
  
  
    case 6: //remove um pokemon
    	cout<<"Pokemon a ser removido: ";
    	cin.ignore();
    	getline(cin, pesquisa);
        tipo = tipo_do_nome(arvore, pesquisa);
        if (!tipo.empty()) {
            tremove(arvore, pesquisa);
            tremoveTipo(arvore_tipo, tipo, pesquisa);
            cout<<pesquisa<<" removido"<<endl;
        } else {
             cout << "Pokemon não encontrado." << endl;
        }
        cout<<endl;
            break;
    	

    case 7: //procura um pokemon
      cout<<"Nome do pokemon a ser porcurado: ";
      cin.ignore();
      getline(cin, pesquisa);

      result = tsearch(arvore, pesquisa);

      if(result != NULL){
        cout<<"Pokemon encontrado :D"<<endl;
        cout<<"Ele está na coodenada ("<<result->info.coordenada.x<<", "<<result->info.coordenada.y<<")"<<endl;
      }else{
        cout<<"Pokemon não encontrado :c"<<endl;
      }
      
      cout<<endl;
      break;
    
    case 8: //mostra os pokemons por tipo
      emOrdem(arvore_tipo);
      cout<<endl;
      
      cout<<endl;
      break;

   
    case 9: //conta a quantidade de pokemons de um tipo
      cout<<"Tipo a ser contado: ";
      cin.ignore();
      getline(cin, pesquisa);

      cout<<"Quantidade de pokemons do tipo "<<pesquisa<<": "<<poketipos(arvore,pesquisa)<<endl;
      
      cout<<endl;
      break;

    case 10: //conta a quantidade de pokemons proximos
 	   cout<<"Sua coordenada x: ";
 	   cin>>point.x;
 	   cout<<"Sua coordenada y: ";
 	   cin>>point.y;
 	   cout<<"Existem "<<poke100m(arvore,point)<<" Pokemons perto de voce"<<endl;
 	   
 	   cout<<endl;
 	   break;
    
    case 11: //calcula o perimetro minimo dos pokemons proximos
    cout << "Sua coordenada x: ";
    cin >> point.x;
    cout << "Sua coordenada y: ";
    cin >> point.y;
    
    count = 0; 
    num_pokemons = pokemons_no_raio(arvore, point, encontrados, count);
    
    if (num_pokemons > 2) { 
        double perimetro = gift_wraping(encontrados, num_pokemons);
        if (perimetro != -1) {
            cout << "Perímetro minimo = " << perimetro <<"m"<< endl;
        } else {
            cout << "Não foi possível calcular o perímetro mínimo." << endl;
        }
    } else {
        cout << "Não há Pokemons suficientes dentro no raio para calcular o perímetro." << endl;
    }
    
    cout << endl;
    break;

    
    default: //opção invalida
      cout<<endl;
      break;

  }
}
  return 0;
}