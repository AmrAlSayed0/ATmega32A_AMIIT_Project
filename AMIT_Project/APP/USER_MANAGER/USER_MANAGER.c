#include <math.h>
#include "std_types.h"
#include "EEPROM.h"
#include "EXT_EEPROM.h"
#include "USER_MANAGER.h"
#include "USER_MANAGER_config.h"
#include "USER_MANAGER_private.h"
#define MAX_ID_VALUE                ( ( UserId_t ) 9999 )
#define SIZE_OF_USER                ( sizeof ( User_t ) )
#define SIZE_OF_USER_COUNTER        ( sizeof ( UserCounter_t ) )
#define ADDR_OF_USER_COUNTER        ( EEPROM_SIZE_IN_BYTES - SIZE_OF_USER_COUNTER )
#define MAX_NUM_OF_USERS            ( ( uint16_t ) floor ( ( ( ( double ) EEPROM_SIZE_IN_BYTES ) - ( ( double ) SIZE_OF_USER_COUNTER ) ) / ( ( double ) SIZE_OF_USER ) ) )
#define SIZE_OF_USER_LOG            ( sizeof ( UserLog_t ) )
#define SIZE_OF_USER_LOG_COUNTER    ( sizeof ( UserLogCounter_t ) )
#define ADDR_OF_USER_LOG_COUNTER    ( EXT_EEPROM_SIZE_IN_BYTES - SIZE_OF_USER_LOG_COUNTER )
#define MAX_NUM_OF_USERS_LOGS       ( ( uint16_t ) floor ( ( ( ( double ) EXT_EEPROM_SIZE_IN_BYTES ) - ( ( double ) SIZE_OF_USER_LOG_COUNTER ) ) / ( ( double ) SIZE_OF_USER_LOG ) ) )
static int16_t searchUsers ( UserCounter_t numOfUsers , UserId_t id )
{
    User_t currentUserToCompare;
    if ( numOfUsers == 0 )
    {
        return ( int16_t ) - 1;
    }
    else if ( numOfUsers == 1 )
    {
        readUser ( 0 , &currentUserToCompare );
        if ( id < currentUserToCompare.id )
        {
            return ( int16_t ) - 1;
        }
        else if ( id > currentUserToCompare.id )
        {
            return ( int16_t ) - 2;
        }
        else
        {
            return ( int16_t ) 0;
        }
    }
    else
    {
        readUser ( 0 , &currentUserToCompare );
        if ( id < currentUserToCompare.id )
        {
            return ( int16_t ) - 1;
        }
        readUser ( numOfUsers - 1 , &currentUserToCompare );
        if ( id > currentUserToCompare.id )
        {
            return ( int16_t ) - numOfUsers;
        }
        uint16_t low = 0;
        uint16_t high = numOfUsers - 1;
        uint16_t currentIndex;
        while ( low <= high )
        {
            currentIndex = ( uint16_t ) floor ( ( ( ( double ) low ) + ( ( double ) high ) ) / ( ( double ) 2 ) );
            readUser ( currentIndex , &currentUserToCompare );
            if ( id > currentUserToCompare.id )
            {
                low = ++currentIndex;
            }
            else if ( id < currentUserToCompare.id )
            {
                high = --currentIndex;
            }
            else
            {
                return currentIndex;
            }
        }
        return -( currentIndex + 1 );
    }
}
static void readUser ( uint16_t userPosition , User_t* user )
{
    EEPROM_readSection ( userPosition * SIZE_OF_USER , SIZE_OF_USER , ( uint8_t* ) user );
}
static void writeUser ( uint16_t userPosition , User_t* user )
{
    EEPROM_writeSection ( userPosition * SIZE_OF_USER , SIZE_OF_USER , ( uint8_t* ) user );
}
static void readUserCounter ( UserCounter_t* userCounter )
{
    EEPROM_readSection ( ADDR_OF_USER_COUNTER , SIZE_OF_USER_COUNTER , ( uint8_t* ) userCounter );
}
static void writeUserCounter ( UserCounter_t* userCounter )
{
    EEPROM_writeSection ( ADDR_OF_USER_COUNTER , SIZE_OF_USER_COUNTER , ( uint8_t* ) userCounter );
}
#pragma GCC diagnostic ignored "-Wunused-function"
static void readUserLog ( uint32_t userLogPosition , UserLog_t* userLog )
{
    EXT_EEPROM_readSection ( userLogPosition * SIZE_OF_USER_LOG , SIZE_OF_USER_LOG , ( uint8_t* ) userLog );
}
static void writeUserLog ( uint32_t userLogPosition , UserLog_t* userLog )
{
    EXT_EEPROM_writeSection ( userLogPosition * SIZE_OF_USER_LOG , SIZE_OF_USER_LOG , ( uint8_t* ) userLog );
}
static void readUserLogCounter ( UserLogCounter_t* userLogCounter )
{
    EXT_EEPROM_readSection ( ADDR_OF_USER_LOG_COUNTER , SIZE_OF_USER_LOG_COUNTER , ( uint8_t* ) userLogCounter );
}
static void writeUserLogCounter ( UserLogCounter_t* userLogCounter )
{
    EXT_EEPROM_writeSection ( ADDR_OF_USER_LOG_COUNTER , SIZE_OF_USER_LOG_COUNTER , ( uint8_t* ) userLogCounter );
}
USER_MANAGER_STD_ERR_t USER_MANAGER_createUser ( UserId_t id , UserPass_t password , UserType_t userType )
{
    USER_MANAGER_STD_ERR_t opResult = USER_MANAGER_OK;
    UserCounter_t currentUserCount;
    readUserCounter ( &currentUserCount );
    if ( currentUserCount == ( UserCounter_t ) 0xFFFF )
    {
        currentUserCount = 0;
    }
    if ( currentUserCount >= MAX_NUM_OF_USERS )
    {
        opResult = USER_MANAGER_ERR_FULL;
    }
    else
    {
        if ( id <= MAX_ID_VALUE )
        {
            if ( password > 999 && password < 10000 )
            {
                int16_t searchResult = searchUsers ( currentUserCount , id );
                if ( searchResult < 0 )
                {
                    uint16_t indexToInsertTo = ( uint16_t ) ( ( -searchResult ) - 1 );
                    User_t userToBeAdded = {
                        id ,
                        password ,
                        userType ,
                        PERMISSION_NONE
                    };
                    switch ( userType )
                    {
                        case USER_TYPE_NONE :
                            break;
                        case USER_TYPE_SUPER_ADMIN :
                            userToBeAdded.permissions = PERMISSION_CREATE_SUPER_ADMIN | PERMISSION_CREATE_ADMIN | PERMISSION_CREATE_WORKER | PERMISSION_EDIT_SELF | PERMISSION_EDIT_ADMIN | PERMISSION_EDIT_WORKER | PERMISSION_DELETE_SELF | PERMISSION_DELETE_ADMIN | PERMISSION_DELETE_WORKER | PERMISSION_VIEW_ADMINS | PERMISSION_VIEW_WORKERS | PERMISSION_VIEW_ADMIN_PASSWORDS | PERMISSION_VIEW_WORKER_PASSWORDS;
                            break;
                        case USER_TYPE_ADMIN :
                            userToBeAdded.permissions = PERMISSION_CREATE_WORKER | PERMISSION_EDIT_SELF | PERMISSION_EDIT_WORKER | PERMISSION_DELETE_SELF | PERMISSION_DELETE_WORKER | PERMISSION_VIEW_WORKERS | PERMISSION_VIEW_WORKER_PASSWORDS;
                            break;
                        case USER_TYPE_WORKER :
                            userToBeAdded.permissions = PERMISSION_EDIT_SELF | PERMISSION_DELETE_SELF;
                            break;
                        default:
                            opResult = USER_MANAGER_ERR_USER_TYPE;
                    }
                    if ( opResult == USER_MANAGER_OK )
                    {
                        if ( indexToInsertTo < currentUserCount )
                        {
                            EEPROM_move ( ( indexToInsertTo + 1 ) * SIZE_OF_USER , indexToInsertTo * SIZE_OF_USER , ( currentUserCount - indexToInsertTo ) * SIZE_OF_USER );
                        }
                        writeUser ( indexToInsertTo , &userToBeAdded );
                        currentUserCount++;
                    }
                }
                else
                {
                    opResult = USER_MANAGER_ERR_ALREADY_EXIST;
                }
            }
            else
            {
                opResult = USER_MANAGER_ERR_PASS;
            }
        }
        else
        {
            opResult = USER_MANAGER_ERR_ID;
        }
    }
    writeUserCounter ( &currentUserCount );
    return opResult;
}
USER_MANAGER_STD_ERR_t USER_MANAGER_authenticateUser ( UserId_t id , UserPass_t password )
{
    USER_MANAGER_STD_ERR_t opResult = USER_MANAGER_OK;
    if ( id <= MAX_ID_VALUE )
    {
        if ( password > 999 && password < 10000 )
        {
            UserCounter_t currentUserCount;
            readUserCounter ( &currentUserCount );
            int16_t searchResult = searchUsers ( currentUserCount , id );
            User_t currentUser;
            if ( searchResult >= 0 )
            {
                readUser ( searchResult , &currentUser );
                if ( currentUser.password != password )
                {
                    opResult = USER_MANAGER_ERR_WRNG_PASS;
                }
                else
                {
                    opResult = USER_MANAGER_AUTH_OK;
                }
            }
            else
            {
                opResult = USER_MANAGER_ERR_NOT_EXIST;
            }
        }
        else
        {
            opResult = USER_MANAGER_ERR_PASS;
        }
    }
    else
    {
        opResult = USER_MANAGER_ERR_ID;
    }
    return opResult;
}
USER_MANAGER_STD_ERR_t USER_MANAGER_deleteUser ( UserId_t id )
{
    USER_MANAGER_STD_ERR_t opResult = USER_MANAGER_OK;
    UserCounter_t currentUserCount;
    readUserCounter ( &currentUserCount );
    if ( currentUserCount == ( UserCounter_t ) 0xFFFF )
    {
        currentUserCount = 0;
    }
    if ( currentUserCount == 0 )
    {
        opResult = USER_MANAGER_ERR_EMPTY;
    }
    else
    {
        int16_t searchResult = searchUsers ( currentUserCount , id );
        if ( searchResult < 0 )
        {
            opResult = USER_MANAGER_ERR_NOT_EXIST;
        }
        else
        {
            if ( ( UserCounter_t ) searchResult == ( currentUserCount - 1 ) )
            {
                EEPROM_fill ( searchResult * SIZE_OF_USER , SIZE_OF_USER , 0xFF );
            }
            else
            {
                EEPROM_move ( searchResult * SIZE_OF_USER , ( searchResult + 1 ) * SIZE_OF_USER , ( currentUserCount - searchResult - 1 ) * SIZE_OF_USER );
            }
            currentUserCount--;
        }
    }
    writeUserCounter ( &currentUserCount );
    return opResult;
}
USER_MANAGER_STD_ERR_t USER_MANAGER_logUserEntry ( UserId_t id , TIME_t* time )
{
    USER_MANAGER_STD_ERR_t opResult = USER_MANAGER_OK;
    UserLogCounter_t currentCounter;
    readUserLogCounter ( &currentCounter );
    if ( currentCounter == ( UserLogCounter_t ) 0xFFFFFFFF )
    {
        currentCounter = 0;
    }
    if ( currentCounter >= MAX_NUM_OF_USERS_LOGS )
    {
        opResult = USER_MANAGER_ERR_FULL;
    }
    else
    {
        UserLog_t log = {
            id ,
            *time
        };
        writeUserLog ( currentCounter , &log );
    }
    writeUserLogCounter ( &currentCounter );
    return opResult;
}
