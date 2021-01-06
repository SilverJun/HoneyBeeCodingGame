#include "Expression.h"
#include "Error.h"
#include "ExpressionImpl.h"
#include <iostream>

namespace script
{
	void CExpression::Expect(TokenID Expected, const Token &NowToken)
	{
#ifdef _DEBUG
		std::cout << "Expression Token : " << NowToken._name << std::endl;
#endif

		if (Expected != NowToken._id)
			throw (Error(std::string("SyntaxError : ") + NowToken._name));
	}

	CExpression::ExprPtr CExpression::Parse(TokenIter &it)
	{
		//������ �켱������ ���ؼ� ���� �������� �ϴ� or������� �Ʒ��� �Ľ�Ʈ�� �ۼ�.
		return ExprPtr(CComparisonExp::Parse(it));
	}

	// OrExp
}
