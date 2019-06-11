#ifndef TEST_TASK_CONTAINER_H
#define TEST_TASK_CONTAINER_H

#include <utility>

template<class Key, class Data>
class Container {
public:
    Container() {
        topn_size = 0;
    }

    virtual ~Container() = default;

    long long get_topn_size() const { return topn_size; }

    virtual void add(Key price, Data amount) {};

    virtual void remove(Key price) {};

    virtual std::pair<Key, Data> get_first() {};

    virtual Data get(Key price) {};

    virtual std::pair<Key, Data> *topn(long long n) {};

    virtual unsigned long long get_sum_amount() {};

protected:
    void set_topn_size(long long n) { topn_size = n; }

private:
    long long topn_size;
};

#endif //TEST_TASK_CONTAINER_H
