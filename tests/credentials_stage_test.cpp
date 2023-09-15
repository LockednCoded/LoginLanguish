#include <gtest/gtest.h>
#include "stages/credentials_stage.h"

namespace {
    class CredentialsStageTest : public ::testing::Test {
        protected:
            CredentialsStage *credentialsStage;

            CredentialsStageTest() {
                // You can do set-up work for each test here.
            }

            virtual ~CredentialsStageTest() {
                // You can do clean-up work that doesn't throw exceptions here.
            }

            // If the constructor and destructor are not enough for setting up
            // and cleaning up each test, you can define the following methods:
            virtual void SetUp() {
                // Code here will be called immediately after the constructor (right
                // before each test).
                credentialsStage = new CredentialsStage();
            }

            virtual void TearDown() {
                // Code here will be called immediately after each test (right
                // before the destructor).
                delete credentialsStage;
            }

            // Objects declared here can be used by all tests in the test case for CredentialStage. 
    };
}

TEST_F(CredentialsStageTest, StageName) {
    EXPECT_TRUE(credentialsStage->getStageName().compare("credentials") == 0);
}