#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

bool evaluate(BYTE b[]);

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE* ptr_in=fopen(argv[1],"r");        //the open the forensic image file.
    if(ptr_in==NULL)
    {
        printf("Error: the forensic image file won't open\n");
        return 1;
    }

    int file_num = 0;       //number of photos done
    BYTE buffer[512];
    FILE* ptr_out;
    char file_name[8];      //buffer to save the jpg file name.
    bool first = true;

    while(fread(buffer,sizeof(BYTE),512,ptr_in))
    {

        if(evaluate(buffer))        //if start of new jpg
        {
            if(first)     //for the 1st image only
            {
                // sprintf(file_name,"%03i.jpg",file_num);
                // ptr_out = fopen(file_name,"w");
                // if (ptr_out == NULL)
                // {
                //     printf("the file couldnt open\n");
                //     return 1;
                // }
                // fwrite(buffer,sizeof(BYTE),512,ptr_out);
                // first =1;
                // continue;
                first =false;
            }

            else 
            {
                fclose(ptr_out);
            }  
            

            sprintf(file_name,"%03i.jpg",file_num++ );
            ptr_out = fopen(file_name,"w");
            if (ptr_out == NULL)
            {
                printf("the file couldnt open\n");
                return 1;
            }
            fwrite(buffer,sizeof(BYTE),512,ptr_out);
            
            

        }
        else if(!first)
        {
            fwrite(buffer,sizeof(BYTE),512,ptr_out);
        }
    }
    fclose(ptr_out);
    fclose(ptr_in);

}



bool evaluate(BYTE b[])
{
    if(b[0]!=0xff && b[1] != 0xd8 && b[2] != 0xff )
        return false;

    if((b[3] & 0xf0) != 0xe0)
        return false;

    return true;
}

