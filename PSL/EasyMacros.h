#pragma once

#define DRAW_SPHERE_AT_LOCATION(loc) DrawDebugSphere(GetWorld(), loc, 16.f, 12, FColor::Red, false);
#define PRINT_STR(str) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT(str)));}
#define PRINT_ONE_VAR(str, var) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT(str), var));}