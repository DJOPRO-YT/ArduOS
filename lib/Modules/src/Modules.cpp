#ifdef REMAKE_328

#include "Modules.hpp"

InfoModule info;
SoftwareSerial uart(TX,RX);

Module::Module() {}

void Module::Init()
{
    uart.begin(115200);

    pinMode(CS,OUTPUT);
    digitalWrite(CS,HIGH); //Not Selected
}

bool Module::Connect()
{
    uart.println("CHECK");
    if (uart.available())
    {
        if (uart.readStringUntil('\n') == "OK")
        {
            uart.println("GETINFO");
            /*
            - TEXT:
            MyModule;
            A012FG5695;
            0;                      //-1: Others
            */
           if (uart.available())
           {
            String data_ = uart.readStringUntil('\n');
            int index = 0;
            char* token = strtok((char*)data_.c_str(),";");
            while (token != NULL)
            {
                if (index == 0)
                {
                    if (strlen(token) <= sizeof(info.name))
                    {
                        strcat(info.name,token);
                    }else{return false;}
                }else if (index == 2)
                {
                    // Type Module Check
                    int choice = (int)token;
                    info.Type = choice;

                }else if (index == 1)
                {
                    if (strlen(token) <= sizeof(info.ID))
                    {
                        strcat(info.ID,token);
                    }else{return false;}
                    break;
                }else if (index == 3)
                {
                    // Type Module Check
                    int choice = (int)token;
                    if ((choice == UART_MODE_COM) || (choice == SPI_MODE_COM)) {
                        info.Type = choice;
                        info.connected = true;
                        return true;
                    }
                }

                token = strtok(NULL,";");
                index++;
            }

           }
        }
    }
    return false;
}

bool Module::IsConnected()
{
    uart.println("CHECK");
    if (uart.available()){info.connected = true;return true;}
    info.connected = false;
    return false;
}

InfoModule Module::GetModuleInfos()
{
    return info;
}

const char* GetDriverData()
{ 
    if (info.Type == 0 || info.connected == false) {return "";}

    uart.println("GETDRIVER");
    if (uart.available())
    {
        String hi = uart.readStringUntil('\n');
        return hi.c_str();
    }
    return "";
}

void Module::Launch()
{
    if (Module::IsConnected() == false) {return;}
    if (info.Type == 0) {
        if (info.com_type != UART_MODE_COM) {return;}
        uart.println("LAUNCH");
        UIManager::ResetScreen();
        while (true)
        {
            if (uart.available())
            {
                const char* cmd = uart.readStringUntil('\n').c_str();

                if (strcmp(cmd,"GETJPOSX") == 0)
                {
                    char buff[4];
                    itoa(Controller::GetJPos().x,buff,10);
                    uart.println(buff);
                }
                else if (strcmp(cmd,"GETJPOSY") == 0)
                {
                    char buff[4];
                    itoa(Controller::GetJPos().y,buff,10);
                    uart.println(buff);
                }
                else if (strcmp(cmd,"GETJBTN") == 0)
                {
                    uart.println(Controller::IsBtnClicked());
                }
                else if (strcmp(cmd,"END") == 0)
                {
                    uart.println("OK");
                    break;
                }
                else if (strcmp(cmd,"RESETSCREEN") == 0)
                {
                    uart.println("OK");
                    UIManager::ResetScreen();
                }
                else if (strcmp(cmd,"CLEARSCREEN") == 0)
                {
                    uart.println("OK");
                    UIManager::ClearScreen();
                }
                else
                {
                    char* tokens = strtok(strdup(cmd),";|");
                    if (tokens != NULL)
                    {
                        if (strcmp(tokens,"DRAWPSCREEN") == 0)
                        {
                            tokens = strtok(strdup(cmd),";|");
                            int data[4];
                            for (int i = 0;i < 4;i++)
                            {
                                if (tokens != NULL)
                                {
                                    data[i] = atoi(tokens);
                                }else{return;}
                                tokens = strtok(strdup(cmd),";|");
                            }
                            UIManager::DrawPixel(data[0],data[1],data[2],data[3]);
                        }
                        else if (strcmp(tokens,"ERASEPSCREEN") == 0)
                        {
                            tokens = strtok(strdup(cmd),";|");
                            int data[4];
                            for (int i = 0;i < 4;i++)
                            {
                                if (tokens != NULL)
                                {
                                    data[i] = atoi(tokens);
                                }else{return;}
                                tokens = strtok(strdup(cmd),";|");
                            }
                            UIManager::ErasePixel(data[0],data[1],data[2],data[3]);
                        }
                        else if (strcmp(tokens,"TEXTSCREEN") == 0)
                        {
                            tokens = strtok(strdup(cmd),";|");
                            int data[2];
                            for (int i = 0;i < 2;i++)
                            {
                                if (tokens != NULL)
                                {
                                    data[i] = atoi(tokens);
                                }else{return;}
                                tokens = strtok(strdup(cmd),";|");
                            }

                            if (tokens != NULL) {
                                UIManager::PrintText(data[0],data[1],tokens);
                            }
                        }

                    }
                }

            }
        }
    }
}
#endif