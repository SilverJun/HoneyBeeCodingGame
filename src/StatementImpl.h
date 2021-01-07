#pragma once

#include "Token.h"
#include "Expression.h"
#include "Statement.h"
#include "Error.h"

namespace script
{

class CIfStatement : public CStatement
{
public:
	CIfStatement(TokenIter &it);
	virtual void Execute(SymbolTable &context);

private:
	CExpression::ExprPtr m_expression;			//if m_expression
	StatementPtr ifStatement;					//{m_statement}
	StatementPtr elseStatement;					//{m_statement}
};

class CWhileStatement : public CStatement
{
public:
	CWhileStatement(TokenIter &it);
	virtual void Execute(SymbolTable &context);

private:
	CExpression::ExprPtr m_expression;				//while m_expression
	StatementPtr m_statement;						//{m_statement}
};

class CForStatement : public CStatement
{
public:
	CForStatement(TokenIter &it);
	virtual void Execute(SymbolTable &context);

private:
	StatementPtr m_init;
	CExpression::ExprPtr m_condition;
	StatementPtr m_increment;
	StatementPtr m_statement;						//{m_statement}
};

class COutputStatement : public CStatement
{
public:
	COutputStatement(TokenIter &it);
	virtual void Execute(SymbolTable &context);

private:
	CExpression::ExprPtr m_expression;				//output m_expression
};

class CInputStatement : public CStatement
{
public:
	CInputStatement(TokenIter &it);
	virtual void Execute(SymbolTable &context);

private:
	std::string m_variable;
	int m_data;						//Ű���忡�� ���� int�� ����Ÿ�� ������ ����
};

class CCompoundStatement : public CStatement
{
public:
	CCompoundStatement(TokenIter &it);
	virtual void Execute(SymbolTable &context);

private:
	StatementList m_statements;					//{m_statement}
};

class CVarStatement : public CStatement
{
public:
	CVarStatement(TokenIter &it);
	virtual void Execute(SymbolTable &context);
private:
	bool m_bAssign;				//���������� �ٷ� �ʱ�ȭ ������ �ִ��� ������
	std::string m_variable;				//int m_variable
	CExpression::ExprPtr m_expression;		//int m_variable = m_expression
};

class CStringStatement : public CStatement
{
public:
	CStringStatement(TokenIter &it);
	virtual void Execute(SymbolTable &context);
private:
	bool m_bAssign;				//���������� �ٷ� �ʱ�ȭ ������ �ִ��� ������
	std::string m_variable;				//string m_variable
	CExpression::ExprPtr m_expression;		//string m_variable = m_expression
};

class CAssignmentStatement : public CStatement
{
public:
	CAssignmentStatement(TokenIter &it);
	virtual void Execute(SymbolTable &context);
private:
	std::string m_variable;				//m_variable = m_expression
	CExpression::ExprPtr m_expression;
};

class CFunctionCallStatement : public CStatement
{
public:
	CFunctionCallStatement(TokenIter &it)
	{
		Expect(TokenID::Func_Call, *it);

		if (it->_name == "Go")
		{
			_action = PlayerAction::Go;
		}
		else if (it->_name == "TurnLeft")
		{
			_action = PlayerAction::TurnLeft;
		}
		else if (it->_name == "TurnRight")
		{
			_action = PlayerAction::TurnRight;
		}
		else
		{
			throw Error("can't parse this function call" + it->_name);
		}
		++it;
		it->Expect(TokenID::OpenSmall);
		++it;

		m_expression = CExpression::Parse(it);
		Expect(TokenID::CloseSmall, *it++);
	}

	void Execute(SymbolTable &context) override
	{
		int count = m_expression->Evaluate(context);
		for (int i = 0; i < count; ++i)
		{
			context.AddAction(_action);
		}
	}

private:
	CExpression::ExprPtr m_expression;
	PlayerAction _action;
};

}
