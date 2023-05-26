#include<bits/stdc++.h>
using namespace std;

struct Statement {
    string expression;
    unordered_set<string> variables;
};

struct AnalysisResult {
    unordered_set<string> availableExpressions;
    unordered_set<string> liveVariables;
};

vector<Statement> parseProgram(const vector<string>& program) {
    vector<Statement> statements;
    
    for (const auto& line : program) {
        size_t pos = line.find('=');
        if (pos != string::npos) {
            string expression = line.substr(pos + 1);
            string variablesStr = line.substr(0, pos);
            
            Statement statement;
            statement.expression = expression;
            
            size_t startPos = 0;
            while (startPos < variablesStr.length()) {
                size_t endPos = variablesStr.find(' ', startPos);
                string variable = variablesStr.substr(startPos, endPos - startPos);
                statement.variables.insert(variable);
                startPos = endPos + 1;
            }
            
            statements.push_back(statement);
        }
    }
    
    return statements;
}

AnalysisResult performAnalysis(const vector<Statement>& statements) {
    unordered_map<string, unordered_set<string>> expressionDependencies;
    unordered_set<string> availableExpressions;
    unordered_set<string> liveVariables;
    
    for (const auto& statement : statements) {
        for (const auto& variable : statement.variables) {
            expressionDependencies[variable].insert(statement.expression);
        }
    }
    
    for (const auto& statement : statements) {
        bool isExpressionAvailable = true;
        
        for (const auto& variable : statement.variables) {
            if (expressionDependencies[variable].size() > 1) {
                isExpressionAvailable = false;
                break;
            }
        }
        
        if (isExpressionAvailable) {
            availableExpressions.insert(statement.expression);
        }
        
        for (const auto& variable : statement.variables) {
            if (availableExpressions.count(statement.expression) == 0) {
                liveVariables.insert(variable);
            }
        }
    }
    
    return { availableExpressions, liveVariables };
}

int main() {
    // Example program
    vector<string> program = {
        "x = a + b",
        "y = c * x",
        "z = y + d",
        "x = b - c",
        "d = z / y"
    };
    
    // Parse the program
    vector<Statement> statements = parseProgram(program);
    
    // it performing  analysis
    AnalysisResult result = performAnalysis(statements);
    
    // it printing the results
    cout << "Available Expressions: ";
    for (const auto& expression : result.availableExpressions) {
        cout << expression << " ";
    }
    cout << endl;
    
    cout << "Live Variables: ";
    for (const auto& variable : result.liveVariables) {
        cout << variable << " ";
    }
    cout << endl;
    
    return 0;
}
