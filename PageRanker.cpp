//
//  PageRanker.cpp
//
//  Created by Joseph P. Silva on 6/30/13.
//

#include "PageRanker.h"

#include "RankedPage.h"

#include <iostream>


void PageRanker::add_link(std::string source_page_url, std::string target_page_url)
{
    this->add_if_not_known(source_page_url);
    this->add_if_not_known(target_page_url);
    
    pages[source_page_url].add_ref_if_not_known(pages[target_page_url]);
}


void PageRanker::add_if_not_known(std::string url)
{
    if (pages.count(url)==0)
    {
        RankedPage newPage(url);
        PageFromUrl::value_type pair(url,newPage);
        this->pages.insert(pair);
    }
}


void PageRanker::rank_pages(unsigned int num_iterations, float decay_factor)
{
    // initialize all page ranks to 1/N
    
    size_t num_pages = pages.size();
    float x = 1.0 / num_pages;
    for ( auto page=this->pages.begin(); page!=this->pages.end(); page++)
    {
        page->second.current_rank = x;
    }
    
    std::cout << "INITIAL RANKS " << std::endl;
    std::cout << *this;
        
    // rank the pages # iterations requested
    
    for (unsigned int i=1; i<=num_iterations; i++)
    {
        this->rank_pages(decay_factor);
        std::cout << "*** ITERATION " << i << "***" << std::endl;
        std::cout << *this;
    }
}


void PageRanker::rank_pages(float decay_factor)
{
    size_t num_pages = pages.size();
    
    // initialize next ranks to zero
    
    for ( auto page=this->pages.begin(); page!=this->pages.end(); page++)
    {
        page->second.next_rank = 0;
    }
    
    // distrubute current ranks to the pages using the Page Rank variable term
    // r(i) = sum[j over B::pages pointing to i] r(j) / N(j)
    // the intent is really each source page gives the pages it links to 1/N of its (source page) rank
    // where N is # pages the source links to
    
    for ( auto page=this->pages.begin(); page!=this->pages.end(); page++)
    {
        // leak pages (no out links) distribute their rank to all other pages
        // (user randomly goes to another page)
        if (page->second.links.size()==0)
        {
            for ( auto page2=this->pages.begin(); page2!=this->pages.end(); page2++)
            {
                if (page2->second.url!=page->second.url)
                {
                    float leak_back = page->second.current_rank / (num_pages-1);
                    page2->second.next_rank += leak_back;
                }
            }
        }
        else // non-leak pages distribute to their links (user randomly clicks a link)
        {
            float q = page->second.current_rank / page->second.links.size();
            for ( auto other_page=page->second.links.begin(); other_page!=page->second.links.end(); other_page++)
            {
                other_page->second.next_rank += q;
            }
        }
    }
    
    // multiply the distributed ranks by the decay factor (percent user clicks a link)
    
    for ( auto page=this->pages.begin(); page!=this->pages.end(); page++)
    {
        page->second.next_rank *= decay_factor;
    }
    
    // add the decay factor constant term (1-d)/m to all pages and set current_rank = next_rank
    // (percent user goes randomly to any page instead of clicking on a link)
    
    float c = (1.0-decay_factor) / num_pages;
    for ( auto page=this->pages.begin(); page!=this->pages.end(); page++)
    {
        page->second.next_rank += c;
        page->second.current_rank = page->second.next_rank;
    }
}


std::ostream& operator<< (std::ostream& os, const PageRanker& ranker)
{
    for ( auto page=ranker.pages.cbegin(); page!=ranker.pages.end(); page++)
    {
        os << page->first << " " << page->second.current_rank << std::endl;
    }
    return os;
}