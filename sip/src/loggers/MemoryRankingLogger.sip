struct RankingLog{
  %TypeHeaderCode
  #include "cpp/MemoryRankingLogger.h"
  %End
  double time;
  int id;
  int rank;
  int user;
  int item;
  double score;
  double prediction;
};

struct RankingLogs{
  %TypeHeaderCode
  #include "cpp/MemoryRankingLogger.h"
  %End
  int top_k;
  std::vector<RankingLog> logs;
};

struct MemoryRankingLoggerParameters{
  %TypeHeaderCode
  #include "cpp/MemoryRankingLogger.h"
  %End
  double min_time;
  std::string out_file;
};

class MemoryRankingLogger : public Logger /NoDefaultCtors/{
  %TypeHeaderCode
  #include "cpp/MemoryRankingLogger.h"
  %End
  public:
    MemoryRankingLogger(MemoryRankingLoggerParameters* params);
    ~MemoryRankingLogger();
    void set_model(Model* model);
    void set_rank_computer(RankComputer* rank_computer);
    void set_ranking_logs(RankingLogs* logs);
    void run(RecDat* rec_dat);
};
