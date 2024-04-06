#include <filesystem>
#include <string>

#include "cmdline.h"
#include "stlog/stlog.h"
#include "toml++/toml.h"

#include "pts/utils.hpp"

namespace pts {
class ConfigManager {
  public:
    static ConfigManager& GetInstance() {
        static ConfigManager instance;
        return instance;
    }

    void Init(int argc, char** argv);

    int32_t GetDate() const { return GetInstance().date_; }
    const toml::table& GetConfig() const { return GetInstance().config_; }

  private:
    ConfigManager();
    ~ConfigManager();
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    void InitCmdArgs(int argc, char** argv);
    void InitConfig(const std::string& config_path);
    void InitLogger(const std::filesystem::path& log_path, const std::string& app_name, const std::string& log_level);
    void InitErrorXml();

    std::string config_path_;
    std::filesystem::path log_path_;
    std::string app_name_;
    std::string log_level_;
    int32_t date_;
    toml::table config_;
    bool initialized_;  // 用于确保 Init 只被调用一次
};

inline ConfigManager::ConfigManager() : initialized_(false) {}

inline ConfigManager::~ConfigManager() {}

inline void ConfigManager::Init(int argc, char** argv) {
    if (initialized_) {
        return;  // Init 已经被调用过了，直接返回
    }
    initialized_ = true;

    InitCmdArgs(argc, argv);
    InitConfig(config_path_);
    InitLogger(log_path_, app_name_, log_level_);
}

inline void ConfigManager::InitCmdArgs(int argc, char** argv) {
    cmdline::parser parser;
    parser.add<std::string>("config", 'c', "config path", true, "./config/config.toml");
    parser.parse_check(argc, argv);
    config_path_ = parser.get<std::string>("config");
}

inline void ConfigManager::InitConfig(const std::string& config_path) {
    try {
        LOG_INFO("Parsing config: {}", std::filesystem::absolute(config_path).string());
        config_ = toml::parse_file(config_path);
    } catch (const toml::parse_error& e) {
        LOG_ERROR("parse config file failed: {}", e.what());
        throw;
    }

    date_ = config_["date"].value_or(DateUtils::GetCurrentDate());
    std::string log_path = config_["log"]["path"].value_or(std::string("."));
    log_path_ = std::filesystem::absolute(log_path);
    app_name_ = config_["log"]["name"].value_or("pts");
    log_level_ = config_["log"]["level"].value_or("INFO");

    LOG_INFO("Date: {}", date_);
}

inline void ConfigManager::InitLogger(const std::filesystem::path& log_path, const std::string& app_name,
                                      const std::string& log_level) {
    st::log::Logger::Init(log_path, app_name, log_level, date_);
}
}  // namespace pts