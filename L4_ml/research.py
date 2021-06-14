from preprocessing import uni_grams_clean_up


def stem_lem_comparison(texts):
    stem = uni_grams_clean_up(texts, stem=True)
    lem = uni_grams_clean_up(texts, lemmatize=True)
    stem_lem = uni_grams_clean_up(texts, stem=True, lemmatize=True)

    stem_diff = []
    lem_diff = []
    stem_lem_diff = []
    for i, text in enumerate(stem):
        for j, token in enumerate(text):
            if stem[i][j] != lem[i][j]:
                stem_diff.append(token)
                lem_diff.append(lem[i][j])
                stem_lem_diff.append(stem_lem[i][j])

    print(stem_diff)
    print(lem_diff)
    print(stem_lem_diff)