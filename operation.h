#ifndef OPERATION_H
#define OPERATION_H

#include <map>
#include <string>

/**
 * @brief Class to handle supported assembly operations and their operand count.
 */
class Operation
{
private:
    // Stores number of operands required for each operation
    std::map<std::string, int> numberOfOperands;

public:
    Operation();

    /**
     * @brief Returns the number of operands required for a given operation.
     * @param op Reference to the operation name (e.g., "MOV", "ADD").
     * @return Number of operands if supported, otherwise -1.
     */
    int getNumberOfOperands(std::string& op);
};

#endif // OPERATION_H
