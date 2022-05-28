#include <QCoreApplication>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
using Matrix = std::vector<std::vector<int>>;
using uint = unsigned int;
class Solution
{
public:
    Matrix& Rotate(Matrix& matrix)
    {
        if(matrix.empty())
            return matrix;
        print(matrix, "Before rotate");
        const uint size = matrix.at(0).size();
        //left-up to right-down
        for (uint i = 0; i < size; i++)
        {
            for (uint j = 0; j < i; j++)
                std::swap(matrix[i][j], matrix[j][i]);
        }
        //Central line
        for (uint i = 0; i < size; i++)
        {
            for (uint j = 0, k = size - 1; j < k; j++, k--)
                std::swap(matrix[i][j], matrix[i][k]);
        }

        return matrix;
    }

    bool testMatrix(Matrix& matrix)
    {
        uint i = 0;
        Matrix ans_matrix = { {13, 9, 5, 1,},
                             {14, 10, 6, 2},
                             {15, 11, 7, 3},
                             {16, 12, 8, 4}};

        for(const auto& row : ans_matrix)
        {
            const auto& result_row = matrix.at(i);
            if (!std::equal(row.begin(), row.end(), result_row.begin()))
            {
                print(matrix, "After rotate");
                print(ans_matrix, "Answer of matrix");
                return false;
            }
            i++;
        }
        return true;
    }

    void print(const Matrix& matrix, const std::string& message)
    {
        std::cout << message << "\n";
        for(const auto& row : matrix)
        {
            for(const auto& col : row)
            {
                std::cout << col << ", ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
};


TEST(Matrix, matrix)
{
    Matrix matrix = { {1, 2, 3, 4,},
                     {5, 6, 7, 8},
                     {9, 10, 11, 12},
                     {13, 14, 15, 16}};
    Solution s;
    auto& result_matrix = s.Rotate(matrix);
    ASSERT_TRUE(s.testMatrix(result_matrix));
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    QCoreApplication a(argc, argv);

    return (!RUN_ALL_TESTS() && a.exec());
}
