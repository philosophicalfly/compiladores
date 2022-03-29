### Sobre

Estou utilizando os seguintes comandos na raiz da aplicação para executá-la:

> Em um primeiro terminal, para ver o arquivo decompilado em tempo real:

```
tail -f out2.txt
```

> Em um segundo terminal, para ver o diff de arquivos continuamente:

```
watch -n 1 diff out1.txt out2.txt
```

> Em um último terminal, para executar o programa:

```
make clean; make && ./etapa3 testeCru.azby out1.txt && ./etapa3 out1.txt out2.txt
```