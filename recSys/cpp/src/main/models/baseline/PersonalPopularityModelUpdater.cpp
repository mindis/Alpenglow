#include "PersonalPopularityModelUpdater.h"

void PersonalPopularityModelUpdater::update(RecDat* rec_dat){
  model_->global_popularities_.increase(rec_dat->item);
  double current_personal_pop = model_->personal_popularities_.get(rec_dat->user, rec_dat->item) + rec_dat->score;
  model_->personal_popularities_.update(rec_dat->user, rec_dat->item, current_personal_pop);
  double highest_personal_pop = model_->get_user_highest_personal_pop_item_score(rec_dat->user);
  if(current_personal_pop > highest_personal_pop){
    model_->user_personal_pop_items_[rec_dat->user] = rec_dat->item;
  }
}
