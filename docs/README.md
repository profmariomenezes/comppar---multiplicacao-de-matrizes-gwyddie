# Multiplicação de matrizes

Para começarmos, o algoritmo abaixo foi o primeiro desenvolvido, seguindo,
basicamente, uma forma mais direta de raciocínio.

```c
void matrixMultiply(struct matrix *a, struct matrix *b, struct matrix *result) {
  int i, j, k;

  if (a->j != b->i) {
    matrixInit(result, 0, 0);
    return;
  }

  matrixInit(result, a->i, b->j);

  for (i = 0; i < result->i; i++)
    for (j = 0; j < result->j; j++)
      for (k = 0; k < result->i; k++)
        result->matrix[i][j] += a->matrix[i][k] * b->matrix[k][j];
}
```

Os resultados de sua execução com matrizes de tamanhos variáveis com
otimizações desligadas (`-O0`) e ligadas (`-O3`), são, respectivamente:

    MULTIPLYING MATRICES OF SIZE 32 x 32: spent 0.000123 seconds
    MULTIPLYING MATRICES OF SIZE 64 x 64: spent 0.001233 seconds
    MULTIPLYING MATRICES OF SIZE 128 x 128: spent 0.008639 seconds
    MULTIPLYING MATRICES OF SIZE 256 x 256: spent 0.066966 seconds
    MULTIPLYING MATRICES OF SIZE 512 x 512: spent 0.418576 seconds
    MULTIPLYING MATRICES OF SIZE 640 x 640: spent 0.819442 seconds
    MULTIPLYING MATRICES OF SIZE 768 x 768: spent 1.425671 seconds
    MULTIPLYING MATRICES OF SIZE 896 x 896: spent 2.309576 seconds
    MULTIPLYING MATRICES OF SIZE 1024 x 1024: spent 4.418335 seconds
    MULTIPLYING MATRICES OF SIZE 1536 x 1536: spent 17.575114 seconds

---

    MULTIPLYING MATRICES OF SIZE 32 x 32: spent 0.000021 seconds
    MULTIPLYING MATRICES OF SIZE 64 x 64: spent 0.000170 seconds
    MULTIPLYING MATRICES OF SIZE 128 x 128: spent 0.001525 seconds
    MULTIPLYING MATRICES OF SIZE 256 x 256: spent 0.018144 seconds
    MULTIPLYING MATRICES OF SIZE 512 x 512: spent 0.156148 seconds
    MULTIPLYING MATRICES OF SIZE 640 x 640: spent 0.210908 seconds
    MULTIPLYING MATRICES OF SIZE 768 x 768: spent 0.389395 seconds
    MULTIPLYING MATRICES OF SIZE 896 x 896: spent 0.626912 seconds
    MULTIPLYING MATRICES OF SIZE 1024 x 1024: spent 1.564676 seconds
    MULTIPLYING MATRICES OF SIZE 1536 x 1536: spent 4.465722 seconds

Por fim, após a leitura do [artigo](https://software.intel.com/content/www/us/en/develop/articles/putting-your-data-and-code-in-order-optimization-and-memory-part-1.html)
disponibilizado pela plataforma do Moodle e reordenando os `for`s de `ijk`
para `ikj` de maneira a otimizar a utilização do cache, chegamos aos
resultados abaixo, em `-O0` e `-O3`, respectivamente:

    MULTIPLYING MATRICES OF SIZE 32 x 32: spent 0.000314 seconds
    MULTIPLYING MATRICES OF SIZE 64 x 64: spent 0.002365 seconds
    MULTIPLYING MATRICES OF SIZE 128 x 128: spent 0.007938 seconds
    MULTIPLYING MATRICES OF SIZE 256 x 256: spent 0.066088 seconds
    MULTIPLYING MATRICES OF SIZE 512 x 512: spent 0.374423 seconds
    MULTIPLYING MATRICES OF SIZE 640 x 640: spent 0.725389 seconds
    MULTIPLYING MATRICES OF SIZE 768 x 768: spent 1.264651 seconds
    MULTIPLYING MATRICES OF SIZE 896 x 896: spent 1.986973 seconds
    MULTIPLYING MATRICES OF SIZE 1024 x 1024: spent 2.961490 seconds
    MULTIPLYING MATRICES OF SIZE 1536 x 1536: spent 9.969929 seconds

---

    MULTIPLYING MATRICES OF SIZE 32 x 32: spent 0.000064 seconds
    MULTIPLYING MATRICES OF SIZE 64 x 64: spent 0.000481 seconds
    MULTIPLYING MATRICES OF SIZE 128 x 128: spent 0.003558 seconds
    MULTIPLYING MATRICES OF SIZE 256 x 256: spent 0.008878 seconds
    MULTIPLYING MATRICES OF SIZE 512 x 512: spent 0.060325 seconds
    MULTIPLYING MATRICES OF SIZE 640 x 640: spent 0.090556 seconds
    MULTIPLYING MATRICES OF SIZE 768 x 768: spent 0.153404 seconds
    MULTIPLYING MATRICES OF SIZE 896 x 896: spent 0.244109 seconds
    MULTIPLYING MATRICES OF SIZE 1024 x 1024: spent 0.373289 seconds
    MULTIPLYING MATRICES OF SIZE 1536 x 1536: spent 1.235718 seconds

Com isso, concluímos que é possível obter uma melhora brusca de performance em
com um algoritmo projetado de modo a tirar proveito dos princípios de localidade
temporal e espacial de memória. No caso de uso acima, sem otimizações de compilador,
tivemos uma melhora de 1.76x no tempo de execução, enquanto, com otimizações ligadas, o
ganho foi ainda de 3.61x para as matrizes de tamanho 1536.
