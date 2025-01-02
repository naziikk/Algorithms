#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

std::unordered_set<char> forbidden = {'(', ')', '-', '+', ' '};

std::string strip(const std::string& number) {
    std::string reformatted_number;
    for (const auto& symbol : number) {
        if (forbidden.find(symbol) == forbidden.end()) {
            reformatted_number += symbol;
        }
    }
    return reformatted_number;
}

std::vector<std::string> parseTemplateNumber(const std::string& template_number) {
    std::vector<std::string> parsed_template_number;
    auto idx = template_number.rfind('-');
    std::string number = template_number.substr(0, idx);
    parsed_template_number.push_back(strip(number));
    parsed_template_number.push_back(template_number.substr(idx + 1));
    parsed_template_number.push_back(number);
    return parsed_template_number;
}

std::string reformatNumber(const std::string& hidden_numbered, const std::string& matching_number,
                           const std::string& template_suffix) {
    auto first_brace_idx = hidden_numbered.find('(');
    auto second_brace_idx = hidden_numbered.find(')');
    std::string reformatted = '+' + matching_number.substr(0, first_brace_idx - 2) + ' ' + '(' +
                              matching_number.substr(first_brace_idx - 2, second_brace_idx - first_brace_idx - 1) + ')' +
                              ' ' + matching_number.substr(second_brace_idx - 3) + " -" + template_suffix + '\n';
    return reformatted;
}

struct Number {
    std::string number;
    std::unordered_set<std::string> prefixes;
    int idx;
    bool found;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Number> telephone_numbers(n);
    for (int i = 0; i < n; i++) {
        std::string number;
        std::getline(std::cin >> std::ws, number);
        std::string stripped_number = strip(number);
        telephone_numbers[i].number = stripped_number;
        telephone_numbers[i].idx = i;
        std::string prefix;
        for (const auto& symbol : stripped_number) {
            prefix += symbol;
            telephone_numbers[i].prefixes.insert(prefix);
        }
    }
    int m;
    std::cin >> m;
    std::vector<std::string> result_matching(n);
    for (int i = 0; i < m; i++) {
        std::string template_number;
        std::getline(std::cin >> std::ws, template_number);
        std::vector<std::string> parsed_template_number = parseTemplateNumber(template_number);
        std::string template_prefix = parsed_template_number[0];
        std::string template_suffix = parsed_template_number[1];
        std::string hidden_number = parsed_template_number[2];
        auto idx = template_prefix.find('X');
        std::string cut_template_prefix = template_prefix;
        if (idx != std::string::npos) {
            cut_template_prefix = template_prefix.substr(0, idx);
        }
        for (const auto& telephone_number : telephone_numbers) {
            if (!telephone_numbers[telephone_number.idx].found && telephone_number.prefixes.find(cut_template_prefix) != telephone_number.prefixes.end()
                && telephone_numbers[telephone_number.idx].number.size() == template_prefix.size()) {
                result_matching[telephone_number.idx] = reformatNumber(hidden_number, telephone_number.number, template_suffix);
                telephone_numbers[telephone_number.idx].found = true;
            }
        }
    }
    for (const auto& matching : result_matching) {
        std::cout << matching;
    }
    return 0;
}