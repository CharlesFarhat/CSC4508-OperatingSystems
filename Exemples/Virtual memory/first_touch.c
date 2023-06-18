  double *array = malloc(sizeof(double)*N);

  for(int i=0; i<N; i++) {
    array[i] = something(i);
  }

  #pragma omp parallel for
  for(int i=0; i<N; i++) {
    double value = array[i];
    /* ... */
  }
