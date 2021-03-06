//
// Created by ahmed on 12/11/17.
//

#include <fstream>
#include <iomanip>
#include "First.h"
#include "../parse_table/Parse_Table.h"

First::First(GRAMMAR grammar, set<string> terminals) {
    this->grammar = move(grammar);
    this->terminals = move(terminals);

    // Each terminal is first of itself
    for (const string &terminal: this->terminals)
        this->first[terminal].insert(terminal);

    for (pair<const string, vector<vector<string> > > &rule: this->grammar)
        if (this->first.find(rule.first) == this->first.end())
            __generate(rule.first);
}

FIRST_FOLLOW First::get() {
    return this->first;
}

void First::log(ofstream *log_file) {
    *log_file << "\n\nFirst:\n";
    for (pair<string, set<string>> entry: this->first) {
        *log_file << "    " << setw(20) << entry.first << "  ➜  ";
        for (const string &str: entry.second) {
            if (entry.second.find(str) != entry.second.begin()) *log_file << "  ,  ";
            *log_file << str;
        }
        *log_file << endl;
    }
}

set<string> First::__generate(const string &non_terminal) {
    if (this->first.find(non_terminal) != this->first.end())
        return this->first[non_terminal];

    set<string> non_term_first;
    for (vector<string> &prod_rule: this->grammar[non_terminal]) {
        if (this->terminals.count(prod_rule[0])) { // if is terminal
            non_term_first.insert(prod_rule[0]);
        } else if (prod_rule[0] != non_terminal) { // if it's non-terminal
            int i = -1;
            set<string> prod_rule_first;

            while (++i < prod_rule.size()) {
                prod_rule_first.clear();

                if (this->terminals.count(prod_rule[i])) // if is terminal
                    prod_rule_first.insert(prod_rule[i]);
                else
                    prod_rule_first = __generate(prod_rule[i]);

                non_term_first.insert(prod_rule_first.begin(), prod_rule_first.end());

                if (prod_rule_first.find(EPS) == prod_rule_first.end())
                    break;
            }
        }
    }

    this->first[non_terminal] = non_term_first;
    return non_term_first;
}
