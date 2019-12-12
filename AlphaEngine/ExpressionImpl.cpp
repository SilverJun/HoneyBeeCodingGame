#include "ExpressionImpl.h"
#include "Error.h"

namespace script
{
	// ComparisonExp

	CComparisonExp::CComparisonExp(ExprPtr lhs, ExprPtr rhs, TokenID tok)
		: m_lhs(lhs)
		, m_rhs(rhs)
		, m_tok(tok)
	{}

	CExpression::ExprPtr CComparisonExp::Parse(TokenIter &it)
	{
		ExprPtr lhs, rhs;

		lhs = CAddExp::Parse(it);

		TokenID tok = it->_id;
		if (tok == TokenID::Relational_Equal || tok == TokenID::Relational_Less || tok == TokenID::Relational_LessEqual || tok == TokenID::Relational_GreaterEqual || tok == TokenID::Relational_Greater || tok == TokenID::Relational_NotEqual)
		{
			it++;
			rhs = CAddExp::Parse(it);
		}
		//������ ������ ���� �ۿ� �����Ƿ� ���� ����, ������ ������ �ٽ� ���� �˻�.
		return rhs.get() == NULL ? ExprPtr(lhs) : ExprPtr(new CComparisonExp(lhs, rhs, tok));
	}

	int CComparisonExp::Evaluate(SymbolTable &context)
	{
		switch (m_tok)
		{
		case TokenID::Relational_Equal:
			result = m_lhs->Evaluate(context) == m_rhs->Evaluate(context);
			break;
		case TokenID::Relational_Less:
			result = (m_lhs->Evaluate(context) < m_rhs->Evaluate(context));
			break;
		case TokenID::Relational_Greater:
			result = (m_lhs->Evaluate(context) > m_rhs->Evaluate(context));
			break;
		case TokenID::Relational_LessEqual:
			result = (m_lhs->Evaluate(context) <= m_rhs->Evaluate(context));
			break;
		case TokenID::Relational_GreaterEqual:
			result = (m_lhs->Evaluate(context) >= m_rhs->Evaluate(context));
			break;
		case TokenID::Relational_NotEqual:
			result = (m_lhs->Evaluate(context) != m_rhs->Evaluate(context));
			break;
		default:
			throw Error(std::string("Unexpected Comparison Token"));
		}
		return result;
	}

	// AddExp

	CExpression::ExprPtr CAddExp::Parse(TokenIter &it)
	{
		CAddExp *addExp = new CAddExp;
		addExp->m_exprs.push_back(CMultExp::Parse(it));		//���� �Ľ�Ʈ�� �ۼ�

		while (it->_id == TokenID::Arithmetic_Add || it->_id == TokenID::Arithmetic_Subtract)		//��ū�� +, -�϶� �ݺ��� ����.
		{
			bool bAdd = it->_id == TokenID::Arithmetic_Add;			//�� : +, ���� : -
			addExp->m_ops.push_back(bAdd);
			it++;
			addExp->m_exprs.push_back(CMultExp::Parse(it));			//�����߿����� ������ �ü� �����Ƿ� �ٽ� �Ľ�Ʈ�� �ۼ�
		}
		return addExp->m_exprs.size() == 1 ? *(addExp->m_exprs.begin()) : ExprPtr(addExp);
	}

	int CAddExp::Evaluate(SymbolTable &context)
	{
		Exprs::iterator it = m_exprs.begin();

		int result = it->get()->Evaluate(context);

		for (std::list<bool>::iterator opIt = m_ops.begin(); opIt != m_ops.end(); opIt++)
		{
			it++;
			if (*opIt)
				result += it->get()->Evaluate(context);
			else
				result -= it->get()->Evaluate(context);
		}
		return result;
	}


	// MultExp

	CExpression::ExprPtr CMultExp::Parse(TokenIter &it)
	{
		CMultExp *multExp = new CMultExp;
		multExp->m_exprs.push_back(CAtom::Parse(it));			//���� ���� �Ľ�Ʈ�� �ۼ�(����)

		while (it->_id == TokenID::Arithmetic_Multiply || it->_id == TokenID::Arithmetic_Divide || it->_id == TokenID::Arithmetic_Modulo)
		{
			multExp->m_ops.push_back(it->_id);
			it++;
			multExp->m_exprs.push_back(CAtom::Parse(it));		//���� �߿��� ������ �־�� �ϴ� �ٽ� �Ľ�Ʈ�� �ۼ�
		}
		return multExp->m_exprs.size() == 1 ? *(multExp->m_exprs.begin()) : ExprPtr(multExp);
	}

	int CMultExp::Evaluate(SymbolTable &context)
	{
		Exprs::iterator it = m_exprs.begin();

		int result = it->get()->Evaluate(context);

		for (std::list<TokenID>::iterator opIt = m_ops.begin(); opIt != m_ops.end(); opIt++)
		{
			it++;
			if (*opIt == TokenID::Arithmetic_Multiply)
				result *= it->get()->Evaluate(context);
			else if (*opIt == TokenID::Arithmetic_Divide)
				result /= it->get()->Evaluate(context);
			else if (*opIt == TokenID::Arithmetic_Modulo)
				result %= it->get()->Evaluate(context);
		}
		return result;
	}

	// Atom

	CExpression::ExprPtr CAtom::Parse(TokenIter &it)
	{
		CAtom *result;

		switch (it->_id)			//���� ó��.
		{
		case TokenID::Logical_Not:
			it++;
			result = new CNot(Parse(it));		//���ȣ��� ó��
			break;
		case TokenID::Literal_Integer:
			result = new CNumber(it->_data);
			it++;
			break;
		case TokenID::Identifier:
			result = new CIdentifier(it->_name);
			it++;
			break;
		case TokenID::OpenSmall:
			it++;
			result = new CCompoundAtom(CExpression::Parse(it));		//��ȣ�� ó������ ���� �Ľ�Ʈ�� �ۼ�.
			Expect(TokenID::CloseSmall, *it++);
			break;
		default:
			throw Error(std::string("Unexpected : ") + it->_name);
		}
		return ExprPtr(result);
	}
}