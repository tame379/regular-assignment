#include <gtest/gtest.h>

#include <memory>
#include <tuple>

#include "Executor.hpp"

namespace adas
{

// 为 Pose 定义 == 运算符重载，
// 使得在测试中比较 Pose 对象更简单、直观。
// std::tie 可以简化多个成员变量的比较。
bool operator==(const Pose& lhs, const Pose& rhs)
{
    return std::tie(lhs.x, lhs.y, lhs.heading) == std::tie(rhs.x, rhs.y, rhs.heading);
}

// 测试套件名：ExecutorTest
// 测试用例名：should_return_init_pose_when_without_command
// 清晰地描述了预期行为与测试条件，更容易理解测试目标。
TEST(ExecutorTest, should_return_init_pose_when_without_command)
{
    // given：初始化一个 Executor 对象，朝向东（E）
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when：未执行任何指令

    // then：验证返回的位置与朝向是否保持初始状态
    const Pose target({0, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // then
    const Pose target({0, 0, 'N'});
    ASSERT_EQ(target, executor->Query());
}


}  // namespace adas
