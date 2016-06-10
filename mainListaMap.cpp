	#include <iostream>
	#include <list>
	#include <map>
	#include <algorithm>
	#include <vector>
	
	using namespace std;
	
	class Vertice{
		public:
//			const int branco = 0;
//			const int cinza = 1;
//			const int preto = 2;
			int dado;
			int cor;
			int distancia;
			Vertice *pai;
			int cronometro;
			
			//Lista criada permitindo inserir ou remover vértices
			list< Vertice*> verticeAdjacente;
			//Iterator "lerVertice" criado para ler ou modificar qualquer elemento da lista
			list< Vertice*>::iterator lerVertice;
			
			Vertice(int dado){
				this->dado = dado;
				this->cor = cor;
				this->distancia = distancia;
				this->pai = pai;	
				this->cronometro = cronometro;					
			};
			
			//Destrutor do vértice
			~Vertice(){
				this->dado = 0;
				verticeAdjacente.clear();
			};
	};
	
	class Aresta{
		public:
			int verticeOrigem;
			int verticeDestino;
			
			//Construtor da classe Aresta
			Aresta(int idVertice1, int idVertice2){
				this->verticeOrigem = idVertice1;
				this->verticeDestino = idVertice2;
							
			};
			
			~Aresta(){
				
			}		
	};
	
	class Grafo{
		public:
			/*Os mapas  armazenam elementos associativos formados por uma combinação 
			  de um valor de chave e um valor mapeado, seguindo uma ordem específica.*/
			  
			 /*Em um mapa, os valores chave são geralmente utilizados para classificar
			  e identificar exclusivamente os elementos, enquanto que os valores
			  mapeados armazenar o conteúdo associado a esta chave.*/
			  
			//Map criado para armazenar vertices a partir de um id único
			map<int, Vertice*> vertice;
			//Iteratores "lerVert" e "lerVertAdjacente" criados para ler ou modificar quaisquer elementos em um map
			map<int, Vertice*>::iterator lerVert;
			map<int, Vertice*>::iterator lerVertAdjacente;
			
			//Map criado para armazenar arestas a partir de um id único
			map<int, Aresta*> aresta;
			//Iterator "lerAresta" criado para ler ou modificar qualquer elemento em um map
			map<int, Aresta*>::iterator lerAresta;
			
			//Verifica, a partir do id, se o vértice existe
			bool existeVertice(int id){
				bool existe = false;
				/*.find() retorna um iterador que aponta para o local
				 de um elemento em um mapa com uma chave igual a uma chave especificada*/
				//O iterator deve receber o vértice encontrado a partir do id
				lerVert = vertice.find(id);
				//Se o iterator for diferente de nulo então o vértice existe
				//.end() é o elemento após o último elemento do contido no map, ou seja, NULL
				if(lerVert != vertice.end()){
					existe = true;
				}
				return existe;
			};
			
			//Verifica, a partir do id, se a aresta existe
			bool existeAresta(int id){
				bool existe = false;
				/*.find() retorna um iterador que aponta para o local
				 de um elemento em um mapa com uma chave igual a uma chave especificada*/
				//O iterator deve receber a aresta encontrada a partir do id
				lerAresta = aresta.find(id);
				//Se o iterator for diferente de nulo então a aresta existe
				//.end() é o elemento após o último elemento do contido no map, ou seja, NULL
				if(lerAresta != aresta.end()){
					existe = true;
				}
				return existe;
			};
			
			//Insere aresta a partir de um id único vértice origem e destino passados
			void inserirAresta(int idAresta, int verticeOrigem, int verticeDestino){
				Aresta *a = new Aresta(verticeOrigem, verticeDestino);
				//Adiciona um vértice adjacente a partir do vértice origem
				adicionarVerticeAdjacente(verticeOrigem, verticeDestino);
				//Armazena uam nova aresta com id único e vértices de origem e destino
				aresta[idAresta] = a;
			};
			
			//Adiciona um vértice adjacente a partir do vértice origem
			void adicionarVerticeAdjacente(int idVertice, int idVerticeAdjacente){
				/*.find() retorna um iterador que aponta para o local
				 de um elemento em um mapa com uma chave igual a uma chave especificada*/
				//Os iteratores devem receber os vértices encontrados a partir de seus id's
				lerVert = vertice.find(idVertice);
				lerVertAdjacente = vertice.find(idVerticeAdjacente);
				
				//"->second" acessa o valor de referência mapeada para o elemento
				//O objeto v recebe o valor do vértice origem		
				Vertice *v = lerVert->second;
				//.push_back() Adiciona um novo elemento no final da lista, após o atual último elemento.
				//O vertice adjacente é adicionado na lista junto à referência do vértice origem
				v->verticeAdjacente.push_back(lerVertAdjacente->second);
			};
			
			//Remove aresta a partir de um id único
			void removerAresta(int idAresta){
				int idVertice1;
				int idVertice2;
				/*.find() retorna um iterador que aponta para o local
				 de um elemento em um mapa com uma chave igual a uma chave especificada*/
				//O iterator deve receber a aresta encontrada a partir do id
				lerAresta = aresta.find(idAresta);
				//"->second" acessa o valor de referência mapeada para o elemento
				//As variaveis idVertice1 e idVertice2 receberam os valores dos vértices
				idVertice1 = lerAresta->second->verticeOrigem;
				idVertice2 = lerAresta->second->verticeDestino;
				//Remove um vértice adjacente a partir do vértice origem
				removerVerticeAdjacente(idVertice1, idVertice2);
				//.erase() Remove um elemento que corresponde a uma chave especificada.
				//A aresta é removida a partir de um id único
				aresta.erase(idAresta);
			};	
			
			//Remove um vértice adjacente a partir do vértice origem
			void removerVerticeAdjacente(int idVertice, int idVerticeAdj){
				/*.find() retorna um iterador que aponta para o local
				 de um elemento em um mapa com uma chave igual a uma chave especificada*/
				//Os iteratores devem receber os vértices encontrados a partir de seus id's
				lerVert = vertice.find(idVertice);
				lerVertAdjacente = vertice.find(idVerticeAdj);
				
				//"->second" acessa o valor de referência mapeada para o elemento
				//O objeto v recebe o valor do vértice origem
				Vertice *v = lerVert->second;
				//.remove() Remove um elemento da lista a partir de um id específico
				//O vertice adjacente é removido da lista junto à referência do vértice origem
				v->verticeAdjacente.remove(lerVertAdjacente->second);
			};		
			
			//Inserir novo vértice no vetor passando id único e valor do vértice
			void inserirVertice(int idVertice, int dado){	
				Vertice *v = new Vertice(dado);
				vertice[idVertice] = v;
			};
			
			//Remover vértice do grafo a partir do id
			void removerVertice(int idVertice){
				Aresta *arst;
				for(lerAresta = aresta.begin(); lerAresta != aresta.end(); lerAresta++){
					arst = lerAresta->second;
					if(arst->verticeDestino == idVertice){
						removerVerticeAdjacente(arst->verticeOrigem, arst->verticeDestino);
						removerAresta(lerAresta->first);
					}
					if(arst->verticeOrigem == idVertice){
						removerAresta(lerAresta->first);
					}
				}
				removerVerticeDoGrafoPorId(idVertice);
			};
			
			void removerVerticeDoGrafoPorId(int idVertice){
				Vertice *remove;
				lerVert = vertice.find(idVertice);
				remove = lerVert->second;
				remove->~Vertice();
				vertice.erase(idVertice);
			};
			
			//Exibe a lista de adjacência
			void imprimirGrafo(){
				Vertice *v;
				cout << "Grafo: \n";
				for(lerVert = vertice.begin(); lerVert != vertice.end(); lerVert++){
					v = lerVert->second;
					cout << " ";
					cout << "[";	
					cout << v->dado ;
					cout << "]";
					cout << " -> ";
					Vertice *imprimirVertice;
					for(v->lerVertice = v->verticeAdjacente.begin(); v->lerVertice != v->verticeAdjacente.end(); v->lerVertice++){
						imprimirVertice = *(v->lerVertice);
						cout << imprimirVertice->dado << " -> ";
					}
					cout << endl;
				}
				cout << endl;
				cout << endl;
				/*
				---------------EXIBIÇÃO----------------
				Grafo: 
				[A] -> B -> C  -> NULL
				[B] -> A -> D -> E  -> NULL
				[C] -> B -> A -> NULL
				[D] -> D -> A -> NULL
				[E] -> A -> B -> C -> NULL
				
				*/
			};	
			
			void buscaEmLargura(){
				Vertice *u, *s, *v;
				list< Vertice*> Q;
				list< Vertice*>::iterator lerVertQ;
				// Pega o primeiro elemento da lista
				s = vertice.begin()->second;
				for(lerVert = vertice.begin(); lerVert != vertice.end(); lerVert++){
					u = lerVert->second;
					// cor = 0 (Branco) = Vértice não visitado
					u->cor = 0;
					// Distância do vértice até a raiz
					u->distancia = -1;
					// Pai
					u->pai = NULL;
				}
				// cor = 1 (Cinza) = Vértice sendo visitado
				s->cor = 1;
				s->distancia = 0;
				s->pai = NULL;
				// Q é uma fila
				Q.push_back(s);
				// Exibir raiz
				cout << s->dado;
				while (Q.size() != 0) {
					lerVertQ = Q.begin();
					u = *lerVertQ;
					for(u->lerVertice = u->verticeAdjacente.begin(); u->lerVertice != u->verticeAdjacente.end(); u->lerVertice++){
						v = *(u->lerVertice);
						if(v->cor == 0){
							v->cor = 1;
							v->distancia = u->distancia + 1;
							v->pai = u;
							Q.push_back(v);
							//Exibir vértices adjacentes
							cout << " -> " << v->dado;
						}
					}
					Q.pop_front();
					// cor = 2 (Preto) = Vértice visitado
					u->cor = 2;
				};
			}
				
			void buscaEmProfundidade(){
				Vertice *u, *s;
				// Pega o primeiro elemento da lista
				s = vertice.begin()->second;
				for(lerVert = vertice.begin(); lerVert != vertice.end(); lerVert++){
					u = lerVert->second;
					// cor = 0 (Branco) = Vértice não visitado
					u->cor = 0;
					// Pai
					u->pai = NULL;
				}
				int tempo = 0;
				//int &t = tempo;
				// Exibir raiz
				cout << s->dado;
				for(lerVert = vertice.begin(); lerVert != vertice.end(); lerVert++){
					u = lerVert->second;
					// cor = 0 (Branco) = Vértice não visitado
					if (u->cor == 0)
						buscaEmProfundidadeVisita(u, tempo);
				}
			}
			
			void buscaEmProfundidadeVisita(Vertice *u, int tempo){
				Vertice *v;
				// cor = 1 (Cinza) = Vértice sendo visitado
				u->cor = 1;
				tempo++;
				// Distância do vértice até a raiz
				u->distancia = tempo;
				for(u->lerVertice = u->verticeAdjacente.begin(); u->lerVertice != u->verticeAdjacente.end(); u->lerVertice++){
					v = *(u->lerVertice);
					if(v->cor == 0){
						v->pai = u;
						//Exibir vértices adjacentes
						cout << " -> " << v->dado;
						buscaEmProfundidadeVisita(v, 0);
					}
				}
				// cor = 2 (Preto) = Vértice visitado
				u->cor = 2;
				tempo++;
				// cronometro guarda todos os intervalos de tempo
				u->cronometro = tempo;
			}
	};
	
	int main(int argc, char** argv) {
		Grafo *grafo = new Grafo();
		int opcao, idAresta, verticeOrigem, verticeDestino, idVertice, valorVertice;
		
		do {
			cout << "  ------------------Menu------------\n";
			cout << "  | 1 - Inserir Vertice            |\n";
			cout << "  | 2 - Remover Vertice            |\n";
			cout << "  | 3 - Inserir Aresta             |\n";
			cout << "  | 4 - Remover Aresta             |\n";
			cout << "  | 5 - Imprimir Estrutura         |\n";
			cout << "  | 6 - Imprimir por Largura	   |\n";
			cout << "  | 7 - Imprimir por Profundidade  |\n";
			cout << "  | 8 - Sair                       |\n";
			cout << "  ---------------------------------\n";
			cout << endl;
			cout<< "Digite o numero da opcao desejada: ";
			cin >> opcao;
		
			switch(opcao){
				case 1:
					//Inserir Vértice
					cout << "Digite o id do vertice: ";
					cin >> idVertice;
					
					if(grafo->existeVertice(idVertice)){
						cout << "Vertice já existente!\n\n";
						system("pause");
					}else{
						grafo->inserirVertice(idVertice, idVertice);
					}
					
					//limpa tela
					system("cls");
					
					grafo->imprimirGrafo();
					break;
				case 2:
					//Remover Vértice
					cout << "Digite o id do vertice a ser removido: ";
					cin >> idVertice;
					
					if(grafo->existeVertice(idVertice)){
						grafo->removerVertice(idVertice);
					}else{
						cout << "Vertice não existente!\n\n";
						system("pause");	
					}						
					
					//limpa tela 
					system("cls");
					grafo->imprimirGrafo();
					break;
				case 3:
					//Inserir Aresta
					cout << "Digite o id da aresta: ";
					cin >> idAresta;
					
					if(grafo->existeAresta(idAresta)){
						cout << "Aresta existente!\n\n";
						system("pause");
					}else{
						cout << "Digite o id do vertice origem: ";
						cin >> verticeOrigem; 
						cout << "Digite o id do vertice destino: ";
						cin >> verticeDestino;
						if(grafo->existeVertice(verticeOrigem) && grafo->existeVertice(verticeDestino)){
							grafo->inserirAresta(idAresta, verticeOrigem, verticeDestino);
						}else{
							cout << "Vertices inválidos!\n\n";
							system("pause");
						}
					}
					
					//limpa tela 
					system("cls");
					grafo->imprimirGrafo();
					break;
				case 4:
					//Remover Aresta
					cout << "Digite o id da aresta: ";
					cin >> idAresta;
					
					if(grafo->existeAresta(idAresta)){
						grafo->removerAresta(idAresta);
					}else{
						cout << "Aresta não existente!\n\n";
						system("pause");
					}
					
					//limpa tela 
					system("cls");
					grafo->imprimirGrafo();
					break;
				case 5:
					//Imprimir Estrutura
					//Limpa tela
					system("cls");
					grafo->imprimirGrafo();
					break;
				case 6:
					//Limpa tela
					system("cls");
					grafo->buscaEmLargura();
					break;
				case 7:
					//Limpa tela
					system("cls");
					grafo->buscaEmProfundidade();
					break;
				case 8:
					cout<<"Saindo...\n";
					break;
				default:
					//Limpa tela
					system("cls");
					cout << "\nOpcao invalida, tente novamente.\n";
				break;
			}
		} while(opcao != 8);
		
		return 0;
	}

