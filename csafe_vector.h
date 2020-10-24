#pragma once
#include <iostream>
#include <queue>
#include <mutex>
using namespace std;
//�������¶���vector��ʹ����Բ�����
template<typename type>
class csafe_vector
{
public:
	using creferenced = type&;
	//������д������ģ���࣬������ԼӲ���
	template<typename... Args>
	void push(Args &&... args) {
		lock_guard<mutex> lock(_mutex);
		_safe_vector.push_back(args...);
	}
	//
	bool pop(creferenced value) {
		lock_guard<mutex> lock(_mutex);
		if (_safe_vector.empty())return false;
		value = _safe_vector.back();
		_safe_vector.pop_back();
		return true;
	}

private:
	vector<type> _safe_vector;
	mutex _mutex;
};

