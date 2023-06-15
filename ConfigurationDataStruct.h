// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once 

#include "Engine/DataTable.h"

#include "ConfigurationDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FConfigurationDataStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FConfigurationDataStruct()
		: TotalGameSeconds(30)
		, BurgerMoveAmountPerSecond(100)
		, BearDamage(10)
		, BearProjectileDamage(5)
		, BearPoints(10)
		, FriesImpulseForce(150)
		, BearProjectileImpulseForce(150)
		, EasyMinSpawnDelay(1)
		, EasyMaxSpawnDelay(3)
		, EasyMinBearImpulseForce(150)
		, EasyMaxBearImpulseForce(200)
		, EasyMaxNumBears(5)
		, EasyBearMinShotDelay(1.5)
		, EasyBearMaxShotDelay(2.5)
		, EasyBearHomingDelay(2)
		, EasyBearProjectileHomingDelay(0.5)
		, MediumMinSpawnDelay(0.5)
		, MediumMaxSpawnDelay(2)
		, MediumMinBearImpulseForce(250)
		, MediumMaxBearImpulseForce(350)
		, MediumMaxNumBears(7)
		, MediumBearMinShotDelay(1)
		, MediumBearMaxShotDelay(2)
		, MediumBearHomingDelay(1.25)
		, MediumBearProjectileHomingDelay(0.35)
		, HardMinSpawnDelay(0.25)
		, HardMaxSpawnDelay(1)
		, HardMinBearImpulseForce(300)
		, HardMaxBearImpulseForce(600)
		, HardMaxNumBears(10)
		, HardBearMinShotDelay(0.5)
		, HardBearMaxShotDelay(1.5)
		, HardBearHomingDelay(0.5)
		, HardBearProjectileHomingDelay(0.2)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int TotalGameSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float BurgerMoveAmountPerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int BearDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int BearProjectileDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int BearPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float FriesImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float BearProjectileImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyMinSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyMaxSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyMinBearImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyMaxBearImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int EasyMaxNumBears;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyBearMinShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyBearMaxShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyBearHomingDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float EasyBearProjectileHomingDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumMinSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumMaxSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumMinBearImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumMaxBearImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int MediumMaxNumBears;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumBearMinShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumBearMaxShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumBearHomingDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float MediumBearProjectileHomingDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardMinSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardMaxSpawnDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardMinBearImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardMaxBearImpulseForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		int HardMaxNumBears;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardBearMinShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardBearMaxShotDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardBearHomingDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Struct")
		float HardBearProjectileHomingDelay;
};