#include "./translated/checkFile.h"
#include "./translated/checkDirectory.h"
#include "./translated/createFile.h"
#include "./translated/createDirectory.h"

#include <vector>
#include <string>

const std::vector<std::string> RequiredDirectories { "natureos", "natureos/bin", "natureos/system", "natureos/system/config", "natureos/system/cache", "natureos/local" };
const std::vector<std::string> RequiredUserDirectories { "natureos/home" };
const std::vector<std::string> OptionalDirectories { "natureos/cache", "natureos/fscache" };