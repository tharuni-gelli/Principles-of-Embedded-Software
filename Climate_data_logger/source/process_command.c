/*
 * process_command.c
 *
 *  Created on: 14-Dec-2023
 *      Author: THARUNI GELLI
 */
#include "process_command.h"
/******************************************************************************
 * Defines here
 *****************************************************************************/
/**
 * @brief Maximum size for Hexdump data storage.
 */
#define Hexdump_max_size 	(640)

/**
 * @brief Temperature threshold for a warning condition.
 */
#define WARNING_TEMP 		(26)

/**
 * @brief Carbon monoxide (CO) levels threshold for a warning condition.
 */
#define WARNING_CO 			(650)

/**
 * @brief Temperature threshold for a danger condition.
 */
#define DANGER_TEMP 		(30)

/**
 * @brief Carbon monoxide (CO) levels threshold for a danger condition.
 */
#define DANGER_CO 			(800)

/**
 * @brief Maximum Pulse Width Modulation (PWM) value for an RGB LED.
 */
#define MAX_PWM				(255)

/**
 * @brief Time value for 100 milliseconds timer.
 */
#define HUNDRED_MS			(10)

/**
 * @brief Definition for function pointer type for command handlers.
 */
typedef void (*command_handler_t)(int, char *argv[]);

/**
 * @brief Command handler for the "author" command.
 *
 * This function handles the "author" command, providing information about the author.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void handle_author(int argc, char *argv[]);

/**
 * @brief Command handler for the "hexdump" command.
 *
 * This function handles the "hexdump" command, displaying a hexadecimal dump of data.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void handle_dump(int argc, char *argv[]);

/**
 * @brief Command handler for the "help" command.
 *
 * This function handles the "help" command, providing information about available commands.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void handle_help(int argc, char *argv[]);

/**
 * @brief Command handler for the "temperature" command.
 *
 * This function handles the "temperature" command, providing temperature-related information.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void handle_temp(int argc, char *argv[]);

/**
 * @brief Command handler for the "humidity" command.
 *
 * This function handles the "humidity" command, providing humidity-related information.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void handle_hum(int argc, char *argv[]);

/**
 * @brief Command handler for the "CO" (carbon monoxide) level command.
 *
 * This function handles the "CO" command, providing information about CO levels.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void handle_co(int argc, char *argv[]);

/**
 * @brief Command handler for the "weather" monitoring station command.
 *
 * This function handles the "weather" command, providing information from a weather monitoring station.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 */
void handle_weather(int argc, char *argv[]);

/**
 * @brief Structure to define a command table entry.
 */
typedef struct
{
    const char *name;           // Command name
    command_handler_t handler;  // Function pointer to the command handler
    const char *help_string;    // Help string describing the command
} command_table_t;


/**
 * @brief State table containing all possible commands with corresponding command handlers and help strings.
 * This table can be modified in the future to include additional command options.
 */
static const command_table_t commands[] =
{
    // TODO: Fill out the command table with command names, corresponding handlers, and help strings.

    { "author"      ,   handle_author   , "Display information about the author."       },
    { "dump"        ,   handle_dump     , "Display a hexadecimal dump of data."         },
    { "help"        ,   handle_help     , "Display help information for available commands." },
    { "temperature" ,   handle_temp     , "Display temperature-related information."    },
    { "humidity"    ,   handle_hum      , "Display humidity-related information."       },
    { "co"          ,   handle_co       , "Display information about CO (carbon monoxide) levels." },
    { "Weather"     ,   handle_weather  , "Display information from a weather monitoring station." },
};

// Calculate the number of commands based on the size of the commands array
static const int num_commands = sizeof(commands) / sizeof(command_table_t);

// Function to handle user input for Author and print the author's name
void handle_author(int argc, char *argv[])
{
    // Print the author's name
    printf("Tharuni Gelli \n\r");
    printf("? ");
}

// Function to handle user input for Humidity and print the current humidity
void handle_hum(int argc, char *argv[])
{
    // Set I2C1 flags for communication
    set_I2C1_flags();

    // Read humidity value from SHT21 Sensor
    float humidity = read_humidity();
    int hum_dupe= (int)humidity;
    humidity=humidity*2;

    // Print the current humidity
    printf("Current Humidity is: %d\n\r",hum_dupe );
    printf("? ");
}

// Function to handle user input for Temperature and print the current temperature
void handle_temp(int argc, char *argv[])
{
    // Set I2C1 flags for communication
    set_I2C1_flags();

    // Read temperature value from SHT21 Sensor
    float temperature = read_temperature();
    int temp_dupe= (int)temperature;
    temperature=temperature*2;

    // Print the current temperature
    printf("Current Temperature is: %d \n\r", temp_dupe);
    printf("? ");
}

// Function to handle user input for CO (carbon monoxide) Levels and print the current CO Levels
void handle_co(int argc, char *argv[])
{
    // Get CO Levels from MQ7 Sensor
    int co_levels = get_co_values();

    // Print the current CO Levels
    printf("CO Levels = %d\n\r", co_levels);

    printf("? ");
}


