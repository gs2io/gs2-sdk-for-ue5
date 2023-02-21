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
 */

#pragma once

#include "CoreMinimal.h"
#include "Auth/Domain/Model/Gs2AuthEzAccessTokenDomain.h"
#include "Gs2AuthAccessToken.generated.h"

USTRUCT(BlueprintType)
struct FGs2AuthAccessToken
{
    GENERATED_BODY()

    Gs2::UE5::Auth::Domain::Model::FEzAccessTokenDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2AuthAccessTokenValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Token = "";
    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    int64 Expire = 0;
};

inline FGs2AuthAccessTokenValue EzAccessTokenToFGs2AuthAccessTokenValue(
    const Gs2::UE5::Auth::Model::FEzAccessTokenPtr Model
)
{
    FGs2AuthAccessTokenValue Value;
    Value.Token = Model->GetToken() ? *Model->GetToken() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Expire = Model->GetExpire() ? *Model->GetExpire() : 0;
    return Value;
}

inline Gs2::UE5::Auth::Model::FEzAccessTokenPtr FGs2AuthAccessTokenValueToEzAccessToken(
    const FGs2AuthAccessTokenValue Model
)
{
    return MakeShared<Gs2::UE5::Auth::Model::FEzAccessToken>()
        ->WithToken(Model.Token)
        ->WithUserId(Model.UserId)
        ->WithExpire(Model.Expire);
}

UCLASS()
class BPGS2_API UGs2AuthAccessTokenFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};