#pragma once

#include "Expression.h"

namespace script
{
	class CMultExp : public CExpression			//����ó��
	{
	public:
		static CExpression::ExprPtr Parse(TokenIter &it);
		int Evaluate(SymbolTable &context) override;
	private:
		Exprs m_exprs;			//ǥ���ĵ�
		std::list<TokenID> m_ops;		//������, *, /, %�� �� Ŭ�������� �ѹ��� ó���Ѵ�.
	};

	class CAddExp : public CExpression			//����ó��
	{
	public:
		static CExpression::ExprPtr Parse(TokenIter &it);
		int Evaluate(SymbolTable &context) override;
	private:
		Exprs m_exprs;			//ǥ���ĵ�
		std::list<bool> m_ops;			//�� : ����, ���� : ����
	};

	class CComparisonExp : public CExpression		//�񱳿���ó��
	{
	public:
		CComparisonExp(CExpression::ExprPtr lhs, CExpression::ExprPtr rhs, TokenID tok);
		static CExpression::ExprPtr Parse(TokenIter &it);
		int Evaluate(SymbolTable &context) override;
	private:
		CExpression::ExprPtr m_lhs;			//����
		CExpression::ExprPtr m_rhs;			//����
		TokenID m_tok;			//�񱳿�����
		int result;
	};

	class CAtom : public CExpression			//���׿����� ó��
	{
	public:
		static CExpression::ExprPtr Parse(TokenIter &it);
	};

	class CNumber : public CAtom			//�Ϲ� ����
	{
	public:
		CNumber(int number) : m_number(number) {}
		int Evaluate(SymbolTable &context) { return m_number; }
	private:
		int m_number;
	};

	class CNot : public CAtom				//������ not
	{
	public:
		CNot(CExpression::ExprPtr expr) : m_expr(expr) {}
		int Evaluate(SymbolTable &context) { return !m_expr->Evaluate(context); }
	private:
		CExpression::ExprPtr m_expr;
	};

	class CIdentifier : public CAtom			//����ȣ��
	{
	public:
		CIdentifier(std::string identifier) : m_identifier(identifier) {}
		int Evaluate(SymbolTable &context) { return context.GetValue(m_identifier); }
	private:
		std::string m_identifier;
	};

	class CCompoundAtom : public CAtom			//��ȣó��
	{
	public:
		CCompoundAtom(CExpression::ExprPtr expr) : m_CExpression(expr) {}
		int Evaluate(SymbolTable &context) { return m_CExpression->Evaluate(context); }
	private:
		CExpression::ExprPtr m_CExpression;
	};
}