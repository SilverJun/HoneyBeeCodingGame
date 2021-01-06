#include "SymbolTable.h"
#include "Error.h"

namespace script
{
	int SymbolTable::GetValue(std::string variable)
	{
		VarTable::iterator iter = _varTable.find(variable);			//���� Ž��
		if (iter == _varTable.end())				//Ž������.
			throw Error(std::string("Undefined Variable : ") + variable);
		
		return iter->second->_data;
	}

	int SymbolTable::SetValue(std::string variable, int value)
	{
		if (_varTable.find(variable) == _varTable.end())			//���� Ž��
			throw Error(std::string("Undeclared Variable : ") + variable);		//Ž�� ����.
		
		return _varTable[variable]->_data = value;
	}

	void SymbolTable::DeleteValue(std::string variable)
	{
		VarTable::iterator iter = _varTable.find(variable);
		if (iter == _varTable.end())
			throw Error(std::string("Undeclared Variable ") + variable);
		
		_varTable.erase(iter);
	}

	void SymbolTable::AddValue(std::string variable)
	{
		VarTable::iterator itor;
		int i = _varTable.size();
		if (i != 0)		//���� ���̺� �ƹ��� ���� ������ �ٷ� ����, ������ �ߺ� �˻�.
		{
			if (CheckValue(variable))			//Ž�� ���� -> ������ �̹� ��ϵǾ��ִ�.
				throw Error(std::string("Already Registered Variable : ") + variable);
		}

		_varTable[variable] = new Symbol(variable, 0); //Ž�� ���� -> ������ ����� �� �ִ�.
	}

	bool SymbolTable::CheckValue(std::string variable)
	{
		VarTable::iterator itor = _varTable.find(variable);			//���� Ž��
		return itor != _varTable.end();
	}
}
