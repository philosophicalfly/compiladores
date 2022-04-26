## Informações básicas

> Para executar o programa fim a fim em minha máquina, utilizei:

```bash
make clean; make && ./etapa6 testescan.azby out.txt 
```

A saida deve mostrar na stderr:

- AST
- TACs
- HASH Table

> Para ver o ASM gerado, com comentários por TAC:

 ```bash
 cat out.s && gcc out.s && ./a.out
 ```
> Para executar o ASM gerado (não sei se funciona em Mac pois minha arquitetura não permite a main começando por underline)

````bash
gcc out.s && ./a.out
````



## O que/como foi feito:

Vou descrever resumidamente as principais alterações do código abaixo:

### Alterações nas TACs

- Gerada uma nova TAC para lidar com atribuições de vetor para vetor, pois uma só não conseguia contemplar todos os nomes de variáveis e valores.

- Alterada a tac parametros de função para fazer match entre o índice de cada parametro e a declaração, percorrendo recursivamente a AST
- Corrigida TAC de `while` que não continha um label final

### Geração de ASM

- Assim como mostrado na aula, para cada TAC, busquei reproduzir um código C que as representasse, entender o funcionamento, e "clonar" as instruções geradas de forma dinâmica no para a nossa linguagem.

## O que ficou devendo:

- Operações com float;

- Declarações sem inicialização;
- Algumas formatações de print;

## Exemplos:

### Exemplo 1:

No seguinte programa, é executado um simples Fibbonacci:

```c
int i: 2;
int fib_um: 0;
int fib_dois: 1;
int res: 0;

int main(){
    while (i <= 10) {
        i = i+1;
        res = fib_um + fib_dois;
        fib_um = fib_dois;
        fib_dois = res;
        print res;
    };
}
```

O resultado da execução mostra a sequencia de Fibbonacci:

```bash
1
2
3
5
8
13
21
34
55
```



### Exemplo 2:

No seguinte programa, dado pelo professor, comentei as linhas que não conseguem ser compiladas e enviei executei o programa.

````c
\* Abaixo arquivo exemplo fornecido pelo professor: *\
\* UFRGS - Compiladores - Marcelo Johann - 2021/2 *\

char c: 'x';
char d: 100;
int a: 'A';
int i: 1;
int v[10]: 'a' 0 0 0 0 0 0 0 0 0;
\\ int matrix[100]; #COMENTADO 
float f: 2/3;

\*
This is a comment 
of multiple lines
*\

int main ()
{
    a = 0;
    a = a - i;
    a = 5;
    v[a] = 55;
    \\ print v[5]; #COMENTADO
    print a;
    i = 2;

    print "Digite um numero: \n";
    a = read;

    while i<10
    {
        i = incn(i,1);
        a = incn(a,1);
    };

    print "Incrementado algumas vezes a fica " , a ,"\n";

    if a==15 then
    {
        label-x:
        a = a - 1;
        print "A era=15\n";
    };

    if (i==100) then
    {
        print "Nao tem como isso...\n";
    }
    else
        print "OK!\n";
    if a > 0 then 
        goto label-x;
}

int incn (int x , int n)
{
    return x+n;
}``
````

O resultado das execuções estão abaixo, com entradas `-5` e `0`.

```bash
5
Digite um numero: 

-5\ #MINHA ENTRADA
Incrementado algumas vezes a fica 
3


OK!

A era=15

OK!

A era=15

OK!

A era=15

OK!


```

```bash
5
Digite um numero: 

0\n #MINHA ENTRADA
Incrementado algumas vezes a fica 
8


OK!

A era=15

OK!

A era=15

OK!

A era=15

OK!

A era=15

OK!

A era=15

OK!

A era=15

OK!

A era=15

OK!

A era=15

OK!
