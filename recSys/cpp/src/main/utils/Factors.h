#ifndef FACTORS
#define FACTORS

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <gtest/gtest_prod.h>

using namespace std;

struct FactorsParameters{
  double begin_max;
  double begin_min;
  double dimension;
};

class Factors{
  public:
    Factors(){};
    Factors(FactorsParameters parameters){
      set_parameters(parameters);
    };
    ~Factors(){
      for(uint i=0;i<factors.size();i++){
        if(factors[i]!=NULL){
          delete factors[i];
          factors[i]=NULL;
        }
      } 
    }
    void set_parameters(FactorsParameters parameters);
    void init(int idx);
    void init_zero(int idx);
    void init_rand(int idx);
    vector<double>* get(int idx); 
    void set(int idx, vector<double>* value);
    void set_zero(int idx); 
    void set_rand(int idx); 
    void set(int idx, int dim, double val); 
    void all_to_zero();
    void add(int idx, vector<double>* value);
    void add(int idx, vector<double>* value, double coef);
    void add(int idx, int dim, double val);
    //void print(int idx);
    inline void lin_combine(int idx, double weight, vector<double>* other);
    //inline void lin_combine(int idx, double weight, double val);
    //inline void lin_combine(int idx, double weight);
    void resize(int idx);
    int get_size();
    void write(ofstream& file);
    void read(ifstream& file);
    void clear();
    size_t get_dimension(){return dimension;}
    vector <int> get_nonnull_indices();
  private:
    vector <vector<double>*> factors;
    double begin_min, begin_max;
    int dimension;
};

void Factors::lin_combine(int idx, double weight, vector<double>* other){
  if(other->size() == (uint) dimension){
    for(int ii=0; ii<dimension; ii++){
      (*factors[idx])[ii] += weight*(*other)[ii];
    }
  }
}

//void Factors::lin_combine(int idx, double weight){
//  for(int ii=0; ii<dimension; ii++){
//    //(*factors[idx])[ii]=(*factors[idx])[ii]+weight*val;
//    (*factors[idx])[ii] += weight;
//  }
//}

#endif
