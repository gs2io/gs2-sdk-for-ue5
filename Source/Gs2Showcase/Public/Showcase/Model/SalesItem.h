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
#include "VerifyAction.h"
#include "ConsumeAction.h"
#include "AcquireAction.h"

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FSalesItem final : public Gs2Object, public TSharedFromThis<FSalesItem>
    {
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> VerifyActionsValue;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;

    public:
        FSalesItem();
        FSalesItem(
            const FSalesItem& From
        );
        virtual ~FSalesItem() override = default;

        TSharedPtr<FSalesItem> WithName(const TOptional<FString> Name);
        TSharedPtr<FSalesItem> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSalesItem> WithVerifyActions(const TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> VerifyActions);
        TSharedPtr<FSalesItem> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> ConsumeActions);
        TSharedPtr<FSalesItem> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);

        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FVerifyAction>>> GetVerifyActions() const;
        TSharedPtr<TArray<TSharedPtr<FConsumeAction>>> GetConsumeActions() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetAcquireActions() const;


        static TSharedPtr<FSalesItem> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSalesItem, ESPMode::ThreadSafe> FSalesItemPtr;
}