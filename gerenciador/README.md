# Sistema Gerenciador de Arquivos
O sistema gerenciador de arquivos foi desenvolvido em linguagem C e trabalha com arquivos de texto em formato ”.txt”. Ao armazenar esses arquivos, o conteúdo de cada um é dividido em blocos de duzentos bytes até atingir o uso total da memória disponı́vel, que consiste em cem blocos, totalizando 20.000 bytes.
## Modo de uso:
Ao inicializar o programa via terminal o usuário pode informar o(s) nome(s) do(s) arquivo(s) que deseja inserir no sistema, via linha de comando.

Exemplo: ./a.out teste.txt

Em seguida, o programa exibirá um menu com as operações disponíveis e o usuário deve digitar o número correspondente a operação que desejar.
## Operações disponíveis:
1. Inserção
2. Remoção
3. Busca de arquivo
4. Busca de termo
5. Sair do programa