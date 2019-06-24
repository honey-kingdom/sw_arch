
class Sentence_Iterator:

    def __init__(self, sentence):
        self.words = sentence.split(' ')
        self.index = 0

    def __next__(self):
        if self.index >= len(self.words):
            raise StopIteration
        index = self.index
        self.index += 1
        return self.words[index]


class Sentence:

    def __init__(self, sentence):
        self.iterator = Sentence_Iterator(sentence)

    def __iter__(self):
        return self.iterator


my_sentence = Sentence('This is a test')

for word in my_sentence:
    print(word)


my_sentence = Sentence('This is a test')

print(next(my_sentence.iterator))
print(next(my_sentence.iterator))
print(next(my_sentence.iterator))
print(next(my_sentence.iterator))
# print(next(my_sentence.iterator)) # StopIteration


def sentence(sentence):
    for word in sentence.split(' '):
        yield word


my_sentence = sentence('This is a test')

for word in my_sentence:
    print(word)

my_sentence = sentence('This is a test')

print(next(my_sentence))
print(next(my_sentence))
print(next(my_sentence))
print(next(my_sentence))
# print(next(my_sentence.iterator)) # StopIteration
