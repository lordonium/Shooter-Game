// Fill out your copyright notice in the Description page of Project Settings.

#include "TwinStickShooter2.h"
#include "BaseCharacter.h"
#include "HealthPack.h"


// Sets default values
//Default Constructor
AHealthPack::AHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    //Health sets
    Health = 40.f;

}

//Argumented Constructor
AHealthPack::AHealthPack(const FObjectInitializer& ObjectInitializer)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    //Health sets
    Health = 40.f;
    
    //Collision set up
    
    collisionComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("Collision Component"));
    
    // Create a FVector to set this collisionComponent Size
    FVector boxSize = FVector(10.f, 10.f, 10.f);
    
    // Set the box size using a FVECTOR
    collisionComponent->SetBoxExtent(boxSize);
    
    /*
    // Set this box to be effected by gravity
    collisionComponent->SetEnableGravity(true);
    
    // Set this box to be effected by basic physics
    collisionComponent->SetSimulatePhysics(true);
    */
    
    // Set this box as the root component in the scene root
    RootComponent = collisionComponent;
}


// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPack::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


// Overlap Event
void AHealthPack::NotifyActorBeginOverlap(class AActor *Other)
{
    Super::NotifyActorBeginOverlap(Other);
    
    // If the other is NOT null
    if (Other != NULL)
    {
        // If the player has health GREATER THAN 0.f
        if(CanBePickedUp(Cast<ABaseCharacter>(Other)))
        {
            // Give the player health using an accessor method on the player
            HandlePickUp(Cast<ABaseCharacter>(Other));
            
            // Handle aka play any effects or sounds
            HandleEffects();
            
            // Hide and then mark this actor for the next deletion cycl
            RemoveFromWorld();
        }
        
    }
}

//Remove From World Method
void AHealthPack::RemoveFromWorld()
{
    // Hide the static mesh of the box
    RootComponent->GetChildComponent(0)->SetHiddenInGame(true);
    
    // Mark this object to be deleted
    K2_DestroyActor();
}

//---------------------------------------
// Player Interaction Handling and Checks
//---------------------------------------

// Can Be Picked Up Method

bool AHealthPack::CanBePickedUp(class ABaseCharacter* Other)
{
    // Create a flag and assume that the player can not pick it up
    bool flag = false;
    
    // If the player is not null, and the player has returned they can pick it up
    if (Other != NULL && Other->isAlive())
    {
        // Set the flag to true
        flag = true;
    }
    
    // Return the result
    return flag;
    
}

// Handle Pick Up Method
void AHealthPack::HandlePickUp(class ABaseCharacter* Other)
{
    // If the player aka Other is not null
    if (Other != NULL)
    {
        // Use the accessor method on the player to pass them health from this object
        Other->addHealth(this->Health);
    }
}

// Handle Effects
void AHealthPack::HandleEffects()
{
    // Get this actors location in world
    FVector ourLoc = this->GetActorLocation();
    
    // Create a rotator and set it to (0.f, 0.f, 0.f)
    FRotator ourRot = FRotator::ZeroRotator;
    
    // Spawn a particle at the location
    UGameplayStatics::SpawnEmitterAtLocation(this, ourParticle, ourLoc, ourRot);
    
}

