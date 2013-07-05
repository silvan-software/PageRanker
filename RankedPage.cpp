//
//  RankedPage.cpp
//
//  Created by Joseph P. Silva on 6/30/13.
//

#include "RankedPage.h"

#include <ostream>

RankedPage::RankedPage(std::string url)
{
    this->url = url;
    this->current_rank = 0;
    this->next_rank = 0;
}


void RankedPage::add_ref_if_not_known(RankedPage& other_page)
{
    if (this->links.count(other_page.url)==0)
    {
        PageRefsFromUrl::value_type pair(other_page.url,other_page);
        this->links.insert(pair);
    }
}


std::ostream& operator<< (std::ostream& os, const RankedPage& page)
{
    os << "url: " << page.url << std::endl;
    os << " current_rank: " << page.current_rank << std::endl;
    os << " next_rank: " << page.next_rank << std::endl;
   
    for ( auto linked_page=page.links.cbegin(); linked_page!=page.links.end(); linked_page++)
    {
        os << " linked page: " << linked_page->second.url << std::endl;
    }
    return os;
}