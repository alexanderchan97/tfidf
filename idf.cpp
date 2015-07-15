#include <string>
#include <vector>
#include <math.h>
#include "tf.hpp"
#include "filereader.hpp"

/**
 * Identifies the unary inverse document frequency of a term
 * @param t the term to identify inverse document frequency of
 * @param d a filename containing the paths to each document in the corpus
 * @return 1 always
 */
int unIdf(const std::string &t, const std::string &d) {
    return 1;
}

/**
 * Identifies the inverse document frequency of a term
 * @param t the term to identify inverse document frequency of
 * @param d a filename containing the paths to each document in the corpus
 * @return the inverse document frequency of the term
 */
double invIdf(const std::string &t, const std::string &d) {
    std::vector<std::string> corpList = getFileList(d);
    const int N = (int) corpList.size();
    int docCount = 0;
    for (auto const &docName : corpList) {
        if (boolTf(t, docName) == 1) {
            docCount++;
        }
    }
    double idf = log10(N / (1 + docCount));
    return idf;
}

/**
 * Identifies the smoothed inverse IDF of a term given by the formula
 * log(1 + (N / (1 + docCount)))
 * @param t the term to identify inverse document frequency of
 * @param d a filename containing the paths to each document in the corpus
 * @return the smoothed IDF of the term
 */
double invSmoothIdf(const std::string &t, const std::string &d) {
    std::vector<std::string> corpList = getFileList(d);
    const int N = (int) corpList.size();
    int docCount = 0;
    for (auto const &docName : corpList) {
        if (boolTf(t, docName) == 1) {
            docCount++;
        }
    }
    double idf = log10(1 + (N / (1 + docCount)));
    return idf;
}