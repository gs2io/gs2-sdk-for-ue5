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

#include "Money2/Model/Gs2Money2EzAppleAppStoreSubscriptionContent.h"
#include "Gs2Money2AppleAppStoreSubscriptionContent.generated.h"

USTRUCT(BlueprintType)
struct FGs2Money2AppleAppStoreSubscriptionContent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString SubscriptionGroupIdentifier = "";
};

inline FGs2Money2AppleAppStoreSubscriptionContent EzAppleAppStoreSubscriptionContentToFGs2Money2AppleAppStoreSubscriptionContent(
    const Gs2::UE5::Money2::Model::FEzAppleAppStoreSubscriptionContentPtr Model
)
{
    FGs2Money2AppleAppStoreSubscriptionContent Value;
    Value.SubscriptionGroupIdentifier = Model->GetSubscriptionGroupIdentifier() ? *Model->GetSubscriptionGroupIdentifier() : "";
    return Value;
}

inline Gs2::UE5::Money2::Model::FEzAppleAppStoreSubscriptionContentPtr FGs2Money2AppleAppStoreSubscriptionContentToEzAppleAppStoreSubscriptionContent(
    const FGs2Money2AppleAppStoreSubscriptionContent Model
)
{
    return MakeShared<Gs2::UE5::Money2::Model::FEzAppleAppStoreSubscriptionContent>()
        ->WithSubscriptionGroupIdentifier(Model.SubscriptionGroupIdentifier);
}