#ifndef AMIT_PROJECT_USER_MANAGER_H_
#define AMIT_PROJECT_USER_MANAGER_H_
#include "std_types.h"
#include "RTC.h"
#define PERMISSION_NONE                         ( ( uint32_t ) 0 )
#define PERMISSION_CREATE_SUPER_ADMIN           ( ( uint32_t ) ( 1ULL << 0 ) )
#define PERMISSION_CREATE_ADMIN                 ( ( uint32_t ) ( 1ULL << 1 ) )
#define PERMISSION_CREATE_WORKER                ( ( uint32_t ) ( 1ULL << 2 ) )
#define PERMISSION_EDIT_SELF                    ( ( uint32_t ) ( 1ULL << 3 ) )
#define PERMISSION_EDIT_SUPER_ADMIN             ( ( uint32_t ) ( 1ULL << 4 ) )
#define PERMISSION_EDIT_ADMIN                   ( ( uint32_t ) ( 1ULL << 5 ) )
#define PERMISSION_EDIT_WORKER                  ( ( uint32_t ) ( 1ULL << 6 ) )
#define PERMISSION_DELETE_SELF                  ( ( uint32_t ) ( 1ULL << 7 ) )
#define PERMISSION_DELETE_SUPER_ADMIN           ( ( uint32_t ) ( 1ULL << 8 ) )
#define PERMISSION_DELETE_ADMIN                 ( ( uint32_t ) ( 1ULL << 9 ) )
#define PERMISSION_DELETE_WORKER                ( ( uint32_t ) ( 1ULL << 10 ) )
#define PERMISSION_VIEW_SELF                    ( ( uint32_t ) ( 1ULL << 11 ) )
#define PERMISSION_VIEW_SUPER_ADMINS            ( ( uint32_t ) ( 1ULL << 12 ) )
#define PERMISSION_VIEW_ADMINS                  ( ( uint32_t ) ( 1ULL << 13 ) )
#define PERMISSION_VIEW_WORKERS                 ( ( uint32_t ) ( 1ULL << 14 ) )
#define PERMISSION_VIEW_SUPER_ADMIN_PASSWORDS   ( ( uint32_t ) ( 1ULL << 15 ) )
#define PERMISSION_VIEW_ADMIN_PASSWORDS         ( ( uint32_t ) ( 1ULL << 16 ) )
#define PERMISSION_VIEW_WORKER_PASSWORDS        ( ( uint32_t ) ( 1ULL << 17 ) )
typedef uint16_t UserId_t;
typedef uint16_t UserPass_t;
typedef enum _UserType_t
{
    USER_TYPE_NONE = ( uint8_t ) 0 ,
    USER_TYPE_SUPER_ADMIN = ( uint8_t ) 1 ,
    USER_TYPE_ADMIN = ( uint8_t ) 2 ,
    USER_TYPE_WORKER = ( uint8_t ) 3 ,
} UserType_t;
typedef struct _User_t
{
    UserId_t id;
    UserPass_t password;
    UserType_t userType;
    uint32_t permissions;
} User_t;
typedef struct _UserLog_t
{
    UserId_t id;
    TIME_t entryTime;
} UserLog_t;
typedef enum _USER_MANAGER_STD_ERR_t
{
    USER_MANAGER_OK = ( uint8_t ) 0 ,
    USER_MANAGER_ERR_ID = ( uint8_t ) 1,
    USER_MANAGER_ERR_FULL = ( uint8_t ) 2 ,
    USER_MANAGER_ERR_USER_TYPE = ( uint8_t ) 3 ,
    USER_MANAGER_ERR_ALREADY_EXIST = ( uint8_t ) 4 ,
    USER_MANAGER_ERR_NOT_EXIST = ( uint8_t ) 5 ,
    USER_MANAGER_ERR_EMPTY = ( uint8_t ) 6 ,
    USER_MANAGER_ERR_PASS = ( uint8_t ) 7 ,
    USER_MANAGER_ERR_WRNG_PASS = ( uint8_t ) 8 ,
    USER_MANAGER_AUTH_OK = ( uint8_t ) 9
} USER_MANAGER_STD_ERR_t;
USER_MANAGER_STD_ERR_t USER_MANAGER_createUser ( UserId_t id , UserPass_t password , UserType_t userType );
USER_MANAGER_STD_ERR_t USER_MANAGER_authenticateUser ( UserId_t id , UserPass_t password );
USER_MANAGER_STD_ERR_t USER_MANAGER_deleteUser ( UserId_t id );
#endif
