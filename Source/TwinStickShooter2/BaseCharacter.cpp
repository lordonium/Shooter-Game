// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinStickShooter2.h"
#include "BaseCharacter.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

//Implement CalculateHealth
void ABaseCharacter::CalculateHealth(float Delta)
{
    Health += Delta;
    CalculateDead();
}

//Implement CalculateDead
void ABaseCharacter::CalculateDead()
{
    if (Health <= 0)
    {
        isDead = true;
    }
    else
    {
        isDead = false;
    }
    
}


//Implemant PostEditChangeProperty

# if WITH_EDITOR
void ABaseCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    isDead = false;
    Health = 100;
    
    Super::PostEditChangeProperty(PropertyChangedEvent);
    
    CalculateDead();
}

#endif

//------------------------------------
// Health Pack Handling and Accessors
//------------------------------------

void ABaseCharacter::addHealth(float Hpp)
{
   if (Hpp != 0.f)
   {
       if (Health < 70.f)
       {
           Health += Hpp;
           
           if (Health >= 100.f)
           {
               Health = 100.f;
           }
       }
   }
}

bool ABaseCharacter::isAlive()
{
    if (Health <= 0.f)
    {
        return false;
    }
    else
    {
        return true; 
    }
}





