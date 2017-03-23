/*
 *  tsne.h
 *  Header file for t-SNE.
 *
 *  Created by Laurens van der Maaten.
 *  Copyright 2012, Delft University of Technology. All rights reserved.
 *
 *  Multicore version by Dmitry Ulyanov, 2016. dmitry.ulyanov.msu@gmail.com
 */


#ifndef TSNE_H
#define TSNE_H

#include <exception>

// - exception class 

static inline double sign(double x) { return (x == .0 ? .0 : (x < .0 ? -1.0 : 1.0)); }


class TSNEException : public std::exception
{
 public:
  TSNEException(const std::string &s)
    :_s(s) {}
  ~TSNEException() {}
  const char* what() const noexcept { return _s.c_str(); }
 private:
  std::string _s;
};

class TSNE
{
public:
    void run(double* X, int N, int D, double* Y, int no_dims, double perplexity, double theta, int num_threads, int max_iter);
    void symmetrizeMatrix(int** row_P, int** col_P, double** val_P, int N);
private:
    int num_threads;
    void computeGradient(int* inp_row_P, int* inp_col_P, double* inp_val_P, double* Y, int N, int D, double* dC, double theta);
    double evaluateError(int* row_P, int* col_P, double* val_P, double* Y, int N, double theta);
    void zeroMean(double* X, int N, int D);
    void computeGaussianPerplexity(double* X, int N, int D, int** _row_P, int** _col_P, double** _val_P, double perplexity, int K);
    double randn();
};

#endif

