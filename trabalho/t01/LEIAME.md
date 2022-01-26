### Sobre

Estou utilizando os seguintes comandos para executar a aplicação:

> Para testar com um arquivo contendo todos os tokens:

```
make clean; make && ./etapa1 testeAll-in.txt testeAll-out.txt
```

> Para testar um programa sem erros sintaticos:

```
make clean; make && ./etapa1 testeProg-in.txt testeProg-out.txt
```

> Para testar um programa com erros sintaticos:

```
make clean; make && ./etapa1 testeErr-in.txt testeErr-out.txt
```
