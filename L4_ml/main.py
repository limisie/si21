from analysis import *
from classifiers import multinomialNB, linearSVC
from preprocessing import *

DATA_PATH = "./scaledata"
CLASS_COUNT = 3


def plot_analyses(texts, labels):
    print_classes_statistics(texts, labels)

    plot_words_count(texts)
    for i in range(max(labels) + 1):
        label_texts = get_label_texts(i, labels, texts)
        plot_words_count(label_texts, f'- class {i}')


if __name__ == '__main__':
    texts, labels = read_files(DATA_PATH, CLASS_COUNT)
    # plot_analyses(texts, labels)

    X_train, X_test, y_train, y_test = train_test_split(texts, labels, test_size=0.2)
    linearSVC(X_train, X_test, y_train, y_test)
