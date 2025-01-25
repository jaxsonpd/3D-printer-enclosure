/** 
 * @file test_command.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-10-18
 * @brief Tests for the command module
 */


#include <stdint.h>
#include <stdbool.h>


#include "unity.h"

#include "fff.h"
DEFINE_FFF_GLOBALS;
#define FFF_MOCK_IMPL


void reset_fff(void) {
    
}

void setUp(void) {
   
}

void tearDown(void) {
   
}

// =========================== Tests ===========================
void test_example(void) {
    int result = 1;
    TEST_ASSERT_EQUAL_MESSAGE(1, result, "Command should have been correct");
}
