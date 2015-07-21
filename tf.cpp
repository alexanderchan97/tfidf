#include <string>
#include <math.h>
#include "tf.hpp"
#include "filereader.hpp"

/**
 * Identifies the boolean term frequency of a term within the document
 * @param t the term to identify term frequency
 * @param d the document within which to identify the term
 * @return 1 if the term exists in the document, 0 otherwise
 */
int boolTf(const std::string &t, const std::string &d) {
    std::string dText = readFile(d);
    size_t found = dText.find(t);
    if (found != std::string::npos) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Identifies the raw term frequency of a term within the document
 * @param t the term to identify term frequency
 * @param d the document within which to identify the term
 * @return the count of the term within the document
 */
int rawTf(const std::string &t, const std::string &d) {
    std::string dText = readFile(d);
    size_t lastIndex = 0;
    int freq = 0;
    while (lastIndex != std::string::npos) {
        lastIndex = dText.find(t, lastIndex);
        if (lastIndex != std::string::npos) {
            freq++;
            lastIndex += t.length();
        }
    }
    return freq;
}

/**
 * Identifies the logarithmically scaled frequency of a term within the document
 * given by the formula log(1 + rawTf(t, d))
 * @param t the term to identify term frequency
 * @param d the document within which to identify the term
 * @return the logarithmically scaled frequency of the term
 * @see rawTf(const std::string &t, const std::string &d)
 */
double logNormTf(const std::string &t, const std::string &d) {
    return log10(1 + (double) rawTf(t, d));
}
