import numpy as np
from sklearn.feature_extraction.text import CountVectorizer, TfidfTransformer
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.model_selection import GridSearchCV, cross_validate
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import Pipeline
from sklearn.svm import LinearSVC


def multinomialNB(X_train, X_test, y_train, y_test):
    text_clf = Pipeline([
        ('vect', CountVectorizer(max_df=0.8, max_features=5000, min_df=0.01, ngram_range=(1, 2))),
        ('tfidf', TfidfTransformer(use_idf=True)),
        ('clf', MultinomialNB(alpha=0.01)),
    ])

    text_clf.fit(X_train, y_train)
    y_pred = text_clf.predict(X_test)

    print(np.mean(y_pred == y_test))
    print(classification_report(y_test, y_pred))
    print(confusion_matrix(y_test, y_pred))

    cv_results = cross_validate(text_clf, X_train, y_train, cv=10)
    print(cv_results)
    print(np.mean(cv_results['test_score']))


def linearSVC(X_train, X_test, y_train, y_test):
    text_clf = Pipeline([
        ('vect', CountVectorizer(max_df=0.8, max_features=5000, min_df=0.01, ngram_range=(1, 2))),
        ('tfidf', TfidfTransformer(use_idf=True)),
        ('clf', LinearSVC(C=1, loss='squared_hinge')),
    ])

    text_clf.fit(X_train, y_train)
    y_pred = text_clf.predict(X_test)

    print(np.mean(y_pred == y_test))
    print(classification_report(y_test, y_pred))
    print(confusion_matrix(y_test, y_pred))


def tuning(pipeline, texts, labels, classifier='NB'):
    parameters = {
        'vect__ngram_range': [(1, 1), (1, 2), (1, 3)],
        'vect__stop_words': ['english', None],
        'vect__max_features': [None, 1000, 3000, 5000],
        'vect__max_df': [0.7, 0.8, 0.9, 1.0],
        'vect__min_df': [1, 0.01, 0.1, 0.2],
        'tfidf__use_idf': [True, False],
    }

    if classifier == 'NB':
        parameters['clf__alpha'] = [1, 0.1, 0.01, 0.001, 0]
    else:
        parameters['clf__C'] = [0.1, 1, 10, 100]
        parameters['clf__loss'] = ['hinge', 'squared_hinge']

    gs_clf = GridSearchCV(pipeline, parameters, cv=10, n_jobs=-1)
    gs_clf = gs_clf.fit(texts, labels)

    print(gs_clf.best_score_)
    for param_name in sorted(parameters.keys()):
        print("%s: %r" % (param_name, gs_clf.best_params_[param_name]))
