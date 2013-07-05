//
//  RankedPage.h
//
//  Created by Joseph P. Silva on 6/30/13.
//

#ifndef PageRanker_RankedPage_h
#define PageRanker_RankedPage_h

#include <string>
#include <unordered_map>

class RankedPage;
typedef std::unordered_map<std::string,RankedPage&> PageRefsFromUrl;

class RankedPage
{
public:
    RankedPage(std::string url);
    
    void add_ref_if_not_known(RankedPage& other_page);
        
    std::string url;
    PageRefsFromUrl links;
    float current_rank;
    float next_rank;
    
    RankedPage() {};
};

std::ostream& operator<< (std::ostream& os, const RankedPage&);


#endif
