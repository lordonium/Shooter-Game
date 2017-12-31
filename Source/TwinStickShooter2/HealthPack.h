// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "HealthPack.generated.h"

UCLASS()
class TWINSTICKSHOOTER2_API AHealthPack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPack();
    
    AHealthPack(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    // Engine Event for Overlap events
    virtual void NotifyActorBeginOverlap(class AActor* Other) override;
    
    // Hides and then deletes this actor from the game world
    void RemoveFromWorld();
    
    // Private information (Player Handles and Checks)
    
private:
    
    // Checks if the player is alive and can pick this up
    bool CanBePickedUp(class ABaseCharacter* Other);
    
    // Handles giving the player health, or other things
    void HandlePickUp(class ABaseCharacter* Other);
    
    // Handles the effects or sounds
    void HandleEffects();
    
    
    // Protected Info Helth Pack's Health, Collision, Particles
protected:
    // Holds the amount of health it can give to the player
    float Health;
    
    // Holds the particle that will spawn when the player picks this up
    UPROPERTY(EditDefaultsOnly, Category = "Caught Particle")
    UParticleSystem* ourParticle;
    
    // Holds the bounds in which this object can interact with the player
    UBoxComponent* collisionComponent;
    
    
    
	
};
