  double *array = malloc(sizeof(double)*N);
  mbind(&array[0], N/4*sizeof(double),
	MPOL_BIND, &nodemask, maxnode,
	MPOL_MF_MOVE);

  #pragma omp parallel for
  for(int i=0; i<N; i++) {
    double value = array[i];
    /* ... */
  }
