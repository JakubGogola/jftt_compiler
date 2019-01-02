#pragma once

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>

#include "defs.hpp"
#include "data.hpp"

class code_generator {
private:
    //Data object (symbols table and memory)
    std::shared_ptr<data> d;

    //Flag - true if sth is read from stdin
    bool is_read;

    //Flag - true if sth is wrtite to stdout
    bool is_write;

    //Code offset
    long long code_offset;

    //Next free label
    long long next_label;

    //Genearted code
    std::vector<std::string> code;

    //Cost of some instructions
    std::map<enum instr, int> costs;

    //Std::string symbols of registers
    std::map<enum reg, std::string> reg_sym;

    /*FUNCTIONS*/

    //Generate costs map
    void gen_costs();
    void gen_reg_sym();

    long long get_label();
    void incr_offset(long long incr);

    void set_mem_reg(variable *var);
    void single_var(variable *var, enum reg r);

    void change_operation(long long index, std::string operation);
    std::string get_operation(long long index);

public:
    code_generator(std::shared_ptr<data> d);

    std::vector<std::string> get_code();
    void array_offset(long long addr, long long offset);

    void end_prog();

    long long get_code_offset();

    void mem_to_reg(variable *var, enum reg r);
    void reg_to_mem(enum reg r, variable *var);

    std::vector<std::string> gen_const(long long c, enum reg r); 

    //operations
    void assign(variable *var);
    void constant(variable *var);

    void add(variable *v_1, variable *v_2);
    void sub(variable *v_1, variable *v_2);
    void mul(variable *v_1, variable *v_2);
    void div(variable *v_1, variable *v_2);
    void mod(variable *v_1, variable *v_2);
    
    //conditions
    long long eq(variable *v_1, variable *v_2);
    long long neq(variable *v_1, variable *v_2);
    long long gt(variable *v_1, variable *v_2);
    long long lt(variable *v_1, variable *v_2);
    long long geq(variable *v_1, variable *v_2);
    long long leq(variable *v_1, variable *v_2);

    //IF, IF_ELSE blocks
    void if_block(long long go_to);
    void if_else_block(long long jump_addr);

    //WHILE, DO_WHILE loops

    //FOR_TO, FOR_DOWNTO loops

    //IO
    void write(variable *var);
    void read(variable *var);

    void read_interact();
    void write_interact();
};