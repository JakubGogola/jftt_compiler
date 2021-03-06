#pragma once

#include <string>
#include <vector>
#include <map>

#include "defs.hpp"

class data {
private:
    //Symbols table
    std::map<std::string, std::shared_ptr<symbol>> sym_map;

    //Error color message
    const std::string error_alert = "\x1b[31merror\x1b[0m: ";

    //Flag - true if errors occured
    bool errors;

    //Numbers of found errors
    int errors_num;

    //Current line
    int line;

    std::vector<std::shared_ptr<label>> labels;

    long long border_symbol;

public:
    //Memory offset
    long long mem_offset;
    std::vector<std::shared_ptr<variable>> variables;

    data();

    //Checks if variable exists
    bool check_context(std::string name);
    variable *init_variable(variable *var, std::string);

    void error_found();
    bool get_errors();
    int get_errors_num();
    void set_line(int line);
    std::string put_line();

    long long alloc_mem();
    long long alloc_mem_array(long long start, long long end);
    void free_mem();

    long long put_symbol(std::string name);
    long long put_symbol_array(std::string name, long long start, long long end);
    long long put_symbol_iterator(std::string name);
    void remove_iterator_symbol(std::string name);
    std::string put_border_symbol();
    long long put_value(long long value);
    symbol *get_symbol(std::string name);

    variable *get_variable(std::string name);
    variable *get_variable_array_var(std::string name, std::string var_name);
    variable *get_variable_array_num(std::string name, long long num);

    variable *get_value(variable *var, std::string name);
    variable *get_value_num(long long value);

    label *get_label(long long go_to, long long jump_false);
    for_label *get_for_label(std::string iterator_name, variable *start, variable *end);

    std::shared_ptr<variable> nop();
};