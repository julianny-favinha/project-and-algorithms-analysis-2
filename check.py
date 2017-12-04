#!/usr/bin/python3
"""
Na mesma pasta de check.py deve existir:
pasta 'saida' do ped
pasta 'aluno' com suas saidas

ele vai criar arquivos onesXX.txt que contem somente os vertices das saidas
e comparar as suas com as do ped, linha a linha, de maneira bem ineficiente.
Caso seu programa tenha linhas diferentes, some todas que terminam com 1 e compare
com a soma de todas que terminam com 0. Se o resultado for o mesmo seu caminho
tambem e minimo
"""

# Isola os vertices dos arquivos de saida
for i in range(1, 7):
    out = open('saida/out0' + str(i) + '.txt', 'r')
    ones = open('saida/ones0' + str(i) + '.txt', 'w')
    out2 = open('aluno/out0' + str(i) + '.txt', 'r')
    ones2 = open('aluno/ones0' + str(i) + '.txt', 'w')
    for line in out:
        if len(line) > 1 and line[:2] == 'X_':
            ones.write(line)
    for line in out2:
        if len(line) > 1 and line[:2] == 'X_':
            ones2.write(line)
    out.close()
    out2.close()
    ones.close()
    ones2.close()

# Compara as linhas em O(n^n)
n = 0
for i in range(1, 7):
    saida = open('saida/ones0' + str(i) + '.txt', 'r')
    for saida_line in saida:
        aluno = open('aluno/ones0' + str(i) + '.txt', 'r')
        found = 0
        for aluno_line in aluno:
            if aluno_line == saida_line:
                found = 1
                break
        if found != 1:
            n += 1
            print('nao achou linha', '"'+saida_line[:len(saida_line)-1]+'"', 'na entrada', str(i))
        aluno.close()
    saida.close()
print(str(n), 'linhas nao encontradas')
