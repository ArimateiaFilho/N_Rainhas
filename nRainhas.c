#include<stdio.h>
#include<stdlib.h>

FILE *arq;

int main(){
	int n, i, j, a, b, c;
	
	arq = fopen("clausulas.cnf", "w");
	printf("Informe n: ");
	scanf("%d", &n);
 	long long int numeroC=0;
 	
 	numeroC=2*n*(n*(n-1))/2;
 	numeroC=numeroC+n;
 	for (i = 0; i < n; i++){
    	for (j = 0; j < n; j++){
			//Diagonal cima p/ baixo
			//Esquerda p/ direita
			b = i + 1;
			c = j + 1;
			while(b < n && c < n){
    			b++;
    			c++;
    			numeroC++;
			}
			//Direita p/ esquerda
			b = i + 1;
			c = j - 1;
			while(b < n && c >= 0){
				b++;
    			c--;
    			numeroC++;
			}
		}
	}
 	
 	
    int **m = (int**)malloc(n * sizeof(int*));
 
    for (i = 0; i < n; i++){
        m[i] = (int*)malloc(n * sizeof(int));
    }
    

    fprintf(arq, "p cnf %d %lld\n", n*n,numeroC);
    
    for (i = 0; i < n; i++){
    	for (j = 0; j < n; j++){
    		if(i == 0){
    			m[i][j] = j+1;
			}else{
				m[i][j] = m[i-1][j]+n;
			}
			fprintf(arq, "%d ", m[i][j]);
		}
		fprintf(arq, "0\n");
	}
	
	for (i = 0; i < n; i++){
    	for (j = 0; j < n; j++){
    		a = m[i][j];
    		//Linhas
    		//Esquerda p/ direita
    		b = j + 1;
    		while(b < n){
    			fprintf(arq, "%d %d 0\n", -a, -m[i][b]);
    			b++;
			}
			//Colunas
			//Cima p/ baixo
			b = i + 1;
			while(b < n){
				fprintf(arq, "%d %d 0\n", -a, -m[b][j]);
    			b++;
			}
			//Diagonal cima p/ baixo
			//Esquerda p/ direita
			b = i + 1;
			c = j + 1;
			while(b < n && c < n){
				fprintf(arq, "%d %d 0\n", -a, -m[b][c]);
    			b++;
    			c++;
			}
			//Direita p/ esquerda
			b = i + 1;
			c = j - 1;
			while(b < n && c >= 0){
				fprintf(arq, "%d %d 0\n", -a, -m[b][c]);
    			b++;
    			c--;
			}
		}
	}
    
    
    
    
	
	for (i = 0; i < n; i++){
        free(m[i]);
    }
    free(m);
	fclose(arq);
	
	system("./glucose_static clausulas.cnf saida.txt");
	
	arq=fopen("saida.txt","r");
	
	int num,opa=1;
	for(i=0;i<n*n;i++){
		fscanf(arq,"%i",&num);
		if(num>0){
			int resul=num%n;
			if(resul==0){
				resul=n;
			}
			printf("[%i]: %i\n",opa,resul);
			opa++;
		}
	}
	
	fclose(arq);
	
	return 0;
}

