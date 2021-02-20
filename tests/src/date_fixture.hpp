#pragma once 

#include "gtest/gtest.h"
#include <dtpp/date_t.hpp>

namespace dtpp
{

class date_fixture : public ::testing::Test
{
protected:
    explicit date_fixture() { }
    virtual ~date_fixture() { }
    virtual void SetUp() override { }
    virtual void TearDown() override { }

    dtpp::date_t d;

private:
    template<typename... Args>
    void log(Args&&... args) const
    {
        ((std::cout << std::forward<Args>(args) << ' ') , ...) << std::endl;
    }
};

}
