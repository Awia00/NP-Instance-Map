#pragma once
#include <filesystem>
#include <vector>

namespace npim
{
class DatasetRepository
{
    const std::filesystem::path dataset_path;

    public:
    DatasetRepository(const std::filesystem::path& path) : dataset_path(path)
    {
    }

    template <typename SolutionType>
    void save_dataset(const std::vector<SolutionType>& solution)
    {
    }
};
} // namespace npim