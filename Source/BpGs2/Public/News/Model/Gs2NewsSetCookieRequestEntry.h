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
#include "News/Domain/Model/Gs2NewsEzSetCookieRequestEntryGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2NewsSetCookieRequestEntry.generated.h"

USTRUCT(BlueprintType)
struct FGs2NewsOwnSetCookieRequestEntry
{
    GENERATED_BODY()

    Gs2::UE5::News::Domain::Model::FEzSetCookieRequestEntryGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2NewsSetCookieRequestEntryValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Key = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Value = "";
};

inline FGs2NewsSetCookieRequestEntryValue EzSetCookieRequestEntryToFGs2NewsSetCookieRequestEntryValue(
    const Gs2::UE5::News::Model::FEzSetCookieRequestEntryPtr Model
)
{
    FGs2NewsSetCookieRequestEntryValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2NewsSetCookieRequestEntryFunctionLibrary::EzSetCookieRequestEntryToFGs2NewsSetCookieRequestEntryValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Key = Model->GetKey() ? *Model->GetKey() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : "";
    return Value;
}

inline Gs2::UE5::News::Model::FEzSetCookieRequestEntryPtr FGs2NewsSetCookieRequestEntryValueToEzSetCookieRequestEntry(
    const FGs2NewsSetCookieRequestEntryValue Model
)
{
    return MakeShared<Gs2::UE5::News::Model::FEzSetCookieRequestEntry>()
        ->WithKey(Model.Key)
        ->WithValue(Model.Value);
}

UCLASS()
class BPGS2_API UGs2NewsSetCookieRequestEntryFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};