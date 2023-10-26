# Octotropo

## Compilando
```powershell
 gcc .\octotropo.c -o .\octotropo
```
## Executando
```powershell
.\octotropo.exe
```

## Pseudocódigo – Core de validação para Jogo da Velha
```text

var
    int linha_contador = 0
    int coluna_contador = 0
    char peças[2] = {‘X’, ‘O’}

início
    //movimento horizontal
    para linha_contador com início 0 execute enquanto for menor que 3
        para coluna_contador com início 0 execute enquanto for menor que 3
            se peças[0] for igual a tabuleiro_matriz[linha_contador][coluna_contador]
                pontuação soma 1
    
        se pontuação for igual 3 entao
            encerra jogo!!
    
    //movimento vertical
    para coluna_contador com início 0 execute enquanto for menor que 3
        para linha_contador com início 0 execute enquanto for menor que 3
            se peças[0] for igual a tabuleiro_matriz[linha_contador][coluna_contador]
                pontuação soma 1
        
        se pontuação for igual 3 entao
            encerra jogo!!
    
    //movimento diagonal da esquerda para direita
    //inicializa contador coluna
    coluna_contador = 0
    
    para linha_contador com início 0 execute enquanto for menor que 3
        se peças[0] for igual a tabuleiro_matriz[linha_contador][coluna_contador++] então
            pontuação soma 1
    
    se pontuação for igual a 3 então
        encerra jogo!!
    
    //movimento diagonal da direita para esquerda
    //inicializa contador coluna
    coluna_contador = 2
    
    para linha_contador com início 0 execute enquanto for menor que 3
        se peça for igual a tabuleiro_matriz[linha_contador][coluna_contador--] então
            pontuação soma 1
    
    se pontuação for igual a 3 entao
        encerra jogo!!

fim

```