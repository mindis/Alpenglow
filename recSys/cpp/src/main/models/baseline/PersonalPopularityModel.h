#ifndef PERSONAL_POPULARITY_MODEL
#define PERSONAL_POPULARITY_MODEL

#include <vector>
#include <map>
#include "../Model.h"
#include "../../utils/PopContainers.h"
#include "../../recommender_data/RecommenderData.h"
#include <gtest/gtest_prod.h>

using namespace std;

class PersonalPopularityModel : public Model{
  public:
    void add(RecDat* rec_dat) override;
    double prediction(RecDat* rec_dat) override;
  private:
    double get_user_highest_personal_pop_item_score(int user);
    SpMatrix personal_popularities_;
    PopContainer global_popularities_;
    map<int, int> user_personal_pop_items_;

    friend class PersonalPopularityModelUpdater;
    FRIEND_TEST(TestPersonalPopularityModel, update);
};

#endif
