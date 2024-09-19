#include <stdio.h>

int main() {
    int jogadores, partidas, fez_gol_em_todas;
    
    scanf("%d %d", &jogadores, &partidas);

    int gols[jogadores][partidas];
    int contagem = 0;

   
    for (int i = 0; i < jogadores; i++) {
         fez_gol_em_todas = 1;  
    
        for (int j = 0; j < partidas; j++) {
            scanf("%d", &gols[i][j]);

            if (gols[i][j] == 0) {
                fez_gol_em_todas = 0;
            }
        }

        
        if (fez_gol_em_todas) {
            contagem++;
        }
    }

    printf("%d\n", contagem);

    return 0;
}
