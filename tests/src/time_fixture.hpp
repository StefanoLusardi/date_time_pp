#pragma once 

#include "gtest/gtest.h"
#include <dtpp/time_t.hpp>

namespace dtpp
{

class time_fixture : public ::testing::Test
{
protected:
    explicit time_fixture() { }
    virtual ~time_fixture() { }
    virtual void SetUp() override { }
    virtual void TearDown() override { }

    dtpp::time_t d;

private:
    template<typename... Args>
    void log(Args&&... args) const
    {
        ((std::cout << std::forward<Args>(args) << ' ') , ...) << std::endl;
    }
};

}
