#ifndef OBJECTIVE_LIST_RANK
#define OBJECTIVE_LIST_RANK

#include <vector>
#include "Objective.h"

using namespace std;

class ObjectiveListRank : public ObjectiveListWise{
  public:
    ObjectiveListRank(){};
    ~ObjectiveListRank(){};
    vector <double> get_gradient(vector <RecPred> * _predictions);
  private:
    void clear();
    void compute_norms();
    void compute_gradients();
    double sigmoid(double x) {
      return 1.0 / (1.0 + exp(-x));
    };
    double sigmoid_der(double x) {
      return sigmoid(x) * ( 1 - sigmoid(x));
    };
    double prediction_norm, score_norm;
    vector <RecPred> * predictions;
    vector <double> gradients, predictions_exp, scores_exp;
};
#endif
