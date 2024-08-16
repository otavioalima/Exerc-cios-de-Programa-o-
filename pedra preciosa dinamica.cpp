#include <iostream>
using namespace std;

// função para encontrar o valor máximo que pode ser carregado no carrinho
int knapSack(int W, int wt[], int val[], int n) {
    // K é uma matriz onde cada elemento K[i][w] representa o valor máximo que pode ser carregado
    // considerando apenas os primeiros i itens e com uma capacidade máxima de w
    int K[n + 1][W + 1];

    // construir tabela K[][] de baixo para cima
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0; // base da programação dinâmica: se não há itens ou capacidade, o valor é 0
            else if (wt[i - 1] <= w)
                // se o volume do item atual pode ser incluído, escolhe o maior valor entre incluir ou não o item
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                // se o volume do item atual não pode ser incluído, mantém o valor anterior
                K[i][w] = K[i - 1][w];
        }
    }

    // o valor máximo que pode ser carregado no carrinho é K[n][W]
    return K[n][W];
}

int main() {
    int n = 4; // número de tipos de pedras preciosa
    int W = 400; // capacidade máxima do carrinho em cm  cúbicos 
    int val[] = {500, 410, 320, 315}; // valor das pedras
    int wt[] = {455, 521, 87, 65}; // volume das pedras em cm cúbicos

    // chama a função knapSack e exibe o valor máximo que pode ser carregado no carrinho
    cout << "Valor máximo: " << knapSack(W, wt, val, n) << endl;
    return 0;
}