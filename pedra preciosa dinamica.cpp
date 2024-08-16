#include <iostream>
using namespace std;

// fun��o para encontrar o valor m�ximo que pode ser carregado no carrinho
int knapSack(int W, int wt[], int val[], int n) {
    // K � uma matriz onde cada elemento K[i][w] representa o valor m�ximo que pode ser carregado
    // considerando apenas os primeiros i itens e com uma capacidade m�xima de w
    int K[n + 1][W + 1];

    // construir tabela K[][] de baixo para cima
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0; // base da programa��o din�mica: se n�o h� itens ou capacidade, o valor � 0
            else if (wt[i - 1] <= w)
                // se o volume do item atual pode ser inclu�do, escolhe o maior valor entre incluir ou n�o o item
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                // se o volume do item atual n�o pode ser inclu�do, mant�m o valor anterior
                K[i][w] = K[i - 1][w];
        }
    }

    // o valor m�ximo que pode ser carregado no carrinho � K[n][W]
    return K[n][W];
}

int main() {
    int n = 4; // n�mero de tipos de pedras preciosa
    int W = 400; // capacidade m�xima do carrinho em cm  c�bicos 
    int val[] = {500, 410, 320, 315}; // valor das pedras
    int wt[] = {455, 521, 87, 65}; // volume das pedras em cm c�bicos

    // chama a fun��o knapSack e exibe o valor m�ximo que pode ser carregado no carrinho
    cout << "Valor m�ximo: " << knapSack(W, wt, val, n) << endl;
    return 0;
}