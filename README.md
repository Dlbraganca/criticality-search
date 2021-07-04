# criticality-search
 ## tipos de busca:
  **1. hill_climbing** - hill climbing puro  
  **2. simulated_annealing** - simulated annealing puro  
  **3. optimized_hillclimbing** - hill climbing selecionado aleatoriamente tuplas não observáveis, e depois realiza A em cada uma delas*  
  **4. optimized_dfs** - realiza uma dfs até uma tupla não observável e depois um hill climbing ao contrário para encontrar a ck  
  **5. reverse_dfs** - realiza uma busca dfs partido de uma rede totalmente sem medidas até encontrar a rede totalmente observável  
  **6. successive_hill_climbing** - aplica sucessivas hill climbing partindo da rede com totas medidas e, conforme uma ck é encontrada, ele diminui a árvore a partir dela  
  **7. reverse_hill_climbing** - aplica sucessivas hill climbing partindo da rede sem medidas e vai inserindo até que ela se torne observaváel. A partir da ck encontrada ele diminui a árvore  
  **8. random_start_a_search** - busca A* com inicio aleatório dentro da árvore e com número máximo para cado iteração.
