#pragma once
#include "token.h"
#include "SymbolTable.h"
#include <memory>
#include <list>
namespace script
{
	class CStatement				//���๮ �ֻ��� Ŭ����
	{
	public:
		virtual void Execute(SymbolTable &context);			//���๮ ����.	expression���� Evaluate�� ����.
		static CStatement* Create(TokenIter &itor);			//���๮ ����.	expression���� Parse�� ����.
		virtual ~CStatement();

	protected:
		static void Expect(TokenID Expected, const Token &NowToken);			//�������� ������ �����ϱ� ���� �ۼ�.
	};

	typedef std::shared_ptr<CStatement> StatementPtr;
	typedef std::list<StatementPtr> StatementList;

}