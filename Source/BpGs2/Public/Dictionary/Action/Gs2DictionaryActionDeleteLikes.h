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
#include "Dictionary/Model/Gs2DictionaryLike.h"
#include "Dictionary/Model/Gs2DictionaryUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2DictionaryActionDeleteLikes.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DictionaryDeleteLikesSuccessDelegate, const TArray<FGs2DictionaryOwnLike>&, Likes, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2DictionaryDeleteLikesErrorDelegate, const TArray<FGs2DictionaryOwnLike>&, Likes, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2DictionaryDeleteLikesAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2DictionaryOwnUser User;
    TArray<FString> EntryModelNames;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2DictionaryDeleteLikesSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2DictionaryDeleteLikesErrorDelegate OnError;

    UGs2DictionaryDeleteLikesAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Dictionary::Like::Action::DeleteLikes", Category="Game Server Services|GS2-Dictionary|Namespace|User|Like|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2DictionaryDeleteLikesAsyncFunction* DeleteLikes(
        UObject* WorldContextObject,
        FGs2DictionaryOwnUser User,
        TArray<FString> EntryModelNames
    );

    virtual void Activate() override;
};