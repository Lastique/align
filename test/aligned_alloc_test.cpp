/*
 Copyright (c) 2014 Glen Joseph Fernandes
 glenfe at live dot com

 Distributed under the Boost Software License,
 Version 1.0. (See accompanying file LICENSE_1_0.txt
 or copy at http://boost.org/LICENSE_1_0.txt)
*/
#include <boost/align/aligned_alloc.hpp>
#include <boost/align/is_aligned.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <cstring>

void test(std::size_t alignment)
{
    {
        void* p = boost::alignment::aligned_alloc(alignment,
            alignment);
        BOOST_TEST(p != 0);
        BOOST_TEST(boost::alignment::is_aligned(alignment, p));
        std::memset(p, 0, 1);
        boost::alignment::aligned_free(p);
    }
    {
        void* p = boost::alignment::aligned_alloc(alignment,
            alignment + 1);
        BOOST_TEST(p != 0);
        BOOST_TEST(boost::alignment::is_aligned(alignment, p));
        std::memset(p, 0, 1);
        boost::alignment::aligned_free(p);
    }
    if (alignment > 1) {
        void* p = boost::alignment::aligned_alloc(alignment,
            alignment - 1);
        BOOST_TEST(p != 0);
        BOOST_TEST(boost::alignment::is_aligned(alignment, p));
        std::memset(p, 0, 1);
        boost::alignment::aligned_free(p);
    }
    {
        void* p = boost::alignment::aligned_alloc(alignment, 0);
        boost::alignment::aligned_free(p);
    }
}

int main()
{
    for (std::size_t i = 1; i <= 128; i <<= 1) {
        test(i);
    }

    return boost::report_errors();
}
