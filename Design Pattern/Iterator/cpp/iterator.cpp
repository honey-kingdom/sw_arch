#include <iostream>
#include <sstream>
#include <queue>

template<class Item>
class BaseIterator {
public:
    virtual Item next() = 0;
    virtual bool hasNext() = 0;
};


template<class Item>
class BaseIterable {
public:
    virtual BaseIterator<Item> * createIterator() = 0;
};


class SentenceIterator: public BaseIterator<std::string> {
private:
    std::queue<std::string> words;

public:
    SentenceIterator(std::string sentence) {
        std::stringstream ss(sentence);
        std::string word;

        while(getline(ss, word, ' ')) {
            words.push(word);
        }
    }

    std::string next() override {
        auto word = words.front();
        words.pop();
        return word;
    }

    bool hasNext() override {
        return !words.empty();
    }
};


class Sentence: public BaseIterable<std::string> {
private:
    std::string sentence;

public:
    Sentence(std::string sentence) : sentence(sentence) {}

    BaseIterator<std::string> * createIterator() override {
        return new SentenceIterator(sentence);
    }
};


int main() {
    Sentence my_sentence("This is a test");

    auto iterator = my_sentence.createIterator();

    while(iterator->hasNext()) {
        std::cout << iterator->next() << std::endl;
    }

    delete iterator;
}
