//
//  main.cpp
//  PageRanker
//
//  Created by Joe on 6/30/13.
//  Copyright (c) 2013 JosephSilva. All rights reserved.
//

#include "PageRanker.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>


void readFile(const char* file_name, PageRanker& pr)
{
    std::fstream fs(file_name);
    if (fs.fail())
    {
        throw 1;
    }
    const size_t MAX_LINE_LENGTH = 4096;
    char* buffer = new char[MAX_LINE_LENGTH];
    int line_num = 0;
    while (!fs.eof())
    {
        fs.getline(buffer, MAX_LINE_LENGTH-1);
        line_num++;
        char* page1 = strtok(buffer, " ");
        char* page2 = strtok(NULL, " ");
        if (!page1)
            printf("line %d no pages...ignored\n",line_num);
        else if (!page2)
            printf("line %d missing second page...ignored\n",line_num);
        else if (strcmp(page1, page2)==0)
            printf("line %d page links to itself...ignored\n",line_num);
        else
        {
            pr.add_link(page1, page2);
        }
    }
    delete[] buffer;
}


int main(int argc, const char * argv[])
{
    if (argc<4)
    {
        printf("Usage: %s filename num_iterations decay_factor\n",argv[0]);
        return 1;
    }
    PageRanker pr;
    
    try {
        readFile(argv[1],pr);
    }
    catch (...) {
        printf("failed to open file\n");
        return 1;
    }
    
    float num_interations = strtof(argv[2],NULL);
    float decay_factor = strtof(argv[3],NULL);
    pr.rank_pages(num_interations, decay_factor);
    return 0;
}


