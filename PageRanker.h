//
//  PageRanker.h
//
//  Created by Joseph P. Silva on 6/30/13.
//

#ifndef PageRanker_PageRanker_h
#define PageRanker_PageRanker_h

#include "RankedPage.h"

#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string,RankedPage> PageFromUrl;

class PageRanker
{
    friend std::ostream& operator<< (std::ostream& os, const PageRanker&);
public:
    void add_link(std::string source_page_url, std::string target_page_url);
    void rank_pages(unsigned int num_iterations, float decay_factor);
private:
    PageFromUrl pages;
    
    void add_if_not_known(std::string url);
    void rank_pages(float decay_factor);
};

std::ostream& operator<< (std::ostream& os, const PageRanker&);

#endif
