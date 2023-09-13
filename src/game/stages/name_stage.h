#include "stage.h"

class NameStage : public Stage {
public:
    bool validateStage();
    std::map<std::string, std::vector<std::string>> getStageErrors();
    void updateStage(std::string args);
    std::string getStageName();
private:
    std::string first_name;
    std::string last_name;
};