//
// Created by martin on 2024-12-03.
//

#ifndef ITER_PQ_H
#define ITER_PQ_H

#include <vector>
#include <algorithm>

namespace labb3 {
    template<typename T, typename Compare>
    class pq {
    private:
        std::vector<T> data;
    public:
        bool empty(){
            return data.empty();
        }
        /**
         * push element e to the queue.
         * @param e
         */
        void push(const T& e){
            data.push_back(e);
            std::push_heap(data.begin(), data.end(), Compare());
        }
        /**
         * Remove topmost element from queue.
         */
        void pop(){
            std::pop_heap(data.begin(), data.end(), Compare());
            data.pop_back();
        }
        /**
         * get the topmost element.
         * @return a reference
         */
        T& top(){
            return data[0];
        }

    };

} // labb3

#endif //ITER_PQ_H
