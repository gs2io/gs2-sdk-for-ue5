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

namespace Gs2::Inventory::Model
{
    class GS2INVENTORY_API FHeldCount final : public Gs2Object, public TSharedFromThis<FHeldCount>
    {
        TOptional<FString> ItemNameValue;
        TOptional<int64> CountValue;

    public:
        FHeldCount();
        FHeldCount(
            const FHeldCount& From
        );
        virtual ~FHeldCount() override = default;

        TSharedPtr<FHeldCount> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FHeldCount> WithCount(const TOptional<int64> Count);

        TOptional<FString> GetItemName() const;
        TOptional<int64> GetCount() const;
        FString GetCountString() const;


        static TSharedPtr<FHeldCount> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FHeldCount, ESPMode::ThreadSafe> FHeldCountPtr;
}