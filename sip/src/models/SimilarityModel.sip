class SimilarityModel{
  %TypeHeaderCode
  #include "models/factor/FactorModel.h"
  %End
  public:
    SimilarityModel();
    virtual ~SimilarityModel();
    virtual double similarity(int item1, int item2)=0;
};
