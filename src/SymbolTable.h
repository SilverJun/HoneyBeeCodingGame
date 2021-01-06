#pragma once
#include <string>
#include <vector>
//#include <functional>
#include <unordered_map>
#include "PlayerAction.h"

namespace script
{
	struct Symbol
	{
		std::string _name;
		int _data;

		Symbol(std::string name, int data) : _name(name), _data(data) {}
		~Symbol() = default;
	};

	class SymbolTable
	{
	public:
		int GetValue(std::string variable);			//���� �޾ƿ´�.
		int SetValue(std::string variable, int value);			//���� �����ϰ� ��ȯ�Ѵ�.
		bool CheckValue(std::string variable);			//������ �ִ��� Ȯ���Ѵ�.
		void DeleteValue(std::string variable);

		void AddValue(std::string variable);			//������ ����Ѵ�.

		void AddAction(PlayerAction action)
		{
			_actions.push_back(action);
		}

		std::vector<PlayerAction> GetActions()
		{
			return _actions;
		}
	private:
		typedef std::unordered_map<std::string, Symbol*> VarTable;

		VarTable _varTable;
		std::vector<PlayerAction> _actions;
	};
}
