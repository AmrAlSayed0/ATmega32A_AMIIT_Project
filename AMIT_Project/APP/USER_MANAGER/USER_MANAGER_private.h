#ifndef AMIT_PROJECT_USER_MANAGER_PRIVATE_H_
#define AMIT_PROJECT_USER_MANAGER_PRIVATE_H_
typedef uint16_t UserCounter_t;
typedef uint32_t UserLogCounter_t;
static int16_t searchUsers ( UserCounter_t numOfUsers , UserId_t id );
static void readUser ( uint16_t userPosition , User_t* readUser );
static void writeUser ( uint16_t userPosition , User_t* readUser );
static void readUserCounter ( UserCounter_t* readUserCounter );
static void writeUserCounter ( UserCounter_t* readUserCounter );
static void readUserLog ( uint32_t userLogPosition , UserLog_t* readUserLog );
static void writeUserLog ( uint32_t userLogPosition , UserLog_t* readUserLog );
static void readUserLogCounter ( UserLogCounter_t* readUserLogCounter );
static void writeUserLogCounter ( UserLogCounter_t* readUserLogCounter );
#endif