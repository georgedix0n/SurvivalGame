
#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemsAdded UMETA(DisplayName = "No items added"),
	IAR_SomeItemsAdded UMETA(DisplayName = "Some items added"),
	IAR_AllItemsAdded UMETA(DisplayName = "All items added")
};

USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_BODY()

public:

	FItemAddResult() {};
	FItemAddResult(int32 InItemQuantity) : AmountToGive(InItemQuantity), ActualAmountGiven(0) { };
	FItemAddResult(int32 InItemQuantity, int32 InQuantityAdded) : AmountToGive(InItemQuantity), ActualAmountGiven(InQuantityAdded) {};
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 AmountToGive;

	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 ActualAmountGiven;

	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	EItemAddResult Result;

	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	FText ErrorText;

	//helpers
	static FItemAddResult AddedNone(const int32 InItemQuantity, const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult(InItemQuantity);
		AddedNoneResult.Result = EItemAddResult::IAR_NoItemsAdded;
		AddedNoneResult.ErrorText = ErrorText;

		return AddedNoneResult;
	}

	static FItemAddResult AddedSome(const int32 InItemQuantity, const int32 ActualAmountGiven, const FText& ErrorText)
	{
		FItemAddResult AddedSomeResult(InItemQuantity, ActualAmountGiven);

		AddedSomeResult.Result = EItemAddResult::IAR_SomeItemsAdded;
		AddedSomeResult.ErrorText = ErrorText;

		return AddedSomeResult;
	}

	static FItemAddResult AddedAll(const int32 InItemQuantity)
	{
		FItemAddResult AddedAllResult(InItemQuantity, InItemQuantity);
		AddedAllResult.Result = EItemAddResult::IAR_AllItemsAdded;

		return AddedAllResult;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class UItem;

public:	

	UInventoryComponent();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	FItemAddResult TryAddItem(class UItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FItemAddResult TryAddItemFromClass(TSubclassOf<class UItem> ItemClass, const int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(class UItem* Item);

	UFUNCTION(BlueprintPure, Category="Inventory")
	bool HasItem(TSubclassOf <class UItem> ItemClass, const int32 Quantity = 1) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UItem* FindItem(class UItem* Item) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	UItem* FindItemByClass(TSubclassOf<class UItem> ItemClass) const;

	UFUNCTION(BlueprintPure, Category = "Inventory")
	TArray<UItem*> FindItemsByClass(TSubclassOf<class UItem> ItemClass) const;


	UFUNCTION(BlueprintPure, Category = "Inventory")
	float GetCurrentWeight() const;

	int32 ConsumeItem(class UItem* Item);
	int32 ConsumeItem(class UItem* Item, const int32 Quantity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetWeightCapacity(const float NewWeightCapacity);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetCapacity(const int32 NewCapacity);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	FORCEINLINE float GetWeightCapacity() const { return WeightCapacity; }

	UFUNCTION(BlueprintPure, Category = "Inventory")
	FORCEINLINE int32 GetCapacity() const { return Capacity; }

	UFUNCTION(BlueprintPure, Category = "Inventory")
	FORCEINLINE TArray<class UItem*> GetItems() const { return Items;  }

	UFUNCTION(Client,Reliable)
	void ClientRefreshInventory();

	UPROPERTY(BlueprintAssignable, Category="Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Inventory")
	float WeightCapacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory", meta =(ClampMin = 0, ClampMax = 200))
	int32 Capacity;

	UPROPERTY(ReplicatedUsing = OnRep_Items, VisibleAnywhere, Category ="Inventory")
	TArray<class UItem*> Items;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch* Bunch, FReplicationFlags *RepFlags) override;

private:
	UItem* AddItem(class UItem* Item);
	UFUNCTION()
	void OnRep_Items();

	UPROPERTY()
	int32 ReplicatedItemsKey;

	FItemAddResult TryAddItem_Internal(class UItem* Item);
};
