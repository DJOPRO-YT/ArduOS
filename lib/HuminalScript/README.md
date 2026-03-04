# HuminalScript
## Custom Easy Readable language and Minimal for ATMEL ATMEGA328P

## Syntax Tree :

create +
       > variable +
                  > <name_variable>
                  > = 
                  > <value>

       > function +
                  > <name_function>
                  > (
                    > <Arg>
                    > ,
                    > <Arg>
                  > )
                nl> <code>
                nl> <code>
                nl> <code>
                nl> end / return <variable_name>


change +
       > variable +
                  > <name_variable>
                  > = 
                  > <value>

call +
     > function +
                > <name_function>
                > (
                  > <Arg>
                  > ,
                  > <Arg>
                > )
               *> save
               *> to
               *> <name_variable>
