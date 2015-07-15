#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
    std::vector<std::string> termFirst;
    std::vector<std::string> termSec;
    std::vector<double> tfidfFirst;
    std::vector<double> tfidfSec;
    for (size_t i = 0, ilen = docList.size(); i < ilen; i++) {
        tfidfFirst.push_back(0);
        tfidfSec.push_back(0);
        termFirst.push_back("unknown");
        termSec.push_back("unknown");
    }

    for (const auto &t : termList) {
        double tf;
        double idf = invIdf(t, argv[3]);
        for (size_t i = 0, ilen = docList.size(); i < ilen; i++) {
            std::string d = docList[i];
            tf = logNormTf(t, d);
            double tfidf = tf * idf;
            if (isnan(tfidf) || isinf(tfidf)) {
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