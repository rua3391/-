#include <iostream>
#include <string>
#include <unordered_map>

// 解释器模式
// 意图: 给定一个语言，定义它的一种语法表示 
// 如果一种特定类型的问题发生的频率足够高，那么可能就值得将该问题的各个实例表述为一个简单语言中的句子，这样就可以构建一个解释器，该解释器通过解释这些句子来解决该问题
// AbstractExpression：声明一个抽象的解释操作。
// TerminalExpression：实现与文法中的元素相关联的解释操作，对非终结符实现解释操作
// NonterminalExpression：文法中的每条规则对应于一个非终结表达式，非终结符表达式根据逻辑的复杂程度而增加，原则上每个文法规则都对应一个非终结符表达式
// Context: 上下文环境类,包含解释器之外的全局信息
// Client: 客户端,解析表达式,构建抽象语法树,执行具体的解释操作等.

class context
{
    public:
        context( const std::string &s) : str(s)
        {
        }
        bool find( std::string &s)
        {
            return str.find(s) != std::string::npos;
        }
    private:
        std::string str;
};

class Expression
{
    public:
        virtual bool interpret( context &con) = 0;
};

class TerminalExpression : public Expression
{
    public:
        TerminalExpression(std::string s) : _p(s)
        {
        }
        virtual bool interpret( context &con)
        {
            return con.find(_p);
        }
    private:
        std::string _p;
};

class NonterminalExpression : public Expression
{
    public:
        Expression &e1, &e2;
        NonterminalExpression( Expression &ex1,  Expression &ex2) : e1(ex1), e2(ex2){}
        virtual bool interpret( context &con) = 0;
};

class AndExpression : public NonterminalExpression
{
    public:
        AndExpression( Expression &ex1,  Expression &ex2) : NonterminalExpression(ex1, ex2){}
        virtual bool interpret( context &con) final
        {
            return this->e1.interpret(con) && this->e2.interpret(con);
        }
};

class OrExpression : public NonterminalExpression
{
    public:
        OrExpression(Expression &ex1, Expression &ex2) : NonterminalExpression(ex1, ex2){}
        virtual bool interpret( context &con) final
        {
            return this->e1.interpret(con) || this->e2.interpret(con);
        }
};

class calculator
{
    public:
        calculator() = default;
        double get(char c){
            return variable[c];
        }
        void insert(std::pair<char, double> ss)
        {
            variable.insert(ss);
        }
        std::unordered_map<char, double> variable;
};

class elem
{
    public:
        virtual double interpret(calculator &cal) = 0;
};

class VariableExpression : public elem
{
    public:
        VariableExpression(char c) : _c(c) {
        }
        virtual double interpret(calculator &cal){
            return cal.get(_c);
        }
    private:
        char _c;
};

class operation : public elem
{
    public:
        operation(elem &e1, elem &e2): _e1(e1), _e2(e2){}
        virtual double interpret(calculator &cal) = 0;
    protected:
        elem &_e1, &_e2;
};

class oneoperation : public elem
{
    public:
        oneoperation(elem &e1) : _e1(e1){}
        virtual double interpret(calculator &cal) = 0;
    protected:
        elem &_e1;
};

class subExpression : public operation
{
    public:
        subExpression(elem &ex1, elem &ex2) : operation(ex1, ex2){}
        virtual double interpret(calculator &con) final
        {
            return this->_e1.interpret(con) - this->_e2.interpret(con);
        }
};

class AddExpression : public operation
{
    public:
        AddExpression(elem &ex1, elem &ex2) : operation(ex1, ex2){}
        virtual double interpret( calculator &con) final
        {
            return this->_e1.interpret(con) + this->_e2.interpret(con);
        }
};

class RevertExpression : public oneoperation
{
    public:
        RevertExpression(elem &ex1) : oneoperation(ex1){}
        virtual double interpret(calculator &con) final
        {
            return -this->_e1.interpret(con);
        }
};

int main()
{
    context co("tom jerry");
    Expression *ex1 = new TerminalExpression("jerry");
    Expression *ex2 = new TerminalExpression("jack");
    Expression *orexp = new OrExpression(*ex1, *ex2);
    Expression *andexp = new AndExpression(*ex1, *ex2);
    std::cout << (orexp->interpret(co) ? "True" : "false") << std::endl;
    std::cout << (andexp->interpret(co) ? "True" : "false") << std::endl;
    
    calculator cal;
    elem *x1 = new VariableExpression('a');
    elem *x2 = new VariableExpression('b');
    elem *x3 = new AddExpression(*x1, *x2);
    cal.insert({'a', 2});
    cal.insert({'b', 3});   
    elem *x4 = new RevertExpression(*x3);
    std::cout << x4->interpret(cal) << std::endl;
    return 0;
}