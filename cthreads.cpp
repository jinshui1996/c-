#include "cthreads.h"
//��������
void cthreads::push_task(cthread_task* task) {
	shared_ptr< cthread_task> T(task);
	_tasks.push(T);
}
//�����߳�������ʵ���Ǵ���һ���߳�Ȼ�������ں�ִ̨��run
void cthreads::add_thread() {
	atomic_bool* flag = new atomic_bool;
	_threads.push_back(flag);
	flag->store(true);
	std::thread(&cthreads::run_thread, this, flag).detach();//detch()��ʾ���̶߳�����̨ȥ����
}
//ɾ���߳�
void cthreads::del_thread() {
	atomic_bool* flag = _threads.back();
	flag->store(false);//��flag����Ϊfalse����run�оͻ�ֹͣ������
	_threads.pop_back();
}
//�����̳߳صĴ�С
size_t cthreads::count() const {
	return _threads.size();
}
//�����̵߳ĺ����������������Ҫ��
void cthreads::run_thread(std::atomic_bool* thread_flag) {
	while (*thread_flag) {
		shared_ptr<cthread_task> task;
		bool ispop = _tasks.pop(task);
		if (ispop) {
			task->tasks();
		}
		else {
			this_thread::yield();//�ͷ���Դ
		}
	}
	delete thread_flag;
}