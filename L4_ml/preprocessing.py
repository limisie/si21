import os
import string

from nltk import WordNetLemmatizer, word_tokenize
from nltk.corpus import stopwords
from nltk.stem.porter import PorterStemmer
from sklearn.model_selection import train_test_split


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


def uni_grams_clean_up(texts, stem=False, lemmatize=False):
    processed = []
    punctuation_destroyer = str.maketrans('', '', string.punctuation)
    stop_words = set(stopwords.words('english'))
    wnl = WordNetLemmatizer()
    porter = PorterStemmer()

    for text in texts:
        stripped = [t.translate(punctuation_destroyer) for t in word_tokenize(text)]
        words = [w for w in stripped if w.isalpha() and w not in stop_words]

        if stem:
            words = [porter.stem(word) for word in words]

        if lemmatize:
            words = [wnl.lemmatize(word) for word in words]

        processed.append(' '.join([str(word) for word in words]))

    return processed


def split_data(texts, labels):
    X_train, X_test, y_train, y_test = train_test_split(texts, labels)
    return X_train, X_test, y_train, y_test


class LemmaTokenizer(object):
    def __init__(self):
        self.wnl = WordNetLemmatizer()

    def __call__(self, articles):
        return [self.wnl.lemmatize(t) for t in word_tokenize(articles)]
