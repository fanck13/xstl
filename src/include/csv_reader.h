#pragma once

#include "common.h"

#include <vector>
#include <string>
#include <fstream>
#include <cassert>

XSTL_NAMESPACE_BEGIN

using Content = std::vector<std::vector<std::string>>;

class csv_reader
{
public:
    csv_reader() = default;

    ~csv_reader() = default;

    bool load(const std::string& path)
    {
        std::ifstream fin;
        fin.open(path, std::ifstream::in);
        if(!fin.good()) return false;

        while (!fin.eof())
        {
            std::string line;
            std::getline(fin, line);
            auto index = std::string::npos;
            size_t start = 0;
            std::vector<size_t> indices;
            indices.push_back(0);
            do
            {
                index = line.find(',', start);
                if (index >= 2 && index < line.size() - 1 && line[index - 1] == '\"' && line[index + 1] == '\"')
                {
                    continue;
                }

                start = index + 1;
                indices.push_back(index);
            } while (index != std::string::npos);

            indices.push_back(line.size());

            std::vector<std::string> row;

            for (size_t i = 1; i < indices.size(); i++)
            {
                if (indices[i] - indices[i - 1] <= 1)
                {
                    row.push_back("");
                }
                else
                {
                    row.push_back(line.substr(indices[i - 1] + 1, indices[i]));
                }
            }
        }
        fin.close();
        return true;
    }

    const std::string& cell_content_at(size_t row, size_t column) const
    {
        assert(content.size() >0 && row< content.size()  && column < content[0].size());
        return content[row][column];
    }

    const std::string& operator()(size_t row, size_t column) const
    {
        return cell_content_at(row, column);
    }

private:
    Content content;
};

XSTL_NAMESPACE_END
