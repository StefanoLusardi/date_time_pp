#pragma once 

#include "gtest/gtest.h"
#include <dtpp/datetime_t.hpp>

namespace dtpp
{

class datetime_fixture : public ::testing::Test
{
protected:
    explicit datetime_fixture() { }
    virtual ~datetime_fixture() { }
    virtual void SetUp() override { }
    virtual void TearDown() override { }

    dtpp::datetime_t d;

private:
    template<typename... Args>
    void log(Args&&... args) const
    {
        ((std::cout << std::forward<Args>(args) << ' ') , ...) << std::endl;
    }
};

}
