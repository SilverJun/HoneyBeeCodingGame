#pragma once

#include <list>
#include <memory>

#include "Token.h"
#include "SymbolTable.h"

namespace script
{
	class CExpression		//ǥ������ ���� �⺻�� �Ǵ� �ֻ��� �θ� Ŭ����
	{
	public:
		typedef std::shared_ptr<CExpression> ExprPtr;		//shared_ptr�� �ѹ� �������ش�.
		typedef std::list<ExprPtr> Exprs;			//����Ʈ�� ����
		typedef std::shared_ptr<Exprs> ExprsPtr;		//����Ʈ�� shared_ptr�� �ѹ� �������ش�.
		static ExprPtr Parse(TokenIter &it);			//ǥ������ �м��ϰ� �Ľ�Ʈ���� �����.
		virtual int Evaluate(SymbolTable &context) = 0;		//�м��� �Ľ�Ʈ���� �������� ���� ����ذ���.
		virtual ~CExpression() = default;
	protected:
		static void Expect(TokenID Expected, const Token &NowToken);		//������ �´��� Ȯ���Ѵ�.
	};

}
