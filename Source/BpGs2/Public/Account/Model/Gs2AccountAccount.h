/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Account/Domain/Model/Gs2AccountEzAccountGameSessionDomain.h"
#include "Account/Domain/Model/Gs2AccountEzAccountDomain.h"
#include "Gs2AccountAccount.generated.h"

USTRUCT(BlueprintType)
struct FGs2AccountOwnAccount
{
    GENERATED_BODY()

    Gs2::UE5::Account::Domain::Model::FEzAccountGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2AccountAccount
{
    GENERATED_BODY()

    Gs2::UE5::Account::Domain::Model::FEzAccountDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2AccountAccountValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Password = "";
    UPROPERTY(BlueprintReadOnly)
    int64 CreatedAt = 0;
};

inline FGs2AccountAccountValue EzAccountToFGs2AccountAccountValue(
    const Gs2::UE5::Account::Model::FEzAccountPtr Model
)
{
    FGs2AccountAccountValue Value;
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Password = Model->GetPassword() ? *Model->GetPassword() : "";
    Value.CreatedAt = Model->GetCreatedAt() ? *Model->GetCreatedAt() : 0;
    return Value;
}

UCLASS()
class BPGS2_API UGs2AccountAccountFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Account::TakeOver", Category="Game Server Services|GS2-Account|Namespace|Account|TakeOver", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="TakeOver") FGs2AccountTakeOver TakeOver(
        FGs2AccountAccount Account,
        int32 Type
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Account::OwnTakeOver", Category="Game Server Services|GS2-Account|Namespace|Account|TakeOver", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="TakeOver") FGs2AccountOwnTakeOver OwnTakeOver(
        FGs2AccountOwnAccount Account,
        int32 Type
    );
};