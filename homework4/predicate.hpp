//
// Created by Vio on 06.05.2021.
//

#ifndef PROGA4LAB_PREDICATE_HPP
#define PROGA4LAB_PREDICATE_HPP

#include <iostream>

using namespace std;

template<typename Iterator, typename Predicate>
bool allOf(Iterator begin, Iterator end, Predicate predicate) {

    while (begin != end) {
        if (predicate(*begin) == false) {
            return false;
        }
        begin++;
    }
    return true;
}

template<typename Iterator, typename Predicate>
bool anyOf(Iterator begin, Iterator end, Predicate predicate) {
    while (begin != end) {
        if (predicate(*begin) == true) {
            return true;
        }
        begin++;
    }
    return false;
}

template<typename Iterator, typename Predicate>
bool noneOf(Iterator begin, Iterator end, Predicate predicate) {
    while (begin != end) {
        if (predicate(*begin) == true) {
            return false;
        }
        begin++;
    }
    return true;
}

template<typename Iterator, typename Predicate>
bool oneOf(Iterator begin, Iterator end, Predicate predicate) {
    int flag = 0;
    while (begin != end) {
        if (predicate(*begin) == true) {
            if (flag == 1) {
                return false;
            }
            flag = 1;
        }
        begin++;
    }
    return true;
}

//todo use default template argument std::less
template<typename Iterator, typename Predicate>
bool isSorted(Iterator begin, Iterator end, Predicate predicate) {
    while ((begin + 1) != end) {
        if (predicate(*begin, *(begin + 1)) == false) {
            return false;
        }
        begin++;
    }
    return true;
}

template<typename Iterator>
bool isSorted(Iterator begin, Iterator end) {
    while ((begin + 1) != end) {
        if ((*begin) > *(begin + 1)) {
            return false;
        }
        begin++;
    }
    return true;
}

template<typename Iterator, typename Predicate>
bool isPartitioned(Iterator begin, Iterator end, Predicate predicate) {
    //todo shorter
    if (predicate(*begin) == true) {
        begin++;
        while (begin != end) {
            if (predicate(*begin) == false) {
                break;
            }
            begin++;
        }
        while (begin != end) {
            if (predicate(*begin) == true) {
                return false;
            }
            begin++;
        }
        return true;
    } else {
        begin++;
        while (begin != end) {
            if (predicate(*begin) == true) {
                break;
            }
            begin++;
        }
        while (begin != end) {
            if (predicate(*begin) == false) {
                return false;
            }
            begin++;
        }
        return true;
    }
}

template<typename Iterator, typename Predicate>
Iterator findNot(Iterator begin, Iterator end, Predicate value) {
    while (begin != end) {
        if ((*begin) != value) {
            return begin;
        }
        begin++;
    }
    return end;
}

template<typename Iterator, typename Predicate>
Iterator findBackward(Iterator begin, Iterator end, Predicate value) {
    Iterator ans;
    int flag = 0;
    while (begin != end) {
        if ((*begin) == value) {
            ans = begin;
            flag = 1;
        }
        begin++;
    }
    if (flag)
        return ans;
    else
        return end;
}

template<typename Iterator, typename Predicate>
bool isPalindrome(Iterator begin, Iterator end, Predicate predicate) {
    auto start = begin;
    auto finish = end;
    while (begin != finish && end != start) {
        if (predicate(*begin, *prev(end)) == false) {
            return false;
        }
        begin++;
        end--;
    }
    return true;
}

#endif //PROGA4LAB_PREDICATE_HPP
