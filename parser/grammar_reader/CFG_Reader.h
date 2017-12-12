//
// Created by ahmed on 12/5/17.
//

#ifndef PARSER_GENERATOR_INPUT_READER_H
#define PARSER_GENERATOR_INPUT_READER_H


#include <set>
#include <map>
#include <vector>
#include <fstream>

#define EPS         "\\EPSILON\\"
#define GRAMMAR map<string, vector<vector<string> > >

using namespace std;

// Context Free Grammar Reader
class CFG_Reader {
public:
    explicit CFG_Reader(string file_path);

    GRAMMAR get_grammar();

    set<string> get_terminals();

    string get_start_symbol();

    void log(ofstream *log_file);

private:
    string file_path;
    string start_symbol;
    GRAMMAR grammar;
    set<string> terminals;

    void __read(string file_path);
};


#endif //PARSER_GENERATOR_INPUT_READER_H