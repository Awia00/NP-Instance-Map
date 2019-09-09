#pragma once
#include <filesystem>
#include <vector>
#include <fstream>
#include <map>
#include <memory>
#include <np_solver/solution.hpp>

namespace npim
{
class DatasetRepository
{
    const std::experimental::filesystem::path dataset_path;

    public:
    DatasetRepository(const std::experimental::filesystem::path& path) : dataset_path(path)
    {
    }

    void save_dataset(const std::map<uint64_t, std::vector<std::unique_ptr<InstanceSolution>>>& result) const
    {
        std::ofstream file;
        file.open(dataset_path);

		// headers
        file << "graph";
        for (const auto& res : result.at(0))
        {
            file << ", " << res->header_string();
		}
        file << std::endl;

		// content
        for (const auto& pair : result)
        {
            auto& g = pair.first;
            auto& results = pair.second;
            file << g;
            for (const auto& res : results)
            {
                file << ", " << res->to_string();
			}
            file << std::endl;
		}

        file.close();
    }
};
} // namespace npim