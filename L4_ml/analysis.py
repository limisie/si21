import os
import statistics
import string
from sklearn.feature_extraction.text import CountVectorizer
import matplotlib.pyplot as plt


def _get_label_file_name(classes):
    if classes == 4:
        return "label.4class"
    else:
        return "label.3class"


def read_files(dir_path, classes=3):
    label_file_name = _get_label_file_name(classes)
    dirs = [x[0] for x in os.walk(dir_path)][1:]

    texts = []
    labels = []

    for d in dirs:
        for file in os.listdir(d):
            if file.startswith("subj"):
                text_file = open(os.path.join(d, file), "r")
                texts.extend(text_file.read().splitlines())
            if file.startswith(label_file_name):
                label_file = open(os.path.join(d, file), "r")
                labels.extend([int(label) for label in label_file.read().splitlines()])

    return texts, labels


def get_label_texts(label, labels, texts):
    label_texts = []

    for i, text in enumerate(texts):
        if labels[i] == label:
            label_texts.append(text)

    return label_texts


def plot_words_count(texts, title='', top_words_number=20):
    cv = CountVectorizer(stop_words='english')

    cv_fit = cv.fit_transform(texts)
    words = cv.get_feature_names()
    counts = cv_fit.toarray().sum(axis=0)
    count_dict = dict(zip(words, counts))
    sorted_dict = dict(sorted(count_dict.items(), key=lambda item: item[1], reverse=True))

    top_x_words = list(sorted_dict.keys())[:top_words_number]
    top_x_freq = list(sorted_dict.values())[:top_words_number]

    plt.bar(top_x_words, top_x_freq)
    plt.xticks(rotation=45)
    plt.title(f"Number of appearances of top {top_words_number} words {title}")
    plt.xlabel("Word")
    plt.ylabel("Number of appearances")
    plt.show()

    return top_x_words, top_x_freq


def print_classes_statistics(texts, labels):
    word_count, char_count = _get_word_and_char_count(texts)
    label_words, label_chars = _split_word_and_char_count_labels(labels, word_count, char_count)

    for label in range(len(label_words)):
        print(f'LABEL ------------------------- {label}')
        print(f'number of documents: {len(label_words[label])}')

        print('------------- WORDS -------------')
        _print_statistics(label_words[label])

        print('---------- CHARACTERS -----------')
        _print_statistics(label_chars[label])
        print()
        print()

    _plot_class_distribution(label_words)


def _print_statistics(data):
    print(f'min:\t{min(data)}')
    print(f'max:\t{max(data)}')
    print(f'mean:\t{statistics.mean(data)}')
    print(f'st_dev:\t{statistics.stdev(data)}')
    print()


def _get_word_and_char_count(texts):
    word_count = []
    char_count = []

    for text in texts:
        word_count.append(sum(x.strip(string.punctuation).isalpha() for x in text.split()))
        char_count.append(sum(len(x) for x in text.split()))

    return word_count, char_count


def _split_word_and_char_count_labels(labels, word_count, char_count):
    label_words = [[] for i in range(max(labels) + 1)]
    label_chars = [[] for i in range(max(labels) + 1)]

    for i, label in enumerate(labels):
        label_words[label].append(word_count[i])
        label_chars[label].append(char_count[i])

    return label_words, label_chars


def _plot_class_distribution(label_words):
    labels = []
    data = []

    for i, label in enumerate(label_words):
        labels.append(i)
        data.append(len(label))

    if len(labels) == 3:
        x_labels = ['negative', 'neutral', 'positive']
    else:
        x_labels = ['negative', 'slightly negative', 'slightly positive', 'positive']

    plt.bar(labels, data)
    plt.title(f"Class distribution")
    plt.xlabel("Class")
    plt.ylabel("Number of documents")
    plt.xticks(labels, x_labels)
    plt.show()
