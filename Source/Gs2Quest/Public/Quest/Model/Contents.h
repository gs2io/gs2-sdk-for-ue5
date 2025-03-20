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
#include "Core/Gs2Object.h"
#include "AcquireAction.h"

namespace Gs2::Quest::Model
{
    class GS2QUEST_API FContents final : public FGs2Object, public TSharedFromThis<FContents>
    {
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> CompleteAcquireActionsValue;
        TOptional<int32> WeightValue;

    public:
        FContents();
        FContents(
            const FContents& From
        );
        virtual ~FContents() override = default;

        TSharedPtr<FContents> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FContents> WithCompleteAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> CompleteAcquireActions);
        TSharedPtr<FContents> WithWeight(const TOptional<int32> Weight);

        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetCompleteAcquireActions() const;
        TOptional<int32> GetWeight() const;
        FString GetWeightString() const;


        static TSharedPtr<FContents> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FContents, ESPMode::ThreadSafe> FContentsPtr;
}