// Function to initiate weather monitoring station
void handle_weather(int argc, char *argv[])
{
    printf("\n\r Weather Monitoring Starts \n\r");
    reset_timer();

    while(1)
    {
        // Start a 100 ms timer
        int time = get_timer();

        // Check if 100 ms has elapsed
        if (time >= HUNDRED_MS)
        {
            reset_timer();

            // Obtain and print the current temperature
            set_I2C1_flags();
            // Read temperature value from SHT21 Sensor
               float temperature = read_temperature();
               int temp_dupe= (int)temperature;
               temperature=temperature*2;

               // Print the current temperature
               printf("TEMPERATURE is: %d \n\r", temp_dupe);

            // Obtain and print the current humidity level
            set_I2C1_flags();
            // Read humidity value from SHT21 Sensor
                float humidity = read_humidity();
                int hum_dupe= (int)humidity;
                humidity=humidity*2;
                // Print the current humidity
                printf("HUMIDITY is: %d\n\r",hum_dupe );

            // Obtain and print the current CO level
            int co = get_co_values();
            printf("CO=%d\n\r", co);

            // Introduce a delay of 100 ms
            Delay(HUNDRED_MS);

            /***************************************************************************************
             * Compare current temperature and CO levels to define states:
             * Safe State    - If temperature and CO levels are below safe values
             * Warning State - If either temperature or CO levels are above warning values
             * Danger State  - If either temperature or CO levels are above danger values
             **************************************************************************************/

            if (temp_dupe >= DANGER_TEMP || co > DANGER_CO)
            {
                printf("\n\r DANGER!! \n\r");
                printf("\n\r");
                RGB_Manup(MAX_PWM, 0, 0); // Set RGB LED to indicate danger
            }
            else if (temp_dupe >= WARNING_TEMP || co > WARNING_CO)
            {
                printf("\n\r WARNING!! \n\r");
                printf("\n\r");
                RGB_Manup(MAX_PWM, MAX_PWM, 0); // Set RGB LED to indicate warning
            }
            else if (temp_dupe < WARNING_TEMP && co < WARNING_CO)
            {
                printf("\n\r SAFE!! \n\r");
                printf("\n\r");
                RGB_Manup(0, MAX_PWM, 0); // Set RGB LED to indicate safe condition
            }
        }
    }
}

// Function to print a hexdump when the user inputs the "dump" command
void handle_dump(int argc, char *argv[])
{
    uint32_t len = 0;
    uint32_t start = 0;

    // Parse and save the start address from the user input, which can be decimal or hexadecimal
    if (((*argv[1] >= '0') && (*argv[1] <= '9')) || ((*argv[1] >= 'A') && (*argv[1] <= 'F')) || ((*argv[1] >= 'a') && (*argv[1] <= 'f')))
    {
        sscanf(argv[1], "%x", &start);

        // Parse the user input for hexdump length, considering hexadecimal or decimal input
        if (strstr((char*) argv[2], "0x") || strstr((char*) argv[2], "0X"))
        {
            sscanf(argv[2], "%x", &len);
        }
        else
        {
            sscanf(argv[2], "%d", &len);
        }

        // Check if the user input length is within the defined range for hexdump
        if (len > Hexdump_max_size)
        {
            printf("Length out of range. Enter a length between 1 to 640 or 0x01 to 0x280\n\r");
            printf("? ");
            return;
        }

        // Call the hexdump function if the input start address is within the valid range
        hexdump(start, len);
        printf("? ");
    }
    else
    {
        printf("Unknown Command \n\r"); // Print an error message if the user input does not satisfy the expected format
        printf("? ");
    }
}


// Function to print all available commands when the user inputs the "Help" command
void handle_help(int argc, char *argv[])
{
    // Print information about the "Temperature" command
    printf("Command: Temperature       ; Arguments: NONE            ; Description: Prints surrounding temperature \n\r");

    // Print information about the "CO" command
    printf("Command: CO                ; Arguments: NONE            ; Description: Prints surrounding CO Levels \n\r");

    // Print information about the "Weather" command
    printf("Command: Weather           ; Arguments: NONE            ; Description: Starts Weather Monitoring station \n\r");

    // Print a prompt for the next user input
    printf("\n\r? ");
}


// Function to process a user command string
void process_command(char *input)
{
    char *p = input;
    char *end;

    // Find the end of the input string
    for (end = input; *end != '\0'; end++)
    {
        ;
    }

    // Tokenize the input in place
    bool in_token = false;
    char *argv[10];
    int argc = 0;
    memset(argv, 0, sizeof(argv));

    // Perform lexical analysis by checking the end of the string and terminating tokens with a null character
    // Store the tokenized string values for further command processing
    for (p = input; p < end; p++)
    {
        switch (in_token)
        {
        case false:
            if ((*p != ' ') || (*p != '\t'))
            {
                argv[argc] = p;
                argc++;
                in_token = true;
            }
            break;
        case true:
            if ((*p == ' ') || (*p == '\t'))
            {
                *p = '\0';
                in_token = false;
            }
            break;
        }
    }

    argv[argc] = NULL;      // Append a null character to mark the end of the tokenized array

    if (argc == 0)          // No command provided
    {
        return;
    }

    // Compare the input command with commands in the state table and perform the associated function
    for (int i = 0; i < num_commands; i++)
    {
        if (strcasecmp(argv[0], commands[i].name) == 0)
        {
            commands[i].handler(argc, argv);
            break;
        }

        // Error handling if the input command is not one of the commands from the state table
        if (i == (num_commands - 1))
        {
            printf("Unknown Command :");
            for (int j = 0; j < argc; j++)
            {
                printf(" %s", argv[j]);
            }
            printf("\n\r? ");
        }
    }
}
