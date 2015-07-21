#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "tf.hpp"
#include "idf.hpp"
#include "filereader.hpp"

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "usage: tfidf termList documentList corpusList\n");
        return 1;
    }

    std::vector<std::string> termList = getFileList(argv[1]);
    std::vector<std::string> docList = getFileList(argv[2]);
    std::vector<std::string> termFirst(docList.size(), "unknown");
    std::vector<std::string> termSec(docList.size(), "unknown");
    std::vector<double> tfidfFirst(docList.size(), 0);
    std::vector<double> tfidfSec(docList.size(), 0);

    for (const auto &t : termList) {
        double idf = invIdf(t, argv[3]);
        for (size_t i = 0, ilen = docList.size(); i < ilen; i++) {
            std::string d = docList[i];
            double tf = logNormTf(t, d);
            double tfidf = tf * idf;
            if (std::isnan(tfidf) || std::isinf(tfidf)) {
                tfidf = 0;
            }
            if (tfidfFirst[i] < tfidf) {
                tfidfSec[i] = tfidfFirst[i];
                tfidfFirst[i] = tfidf;
                termSec[i] = termFirst[i];
                termFirst[i] = t;
            }
        }
    }

    std::ofstream out("tfidfList.csv");
    std::string header = "Comment Number,First Topic,tf-idf value,Second Topic,tf-idf value\n";
    out << header;

    for (size_t i = 0, ilen = docList.size(); i < ilen; i++) {
        std::string commentName = docList[i].substr(docList[i].find("Comment_"));
        std::string line = commentName + "," + termFirst[i] + "," + std::to_string(tfidfFirst[i]) + "," + termSec[i] + "," + std::to_string(tfidfSec[i])+"\n";
        out << line;
    }

    out.close();

    return 0;
}
