#pragma once

#define PRINT_STR(str) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT(str)));}
#define PRINT_ONE_VAR(str, var) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT(str), var));}