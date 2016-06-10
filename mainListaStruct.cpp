	#include <iostream>
	#include <locale.h>
	#include <stdio.h>
	#include <stdlib.h>
	
	using namespace std;
	
	typedef struct grafo Grafo;
	
	// Definição do tipo Grafo
	struct grafo{
		//Determina se o grafo é ponderado ou  não
		int numVertices;
		//Determina o grau de todos os vertices do grafo
		int grauMax;
		//Determina as arestas do grafo
		int** arestas;
		//Determina o grau do grafo
		int* grau;
	};
	
	//Cria um novo grafo
	Grafo* criaGrafo(int numVertices, int grauMax){
		//aloca espaço na memoria para o novo grafo
		Grafo *grafo=(Grafo*) malloc(sizeof(struct grafo));
		
		//verifica se o grafo existe
		if(grafo != NULL){
			//Grafo existe
			
			//popula o grafo
			grafo->numVertices = numVertices;
			grafo->grauMax = grauMax;
			grafo->grau = (int*) calloc(numVertices, sizeof(int));
			grafo->arestas = (int**) malloc(numVertices* sizeof(int*));
			
			//aloca espaço de memoria para as arestas
			for(int i=0; i < numVertices; i++)
				grafo->arestas[i] = (int*) malloc(grauMax* sizeof(int));
			}
	
		return grafo;
	}
	
	//deleta o grafo
	void deletarGrafo(Grafo* grafo){
		//verifica se o grafo existe
		if(grafo != NULL){
			//Grafo existe
						
			// Limpa a matriz de arestas desalocando os espaços de memoria ocupados por ela
			for(int i=0; i < grafo->numVertices; i++){ 
				free(grafo->arestas[i]);
			}
			free(grafo->arestas);
			
			// limpa estruturas iniciais.
			free(grafo->grau);
			free(grafo);
		}
	}
	
	//insere uma aresta
	int inserirAresta(Grafo* grafo, int origem, int destino, int ehDigrafo){
		
		// Verifica se o grafo existe
		if(grafo == NULL)
			return 0;
		
		// Verifica se o vértice origem já existe	
		if(origem < 0 || origem >= grafo->numVertices){
			//Vertice não existe
			return 0;
		}
				
		//Verifica se o  vertices destino já existe
		if(destino < 0 || destino >= grafo->numVertices){
			//Vertice não existe
			return 0;
		}
			
		// Procura a aresta
		int i = 0;
		while(i < grafo->grau[origem] && grafo->arestas[origem][i] != destino){
			i++;
		}
		
		if(i != grafo->grau[origem]) {
			//aresta já existe
			return 0;
		}
		// Insere no final da lista	
		grafo->arestas[origem][grafo->grau[origem]] = destino;
		grafo->grau[origem]++;
		
		// Insere a outra aresta no sentido contrario se não for dígrafo
		if(ehDigrafo == 0){
			inserirAresta(grafo, destino, origem, 1);
		}
		return 1;
	}
	
	//remove uma aresta
	int removerAresta(Grafo* grafo, int origem, int destino, int ehDigrafo){
		
		// Verifica se o grafo é válido
		if(grafo == NULL){
			return 0;		
		}
			
		// Verifica se o vértice origem existe	
		if(origem < 0 || origem >= grafo->numVertices){
			//Não existe
			return 0;
		}
				
		// Verifica se o vértice destino existe		
		if(destino < 0 || destino >= grafo->numVertices){
			//Não existe
			return 0;
		}
		
		// Procura a aresta	
		int i = 0;
		while(i < grafo->grau[origem] && grafo->arestas[origem][i] != destino){
			i++;
		}
			
			
		if(i == grafo->grau[origem]) {
			// Elemento não encontrado
			return 0;
		}		
		// Copia o elemento da última posição	
		grafo->grau[origem]--;
		//aloca esse elemento no local do elemento removido
		grafo->arestas[origem][i] = grafo->arestas[origem][grafo->grau[origem]];
		
		// remove a aresta no sentido contrario se NÃO for dígrafo	
		if(ehDigrafo == 0){
			removerAresta(grafo, destino, origem, 1);
		}
					
		return 1;	
	}
	
		//insere um vertice
	Grafo* inserirVertice(Grafo * grafo, int numVertice){
		if(grafo == NULL){
			//O numero de vértices será igual ao grau máximo
			return criaGrafo(numVertice, numVertice);
		}else{
			int opc;
			cout << "Grafo já criado!";
			cout << endl;
			cout << "Deseja criar outro grafo?\nSim = 1\nNão = 2\n";
			cin >> opc;
			
			if(opc == 1){
				deletarGrafo(grafo);
				return criaGrafo(numVertice, numVertice);
			}
			
			system("pause");
			return grafo;
		}
	}
	
	 //remover vertices
    void removerVertice(Grafo* grafo , int vertice){
        //verifica se o grafo existe
        if(grafo != NULL){
            int* teste; 
            //grafo exite
            //verifica se o vertice a ser removido existe
            //if(grafo->arestas[vertice] != NULL){
                    //vertice exite
                    //percorre o grafo deletando onde o vertive a ser removido é adjacente
                    for (int i = 0; i < grafo->numVertices; i++){
                        removerAresta(grafo, i, vertice, 1);
                        //free(grafo->arestas[i][vertice]);
                    }
                    
                    //deleta o vertice
                    free(grafo->arestas[vertice]);
                
                    //atualiza o numero de vertices existente no grafo
                    grafo->numVertices = grafo->numVertices - 1;
                    //atualiza o grau dos vertices
                    grafo->grauMax = grafo->numVertices;
        //        }
        //    }     else{
        //        cout<<"\nVertice não existe!";
        //        system("pause");
        //    }
        } else{
            cout<<"\nGrafo não existe!";
            system("pause");
        }
    }
	
	// Função auxiliar: realiza o cálculo
	void buscarProfundidade(Grafo *grafo, int inicio, int *visitado, int contador){
		string separador = "  |__";
		
		// Marca o vértice como visitado. Visita os vertices adjacentes ainda não visitados.
		visitado[inicio] = contador;
		
		//Exibe o primeiro elemento visitado
		cout << " " << inicio <<  "(Pai)\n";
		
		//Monta a exibição do grafo
		for(int i=0; i < grafo->grau[inicio]; i++){
			//Se o grau do vértice for maior que 0 e não tiver sido visitado ainda este será um pai
			if(grafo->grau[inicio] > 0 && !visitado[grafo->arestas[inicio][i]]){
				cout << separador << grafo->arestas[inicio][i] << "(Pai)\n";
				separador = "	" + separador;
				buscarProfundidade(grafo, grafo->arestas[inicio][i], visitado, contador+1);
			}else{
				cout << separador << grafo->arestas[inicio][i] << "\n";
				buscarProfundidade(grafo, grafo->arestas[inicio][i], visitado, contador+1);
			}
		}
	}
		
	// Função principal: faz a interface com o usuário
	void buscarProfundidadeGrafo(Grafo *grafo, int inicio, int *visitado){
		int contador = 1;
		
		// Marca vértices como NÃO visitados
		for(int i=0; i< grafo->numVertices; i++){
			visitado[i] = 0;
		}
		buscarProfundidade(grafo, inicio, visitado, contador);
		system("pause");
	}
	
	void buscarLargura(Grafo *grafo, int inicio, int *visitado){
		
		int vertice, numVertives, contador = 1, *fila, inicioFila = 0, fimFila = 0;
		string separador = "  |__";
		
		if(grafo != NULL){
			// Marca vértices como NÃO visitados
			for(int i=0; i < grafo->numVertices; i++){
				visitado[i] = 0;
			}
						
			// Cria fila. Visita e insere "inicio" na fila	
			numVertives = grafo->numVertices;
			fila = (int*) malloc(numVertives * sizeof(int));
			fimFila++;
			fila[fimFila] = inicio;
			visitado[inicio] = contador;
			
			//Exibe o primeiro elemento visitado
			cout << " " << inicio <<  "(Pai)\n";
			
			while(inicioFila != fimFila){
				// Pega o primeiro da fila
				inicioFila = (inicioFila + 1) % numVertives;
				vertice = fila[inicioFila];
				contador++;
				
				// Visita os vizinhos ainda não visitados e coloca na fila
				for(int i=0; i < grafo->grau[vertice]; i++){
					if(!visitado[grafo->arestas[vertice][i]]){
						fimFila = (fimFila + 1) % numVertives;
						fila[fimFila] = grafo->arestas[vertice][i];
						visitado[grafo->arestas[vertice][i]] = contador;
						
						//Monta a exibição do grafo
						//Pega valor do vértice adjacente
						int adj = grafo->arestas[vertice][i];
						
						//Se o grau do vértice for maior que 0 e não tiver sido visitado ainda este será um pai
						if(grafo->grau[adj] > 0 && !visitado[grafo->arestas[adj][i]]){
							cout << separador << grafo->arestas[vertice][i] << "(Pai)\n";
							separador = "	" + separador;
						}else{
							cout << separador << grafo->arestas[vertice][i] << "\n";
						}
					}
					cout << endl;
				}
			}
			
			system("pause");
			free(fila);
		}
	}
	
	void imprime(Grafo *grafo) {
		cout << "   ";
		cout<<"GRAFO - LISTA DE ADJACÊNCIAS:";
		cout << endl;
		cout << endl;

		for (int i = 0; i < grafo->numVertices; i++) {
			cout << "   ";
			//exibe os vertices
			cout << "[" << i <<  "]";
			for (int j = 0; j < grafo->grau[i]; j++) {
				//exibe os vertices adjacentes
				cout << " -> " << grafo->arestas[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	
	int main() {
		
		setlocale(LC_ALL, "Portuguese");
		Grafo* grafo = NULL;
		int opcao, origem, destino, numeroVertice;
		
		do {
			cout << "  ------------------Menu-------------------\n";
			cout << "  | 1 - Inserir Vertice                    |\n";
			cout << "  | 2 - Remover Vertice                    |\n";
			cout << "  | 3 - Inserir Aresta                     |\n";
			cout << "  | 4 - Remover Aresta                     |\n";
			cout << "  | 5 - Imprimir Estrutura                 |\n";
			cout << "  | 6 - Imprimir Estrutura por Largura     |\n";
			cout << "  | 7 - Imprimir Estrutura por Profundidade|\n";
			cout << "  | 8 - Sair                               |\n";
			cout << "  -----------------------------------------\n";
			cout << endl;
			cout<< "Digite o número da opção desejada: ";
			cin >> opcao;
			cout << endl;
		
			switch(opcao){
				case 1:
					//insere vertice
					cout << "Digite o número de vértices do grafo: ";
					cin >> numeroVertice;
					//grafo->numVertices = numeroVertice;
					grafo = inserirVertice(grafo, numeroVertice);			
					//limpa tela 
					system("cls");

					//imprimi o grafo					
					imprime(grafo);
					break;
				case 2:
					//remover vertice
					cout << "Digite o vértice que deseja excluir: ";
					cin >> numeroVertice;
					removerVertice(grafo, numeroVertice);
					//limpa tela 
					system("cls");

					//imprimi o grafo					
					imprime(grafo);						
					break;
				case 3:
					//insere aresta
					cout<<"Digite o vertice origem:";
					cin>>origem;
					cout<<"Digite o vertice destino:";
					cin>>destino;
					
					if(inserirAresta(grafo, origem , destino, 1)  != 1){
						cout<<"\nAresta e/ou Vértices inválidos!\n";
						system("pause");
					}					
					//limpa tela 
					system("cls");
					
					//imprimi o grafo
					imprime(grafo);
					break;
				case 4:
					//remove aresta
					cout<<"Digite o vertice origem:";
					cin>>origem;
					cout<<"Digite o vertice destino:";
					cin>>destino;
					
					if(removerAresta(grafo, origem, destino, 1) != 1){
						cout<<"\nAresta e/ou Vértices inválidos!\n";
						system("pause");
					}
					
					//limpa tela 
					system("cls");

					//imprimi o grafo					
					imprime(grafo);
					break;
				case 5:
					//limpa tela 
					system("cls");

					//imprimi o grafo					
					imprime(grafo);
					break;
				case 6:
					//imprimi o grafo pelo algoritmo de largura
					//vetor contendo número de vértices
					int visitado[3];
					
					cout << "   ";
					cout << "GRAFO - ALGORITMO DE BUSCA EM LARGURA\n";
					cout << endl;
					
					buscarLargura(grafo, 0 , visitado);
					
					//limpa tela 
					system("cls");
					break;
				case 7:
					//imprimi o grafo pelo algoritmo de profundidade
					//vetor contendo número de vértices
					int vertVisitado[3];
					
					cout << "   ";
					cout << "GRAFO - ALGORITMO DE BUSCA EM PROFUNDIDADE\n";
					cout << endl;
					
					buscarProfundidadeGrafo(grafo, 0 , vertVisitado);
					
					//limpa tela 
					system("cls");
					break;
				case 8:
					//encerra a aplicação
					cout<<"Saindo...\n";
					break;
				default:
					//Limpa 
					system("cls");
					cout << "\nOpcao inválida, tente novamente.\n";
				break;
			}
		} while(opcao != 8);
		
		return 0;
	}

