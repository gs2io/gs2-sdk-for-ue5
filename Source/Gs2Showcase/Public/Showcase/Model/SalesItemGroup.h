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
#include "SalesItem.h"

namespace Gs2::Showcase::Model
{
    class GS2SHOWCASE_API FSalesItemGroup final : public Gs2Object, public TSharedFromThis<FSalesItemGroup>
    {
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FSalesItem>>> SalesItemsValue;

    public:
        FSalesItemGroup();
        FSalesItemGroup(
            const FSalesItemGroup& From
        );
        virtual ~FSalesItemGroup() override = default;

        TSharedPtr<FSalesItemGroup> WithName(const TOptional<FString> Name);
        TSharedPtr<FSalesItemGroup> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSalesItemGroup> WithSalesItems(const TSharedPtr<TArray<TSharedPtr<FSalesItem>>> SalesItems);

        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FSalesItem>>> GetSalesItems() const;


        static TSharedPtr<FSalesItemGroup> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSalesItemGroup, ESPMode::ThreadSafe> FSalesItemGroupPtr;
}