# criticality-search
 ## tipos de busca:
  **hill_climbing** - hill climbing puro
  **simulated_annealing** - simulated annealing puro
  **optimized_hillclimbing** - hill climbing selecionado aleatoriamente tuplas não observáveis, e depois realiza A em cada uma delas*
  **optimized_dfs** - realiza uma dfs até uma tupla não observável e depois um hill climbing ao contrário para encontrar a ck
  **reverse_dfs** - realiza uma busca dfs partido de uma rede totalmente sem medidas até encontrar a rede totalmente observável
  **successive_hill_climbing** - aplica sucessivas hill climbing partindo da rede com totas medidas e, conforme uma ck é encontrada, ele diminui a árvore a partir dela
  **reverse_hill_climbing** - aplica sucessivas hill climbing partindo da rede sem medidas e vai inserindo até que ela se torne observaváel. A partir da ck encontrada ele diminui a árvore. 
