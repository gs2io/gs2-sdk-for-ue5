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
#include "Dictionary/Model/Gs2DictionaryEntry.h"
#include "Dictionary/Model/Gs2DictionaryEntry.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2DictionaryActionGetEntryWithSignature.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DictionaryGetEntryWithSignatureSuccessDelegate, FGs2DictionaryOwnEntry, Entry, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DictionaryGetEntryWithSignatureErrorDelegate, FGs2DictionaryOwnEntry, Entry, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2DictionaryGetEntryWithSignatureAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2DictionaryOwnEntry Entry;
    FString KeyId;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2DictionaryGetEntryWithSignatureSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2DictionaryGetEntryWithSignatureErrorDelegate OnError;

    UGs2DictionaryGetEntryWithSignatureAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Dictionary::Entry::Action::GetEntryWithSignature", Category="Game Server Services|GS2-Dictionary|Namespace|User|Entry|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2DictionaryGetEntryWithSignatureAsyncFunction* GetEntryWithSignature(
        UObject* WorldContextObject,
        FGs2DictionaryOwnEntry Entry,
        FString KeyId
    );

    virtual void Activate() override;
};